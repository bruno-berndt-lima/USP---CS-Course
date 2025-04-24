// Importa a classe Kafka da biblioteca kafkajs
const {Kafka} = require("kafkajs")

// Cria uma instância do Kafka com a configuração do cliente
const kafka = new Kafka({
    clientId: 'wss',
    brokers: [process.env.KAFKA_BOOTSTRAP_SERVER]
})

// Exporta a instância do Kafka para uso em outros módulos
module.exports = kafka