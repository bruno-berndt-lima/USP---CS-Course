# gsdgrad17

Projeto para disciplina de Sistemas Computacionais Distribuídos. Consiste em um sistema de gerência de estoques de remédios distribuídos gratuitamente pelo Sistema Único de Saúde (SUS) nos postos de saúde.

O sistema permitirá o monitoramento contínuo e remoto dos estoques locais e regionais, possibilitando que farmacêuticos, médicos e pacientes consultem a disponibilidade de remédios em sua proximidade.

## Ferramentas utilizadas

- `FastAPI`: framework em Python para criação de uma API RESTful
- `nginx`: servidor web utilizado para proxy reverso e balanceamento de carga entre dois servidores websocket
- `node.js (WebSocket + kafkajs)`: utilizado para criação do servidor WebSocket que faz a produção e consumação de mensagens Kafka
- `Kafka`: utilizado para o sistema de mensagens
- `PostgreSQL`: utilizado para o banco de dados
- `Spark`: utilizado como intermediário entre o FastAPI e o PostgreSQL
- `Grafana`: utilizado para o monitoramento do sistema
- `Prometheus`: utilizado para coletar os dados para o grafana. Os dados são provenientes das seguintes ferramentas:
  - `cAdvisor`: Informações sobre a utilização de recursos e medição de performance de cada container
  - `Node exporter`: Monitoramento do sistema host
  - `Postgres exporter`: Exporta métricas do banco de dados
  - `Telegraf`: Coleta dados e mensagens de log do nginx e redireciona esses dados para o prometheus
  - `FastAPI instrumentator`: Coleta de informações sobre as requisições feita a API
- `JMeter`: utilizado para fazer testes de carga no sistema

## Como rodar o projeto

Atualmente é possível fazer o teste da aplicação acessando o [site](http://andromeda.lasdpc.icmc.usp.br:7031/index.html)

Porém caso queira testar a aplicação de maneira local, siga os seguintes passos:

Clone o repositório utilizando o comando

```bash
git clone https://github.com/ICMC-SSC0904-2024/gsdgrad17.git
```

Para testar o sistema localmente é necessário o docker instalado na máquina, onde o docker-compose deve ser de uma versão superior ou igual à 2.20.3. Para rodar o programa abra um terminal e acesse a pasta clonada no passo anterior e utilize o comando:

```bash
docker-compose up
```

Caso queira rodar o código em um servidor diferente de localhost, é necessário alterar todos os arquivos `.js` localizados na pasta `/frontend/site/` e nas pastas internas ao referido diretório. Altere apenas as constantes `url` e `port` localizadas no início de todos os códigos. É importante que `port` possua o mesmo valor que a porta exposta para o nginx no arquivo `frontend/docker-compose.yaml`

Após a execução desse comando, espere que apareça um log no terminal do serviço kafka1 e kafka2. Estes logs representam que os dois serviços estão ativos e é possível utilizar o sistema. Para isso, acesse o endereço web http://localhost:7031 ou o especificado pelas constantes. Neste endereço deve aparecer a tela inicial do sistema (busca dos dados). A navegação no sistema é baseada em selecionar tabelas e clicar no botão de busca. Em hipótese alguma deve ser feita uma busca na tabela de remédios com parâmetros vazios, isso fará com que a página quebre por falta de memória.

Para acessar o monitoramento da aplicação acesse o endereço web http://localhost:5031 ou o especificado pelas constantes. Em seguida utilize o usuário `admin` e a senha `admin` e verifique o uso de cpu, memória e rede através dos dashboards.

## Parâmetros das buscas

Ao acessar o site, há uma opção de filtros de busca. Estão disponíveis as seguintes opções de acordo com as tabelas:

- Remédio: Nome
- Estoque Local: ID
- Estoque Local Remédios: ID do estoque
- Estoque Regional: ID
- Estoque Regional Remédios: ID do estoque
- Famacêutico: CPF
- Médico: CPF
- Paciente: CPF
- Posto: ID
- Receita: ID
- Receita Remédios: ID da receita
- Região: ID
- Tarja: Nome
- Usuário: CPF
