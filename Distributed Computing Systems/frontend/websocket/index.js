// Importa a biblioteca WebSocket
const WebSocket = require('ws');

// Importa a configuração do Kafka
const kafka = require('./kafka');

// Define o tópico do Kafka
const topic = 'updates'

// Cria um consumidor Kafka com o ID do grupo especificado nas variáveis de ambiente
const consumer = kafka.consumer({ groupId: process.env.GROUP_ID })

// Cria um produtor Kafka com a opção de criação automática de tópicos
const producer = kafka.producer({ allowAutoTopicCreation: true });

// Função assíncrona para configurar o consumidor e o produtor Kafka
const run = async () => {
  await producer.connect() // Conecta o produtor
  await consumer.connect() // Conecta o consumidor
  await consumer.subscribe({ topic, fromBeginning: true }) // Assina o tópico a partir do início
  await consumer.run({
    eachMessage: async ({ topic, partition, message }) => {
        const prefix = `${topic}[${partition} | ${message.offset}] / ${message.timestamp}`;
        console.log(`- ${prefix} ${message.key}#${message.value}`);

        // Envia a mensagem para todos os clientes WebSocket conectados, exceto o que enviou a mensagem
        if(message.key !== process.env.GROUP_ID) {
            wss.clients.forEach(client => {
                client.readyState === WebSocket.OPEN && client.send((message.value.toString()));
            });
        }
    },
  })
}

// Função para enviar uma mensagem usando o produtor Kafka
const send_message = async (data) => {
    await producer.send({
        topic: topic,
        messages:[{
            key: process.env.GROUP_ID, value: data
        }]
    });
    console.log(data);
};

// Cria um servidor WebSocket na porta especificada ou na porta 8082
const wss = new WebSocket.Server({ port: process.env.PORT || 8082 });

// Executa a função de configuração do Kafka
run();

// Evento disparado quando um novo cliente WebSocket se conecta
wss.on("connection", (ws, req) => {
    console.log("New connection from " + req.socket.remoteAddress + req.socket.remotePort);
    
    // Evento disparado quando um cliente WebSocket se desconecta
    ws.on("close", (ws, reason) => {
        console.log("Client disconnected: " + req.socket.remoteAddress + reason);
    });

    // Evento disparado quando uma mensagem é recebida de um cliente WebSocket
    ws.on("message",  (data, isBinary) => {
        try {
            // Verifica se a mensagem é binária e a converte para string se não for
            const message = isBinary ? data : data.toString();

            send_message(message);
            wss.clients.forEach(client => {
                // Envia a mensagem para todos os clientes WebSocket conectados
                client.readyState === WebSocket.OPEN && client.send((message));
            });
        } catch(e) {
            console.log(`Something went wrong with the message: ${e.message}`);
        }
    });
});