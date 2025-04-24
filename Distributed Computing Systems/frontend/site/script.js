// const url = "andromeda.lasdpc.icmc.usp.br";
const url = "localhost";
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
        const altered = JSON.parse(e.data);
        console.log(altered);
        if (altered["table"] === table_options.value) {
            query_data();
        }
    } catch (error) {
        console.log(error);
    }
});

// Variável para controlar a seleção padrão
let default_selected = false

// Obtém o elemento do DOM para as opções de tabela
let table_options = document.getElementById("table_options")

// Classe para representar uma opção de tabela
class table_option {
    constructor(id, name, fields) {
        this.id = id
        this.fields = fields

        table_options.innerHTML += `<option value="${id}" ${!default_selected ? "selected" : ""}>${name}</option>`

        this.data_format = `<tr>`
        for (let field of fields) {
            this.data_format += `\n<th>${field}</th>`
        }
        this.data_format += "</tr>"

        if (!default_selected) this.set_table()
        default_selected = true
    }

    set_table() {
        document.getElementById("data").innerHTML = this.data_format
    }
}

// Mapeamento de tabelas com seus campos
let table_maps = {}
table_maps["remedio"] = new table_option("remedio", "Remédios", ["Nome", "Tarja"])
table_maps["receita"] = new table_option("receita", "Receitas", ["ID", "Medico", "Paciente", "Posto"])
table_maps["receitaremedio"] = new table_option("receitaremedio", "Receitas Remédios", ["Receita", "Remedio", "Prontidao"])
table_maps["usuario"] = new table_option("usuario", "Usuários", ["CPF", "Email", "Senha"])
table_maps["farmaceutico"] = new table_option("farmaceutico", "Farmacêuticos", ["Usuario", "Posto"])
table_maps["medico"] = new table_option("medico", "Médicos", ["Usuario", "Posto"])
table_maps["paciente"] = new table_option("paciente", "Pacientes", ["Usuario", "Convenio", "Posto"])
table_maps["regiao"] = new table_option("regiao", "Regiões", ["ID", "Nome"])
table_maps["tarja"] = new table_option("tarja", "Tarjas", ["Nome", "Retencao"])
table_maps["posto"] = new table_option("posto", "Postos", ["ID", "Nome", "Regiao"])
table_maps["estoqueregional"] = new table_option("estoqueregional", "Estoques Regionais", ["ID", "Regiao"])
table_maps["estoqueregionalremedio"] = new table_option("estoqueregionalremedio", "Estoque Regional Remédios", ["EstoqueRegional", "Remedio", "Quantidade"])
table_maps["estoquelocal"] = new table_option("estoquelocal", "Estoques Locais", ["ID", "Regiao"])
table_maps["estoquelocalremedio"] = new table_option("estoquelocalremedio", "Estoque Local Remédios", ["EstoqueLocal", "Remedio", "Quantidade"])

// Função para trocar a tabela selecionada
function change_table() {
    table_maps[table_options.value].set_table()
}

// Função assíncrona para consultar dados do servidor
async function query_data() {
    let selected_table = table_options.value;     // Obtém a tabela selecionada

    let filter_value = document.getElementById("filters").value;        // Obtém o valor do filtro

    // let api_url = `http://andromeda.lasdpc.icmc.usp.br:7031/${selected_table}/${encodeURIComponent(filter_value)}`;
    let api_url = `http://${url}:${port}/${selected_table}/${encodeURIComponent(filter_value)}`;

    try {
        // Faz uma requisição GET para a API
        let response = await fetch(api_url);

        if (!response.ok) {
            throw new Error(`Error: ${response.status} ${response.statusText}`);
        }

        let data = await response.json();

        // Atualiza a tabela com os dados recebidos
        update_table(data, selected_table);
    } catch (error) {
        console.error('Failed to fetch data:', error);
    }
}

// Função para atualizar a tabela com os dados recebidos
function update_table(data, selected_table) {
    // Limpa o conteúdo atual da tabela
    let table = document.getElementById("data");
    table.innerHTML = "";

    // Obtém os campos do cabeçalho da tabela
    let fields = table_maps[selected_table].fields;

    // Cria a linha do cabeçalho da tabela
    let header_row = "<tr>";
    fields.forEach(field => {
        header_row += `<th>${field}</th>`;
    });
    header_row += "</tr>";
    table.innerHTML += header_row;

    // Cria uma linha para cada registro de dados
    data.forEach(row => {
        let row_html = "<tr>";
        fields.forEach(field => {
            row_html += `<td>${row[field.toLowerCase()]}</td>`;
        });
        row_html += "</tr>";
        table.innerHTML += row_html;
    });
}