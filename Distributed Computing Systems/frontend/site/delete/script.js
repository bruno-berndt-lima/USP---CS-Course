const url = "localhost";
// const url = "andromeda.lasdpc.icmc.usp.br";
const port = 7031;

// Cria uma conexão WebSocket com o servidor
const ws = new WebSocket(`ws://${url}:${port}/websocket`);

// Evento acionado quando a conexão WebSocket é aberta
ws.addEventListener("open", () => {
    console.log("We are connected!");
});

// Evento acionado quando uma mensagem é recebida via WebSocket
ws.addEventListener("message", e => {
    try {
        console.log(e)
        const altered = JSON.parse(e.data); // Converte a mensagem recebida de JSON para objeto
        console.log(altered);
        if (altered["table"] === table_options.value) { // Verifica se a tabela alterada é a tabela selecionada
            query_data(); // Atualiza os dados da tabela
        }
    } catch (error) {
        console.log(error);
    }
});

// Variável para controlar a seleção padrão
let default_selected = false;

// Obtém os elementos do DOM
let table_options = document.getElementById("table_options");
let form_container = document.getElementById("form_container");

// Classe para representar uma opção de tabela
class TableOption {
    constructor(id, name, fields, primaryKey) {
        this.id = id;
        this.fields = fields;
        this.primaryKey = primaryKey;
        table_options.innerHTML += `<option value="${id}" ${!default_selected ? "selected" : ""}>${name}</option>`;

        if (!default_selected) this.setTable();
        default_selected = true;
    }

    setTable() {
        this.generateFormFields();
    }

    generateFormFields() {
        form_container.innerHTML = ''; // Limpa os campos anteriores
        for (let field of this.fields) {
            let input_html = `<label for="${field}">${field}</label><input type="text" id="${field}" name="${field}"><br/>`;
            form_container.innerHTML += input_html;
        }
    }
}

// Mapeamento de tabelas
// Formato: TableOption("nome da tabela do banco de dados", "nome da tabela gerada no html", "colunas da tabela", "chave(s) primária(s)")
let table_maps = {
    remedio: new TableOption("remedio", "Remédios", ["Nome", "Tarja"], ["Nome"]),
    receita: new TableOption("receita", "Receitas", ["ID", "Medico", "Paciente", "Posto"], ["ID"]),
    receitaremedio: new TableOption("receitaremedio", "Receitas Remédios", ["Receita", "Remedio", "Prontidao"], ["Receita", "Remedio"]),
    usuario: new TableOption("usuario", "Usuários", ["CPF", "Email", "Senha"], ["CPF"]),
    farmaceutico: new TableOption("farmaceutico", "Farmacêuticos", ["Usuario", "Posto"], ["Usuario"]),
    medico: new TableOption("medico", "Médicos", ["Usuario", "Posto"], ["Usuario"]),
    paciente: new TableOption("paciente", "Pacientes", ["Usuario", "Convenio", "Posto"], ["Usuario"]),
    regiao: new TableOption("regiao", "Regiões", ["ID", "Nome"], ["ID"]),
    tarja: new TableOption("tarja", "Tarjas", ["Nome", "Retencao"], ["Nome"]),
    posto: new TableOption("posto", "Postos", ["ID", "Nome", "Regiao"], ["ID"]),
    estoqueregional: new TableOption("estoqueregional", "Estoques Regionais", ["ID", "Regiao"], ["ID"]),
    estoqueregionalremedio: new TableOption("estoqueregionalremedio", "Estoque Regional Remédios", ["EstoqueRegional", "Remedio", "Quantidade"], ["EstoqueRegional", "Remedio"]),
    estoquelocal: new TableOption("estoquelocal", "Estoques Locais", ["ID", "Regiao"], ["ID"]),
    estoquelocalremedio: new TableOption("estoquelocalremedio", "Estoque Local Remédios", ["EstoqueLocal", "Remedio", "Quantidade"], ["EstoqueLocal", "Remedio"])
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
    let selected_table = table_options.value;   // Obtém a tabela selecionada
    let fields = table_maps[selected_table].fields; // Obtém os campos da tabela selecionada
    let data = {};

    // Preenche o objeto data com os valores dos campos do formulário
    fields.forEach(field => {
        data[field.toLowerCase()] = document.getElementById(field).value;
    });
    console.log(selected_table)

    // URL da API para enviar os dados
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

        let result = await response.json(); // Converte a resposta para JSON
        console.log('Server response:', result);
        alert('Dados enviados com sucesso!');
        data["selected_table"] = selected_table; // Adiciona a tabela selecionada aos dados
        send_ws(data);  // Envia os dados via WebSocket
    } catch (error) {
        console.error('Failed to send data:', error);
        alert('Erro ao enviar dados.');
    }
}

// Função para enviar dados via WebSocket
function send_ws(data) {
    ws.send(JSON.stringify(data));
}

// Função assíncrona para consultar dados do servidor
async function query_data() {
    let selected_table = table_options.value;   // Obtém a tabela selecionada
    let filter_value = document.getElementById("filters").value;    // Obtém o valor do filtro
    let api_url = `http://${url}:${port}/${selected_table}/${encodeURIComponent(filter_value)}`;

    try {
        // Faz uma requisição GET para a API
        let response = await fetch(api_url);

        if (!response.ok) {
            throw new Error(`Error: ${response.status} ${response.statusText}`);
        }

        let data = await response.json();
        update_table(data, selected_table);
    } catch (error) {
        console.error('Failed to fetch data:', error);
    }
}

// Função para atualizar a tabela exibida com novos dados
function update_table(data, selected_table) {
    let table = document.getElementById("data");
    table.innerHTML = "";

    let fields = table_maps[selected_table].fields;

    // Cria a linha do cabeçalho da tabela
    let header_row = "<tr>";
    fields.forEach(field => {
        header_row += `<th>${field}</th>`;  // Adiciona cada campo como um cabeçalho de coluna
    });
    header_row += "<th>Ações</th></tr>";    // Adiciona a coluna de ações
    table.innerHTML += header_row;  // Adiciona a linha do cabeçalho à tabela

    // Cria uma linha para cada registro de dados
    data.forEach(row => {
        let row_html = "<tr>";
        fields.forEach(field => {
            if (row[field.toLowerCase()] !== undefined) {
                row_html += `<td>${row[field.toLowerCase()]}</td>`; // Adiciona o valor do campo na célula da tabela
            } else {
                row_html += `<td></td>`;   // Adiciona uma célula vazia se o campo for indefinido
            }
        });

        // Gera a lista de chaves primárias com keyÇvalue para a função de delete
        let primaryKeys = table_maps[selected_table].primaryKey.map(key => {
            return { key: key.toLowerCase(), value: row[key.toLowerCase()] };
        });

        let primaryKeysJson = JSON.stringify(primaryKeys);

        row_html += `<td><button class="delete" onclick='delete_data("${selected_table}", ${primaryKeysJson})'>Delete</button></td>`;
        row_html += "</tr>";
        table.innerHTML += row_html;
    });
}

// Função assíncrona para deletar dados do servidor
async function delete_data(table, primaryKeys) {
    let api_url = `http://${url}:${port}/${table}/`;

    let data = {};
    primaryKeys.forEach(pair => {
        data[pair.key] = (pair.key === 'id') ? parseInt(pair.value, 10) : pair.value;
    });

    try {
        // Envia os dados para a API usando uma requisição DELETE
        let response = await fetch(api_url, {
            method: 'DELETE',
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
        alert('Dados deletados com sucesso!');
        data["table"] = table;  // Adiciona a tabela aos dados
        send_ws(data);  // Envia os dados via WebSocket
    } catch (error) {
        console.error('Failed to delete data:', error);
        alert('Erro ao deletar dados.');
    }
}
