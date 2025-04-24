const url = "localhost";
// const url = "andromeda.lasdpc.icmc.usp.br";
const port = 7031;

// Cria uma conexão WebSocket com o servidor
const ws = new WebSocket(`ws://${url}:${port}/websocket`);

// Evento acionado quando a conexão WebSocket é aberta
ws.addEventListener("open", () => {
    console.log("We are connected!");
});

// Variável para controlar a seleção padrão
let default_selected = false;

// Obtém os elementos do DOM
let table_options = document.getElementById("table_options");
let form_container = document.getElementById("form_container");

// Classe para representar uma opção de tabela
class TableOption {
    constructor(id, name, fields) {
        this.id = id;
        this.fields = fields;
        // Adiciona uma opção ao elemento de seleção de tabelas
        table_options.innerHTML += `<option value="${id}" ${!default_selected ? "selected" : ""}>${name}</option>`;

        // Define a tabela padrão se ainda não foi selecionada
        if (!default_selected) this.setTable();
        default_selected = true;
    }

    // Define a tabela atual
    setTable() {
        this.generateFormFields();
    }
    // Gera os campos do formulário para a tabela atual
    generateFormFields() {
        form_container.innerHTML = ''; // Limpa os campos anteriores
        for (let field of this.fields) {
            let input_html = `<label for="${field}">${field}</label><input type="text" id="${field}" name="${field}"><br/>`;
            form_container.innerHTML += input_html;
        }
    }
}

// Mapeamento de tabelas com seus campos
let table_maps = {
    remedio: new TableOption("remedio", "Remédios", ["Nome", "Tarja"]),
    receita: new TableOption("receita", "Receitas", ["ID", "Médico", "Paciente", "Posto"]),
    receitaremedio: new TableOption("receitaremedio", "Receitas Remédios", ["Receita", "Remedio", "Prontidão"]),
    usuario: new TableOption("usuario", "Usuários", ["CPF", "Email", "Senha"]),
    farmaceutico: new TableOption("farmaceutico", "Farmacêuticos", ["Usuário", "Posto"]),
    medico: new TableOption("medico", "Médicos", ["Usuário", "Posto"]),
    paciente: new TableOption("paciente", "Pacientes", ["Usuário", "Convênio", "Posto"]),
    regiao: new TableOption("regiao", "Regiões", ["Nome"]),
    tarja: new TableOption("tarja", "Tarjas", ["Nome", "Retenção"]),
    posto: new TableOption("posto", "Postos", ["ID", "Nome", "Região"]),
    estoqueregional: new TableOption("estoqueregional", "Estoques Regionais", ["ID", "Região"]),
    estoqueregionalremedio: new TableOption("estoqueregionalremedio", "Estoque Regional Remédios", ["EstoqueRegional", "Remédio", "Quantidade"]),
    estoquelocal: new TableOption("estoquelocal", "Estoques Locais", ["ID", "Região"]),
    estoquelocalremedio: new TableOption("estoquelocalremedio", "Estoque Local Remédios", ["EstoqueLocal", "Remédio", "Quantidade"])
};

// Função para trocar a tabela selecionada
function change_table() {
    table_maps[table_options.value].setTable();
}

// Função chamada ao carregar a página para configurar a tabela inicial
window.onload = function () {
    change_table();
};

// Função assíncrona para enviar dados ao servidor
async function submit_data() {
    let selected_table = table_options.value; // Obtém a tabela selecionada
    let fields = table_maps[selected_table].fields; // Obtém os campos da tabela selecionada
    let data = {};

    // Preenche o objeto data com os valores dos campos do formulário
    fields.forEach(field => {
        data[field.toLowerCase()] = document.getElementById(field).value;
    });

    // let api_url = `http://andromeda.lasdpc.icmc.usp.br:7031/${selected_table}/`;
    let api_url = `http://${url}:${port}/${selected_table}/`;

    try {
        // Envia os dados para a API usando uma requisição POST
        let response = await fetch(api_url, {
            method: 'POST',
            body: JSON.stringify(data),
            headers: {
                "Content-Type": "application/json"
            }
        });

        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }

        let result = await response.json();
        console.log('Server response:', result);
        alert('Dados enviados com sucesso!');
        data["table"] = selected_table; // Adiciona a tabela aos dados
        send_ws(data); // Envia os dados via WebSocket
    } catch (error) {
        console.error('Failed to send data:', error);
        alert('Erro ao enviar dados.');
    }
}

// Função para enviar dados via WebSocket
function send_ws(data) {
    ws.send(JSON.stringify(data));
}