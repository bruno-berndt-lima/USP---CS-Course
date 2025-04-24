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
        const altered = JSON.parse(e.data);
        if (altered["table"] === table_options.value) {
            query_data();
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
    constructor(id, name, fields, fixed_fields) {
        this.id = id;
        this.fields = fields;

        //Campos não modificáveis(chave primaria ou chaves estrangeiras)
        this.fixed_fields = fixed_fields;

        table_options.innerHTML += `<option value="${id}" ${!default_selected ? "selected" : ""}>${name}</option>`;

        this.data_format = `<tr>`;
        for (let field of fields) {
            this.data_format += `\n<th>${field}</th>`;
        }
        this.data_format += "</tr>";

        if (!default_selected) this.setTable();
        default_selected = true;
    }

    setTable() {
        document.getElementById("data").innerHTML = this.data_format;
    }
}

// Mapeamento de tabelas com seus campos
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

// Função para limpar o formulário
function clear_form() {
    form_container.innerHTML = '';
    document.getElementById("update_form").classList.remove("active");
}

// Função para trocar a tabela selecionada
function change_table() {
    table_maps[table_options.value].setTable();
    clear_form();
}

// Função assíncrona para consultar dados do servidor
async function query_data() {
    let selected_table = table_options.value; // Obtém a tabela selecionada
    let filter_value = document.getElementById("filters").value; // Obtém o valor do filtro

    let api_url = `http://${url}:${port}/${selected_table}/${encodeURIComponent(filter_value)}`;

    try {
        // Faz uma requisição GET para a API
        let response = await fetch(api_url);

        if (!response.ok) {
            throw new Error(`Error: ${response.status} ${response.statusText}`);
        }

        let data = await response.json();
        update_table(data, selected_table); // Atualiza a tabela com os dados recebidos

    } catch (error) {
        console.error('Failed to fetch data:', error);
    }
}

// Função para atualizar a tabela exibida com novos dados
function update_table(data, selected_table) {
    let table = document.getElementById("data"); // Obtém o elemento da tabela no DOM
    table.innerHTML = "";

    let fields = table_maps[selected_table].fields; // Obtém os campos da tabela selecionada

    let header_row = "<tr>";
    fields.forEach(field => {
        header_row += `<th>${field}</th>`; // Adiciona cada campo como um cabeçalho de coluna
    });
    header_row += "</tr>";
    table.innerHTML += header_row; // Adiciona a linha do cabeçalho à tabela

    // Cria uma linha para cada registro de dados
    data.forEach(row => {
        let row_html = "<tr>";
        fields.forEach(field => {
            row_html += `<td>${row[field.toLowerCase()]}</td>`; // Adiciona o valor do campo na célula da tabela
        });
        row_html += `<td><button onclick='populate_form(${JSON.stringify(row)})'>Editar</button></td>`; // Adiciona o botão de edição
        row_html += "</tr>";
        table.innerHTML += row_html;
    });
}

// Função para preencher o formulário com os dados da linha selecionada
function populate_form(row) {
    let selected_table = table_options.value;
    let table_option = table_maps[selected_table];
    let fields = table_option.fields;

    form_container.innerHTML = '';
    fields.forEach(field => {
        let is_fixed_field = table_option.fixed_fields.includes(field);
        form_container.innerHTML += `<label for="${field}">${field}</label>
                                     <input type="text" id="${field}" name="${field}" value="${row[field.toLowerCase()]}" ${is_fixed_field ? "disabled" : ""}><br/>`;
    });

    document.getElementById("update_form").classList.add("active");
}

// Função assíncrona para atualizar os dados no servidor
async function update_data() {
    let selected_table = table_options.value;
    let fields = table_maps[selected_table].fields;
    let data = {};

    fields.forEach(field => {
        let value = document.getElementById(field).value;
        data[field.toLowerCase()] = value;
    });

    try {
        let response = await fetch(`http://${url}:${port}/${selected_table}/`, {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(data)
        });

        if (!response.ok) {
            throw new Error(`Error: ${response.status} ${response.statusText}`);
        }

        let result = await response.json();
        data["table"] = selected_table;
        send_ws(data);
        alert('Dados atualizados com sucesso!');
        clear_form();
        query_data();
    } catch (error) {
        console.error('Failed to update data:', error);
        alert('Falha ao atualizar dados.');
    }
}

function send_ws(data) {
    ws.send(JSON.stringify(data));
}

// Popula opções de tabela e define a tabela padrão
document.addEventListener("DOMContentLoaded", () => {
    Object.keys(table_maps).forEach(key => {
        let tableOption = table_maps[key];
        if (!default_selected) {
            tableOption.setTable();
            default_selected = true;
        }
    });
});

// Adiciona listener ao formulário de atualização
document.getElementById("update_form").addEventListener("submit", (event) => {
    event.preventDefault();
    update_data();
});
