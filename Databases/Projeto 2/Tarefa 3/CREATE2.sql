CREATE TABLE Propriedade (
    Nome VARCHAR(255) NOT NULL,
    Sobrenome VARCHAR(255) NOT NULL,
    Endereco VARCHAR(255) NOT NULL,
    MaxHospedes INT NOT NULL,
    Forma VARCHAR(100),
    Uso VARCHAR(100),
    MaxNoites INT,
    PrecoNoite DECIMAL(10, 2),
    TaxaDeLimpeza DECIMAL(10, 2),
    MinNoites INT,
    Regras TEXT,
    Comodidades TEXT,
    EhCasa BOOLEAN,
    EhQuarto BOOLEAN,
    Cidade VARCHAR(100),
    Estado VARCHAR(100),
    Pais VARCHAR(100),
    DataInicial DATE,
    DataFinal DATE,
    NumeroConta VARCHAR(50),

    PRIMARY KEY (Nome, Sobrenome)
);

CREATE TABLE Usuario (
    Nome VARCHAR(255) NOT NULL,
    Sobrenome VARCHAR(255) NOT NULL,
    Telefone VARCHAR(20) NOT NULL,
    DataNasc DATE,
    Endereco VARCHAR(255),
    Sexo CHAR(1),
    Email VARCHAR(255),
    Senha VARCHAR(255),
    EProprietario BOOLEAN,
    TipoConta VARCHAR(100),
    NumeroRoteamento VARCHAR(50),

    PRIMARY KEY (Nome, Sobrenome, Telefone)
);

CREATE TABLE Locacao (
    Id INT AUTO_INCREMENT,
    NomeU VARCHAR(255) NOT NULL,
    SobrenomeU VARCHAR(255) NOT NULL,
    TelefoneU VARCHAR(20) NOT NULL,
    NomeP VARCHAR(255) NOT NULL,
    EnderecoP VARCHAR(255) NOT NULL,
    PrecoEstadia DECIMAL(10, 2),
    NumeroHospede INT,
    CodigoPromocional VARCHAR(50),
    ImpostoPago DECIMAL(10, 2),
    PrecoTotal DECIMAL(10, 2),
    Desconto DECIMAL(10, 2),
    Status VARCHAR(50),
    DataReserva DATE,
    Checkin DATE,
    Checkout DATE,
    IdAvaliacao INT,
    PRIMARY KEY (Id),
    FOREIGN KEY (NomeU, SobrenomeU, TelefoneU) REFERENCES Usuario(Nome, Sobrenome, Telefone),
    FOREIGN KEY (NomeP, EnderecoP) REFERENCES Propriedade(Nome, Endereco)
);

CREATE TABLE Avaliacao (
    Id INT AUTO_INCREMENT,
    NomeU VARCHAR(255) NOT NULL,
    SobrenomeU VARCHAR(255) NOT NULL,
    TelefoneU VARCHAR(20) NOT NULL,
    NomeP VARCHAR(255) NOT NULL,
    EnderecoP VARCHAR(255) NOT NULL,
    NotaComunicacao DECIMAL(3, 2),
    NotaLocalizacao DECIMAL(3, 2),
    NotaPreco DECIMAL(3, 2),
    NotaLimpeza DECIMAL(3, 2),
    Mensagem TEXT,
    PRIMARY KEY (Id),
    FOREIGN KEY (NomeU, SobrenomeU, TelefoneU) REFERENCES Usuario(Nome, Sobrenome, Telefone),
    FOREIGN KEY (NomeP, EnderecoP) REFERENCES Propriedade(Nome, Endereco)
);

CREATE TABLE PropriedadeRegra (
    NomeP VARCHAR(255) NOT NULL,
    EnderecoP VARCHAR(255) NOT NULL,
    Regra TEXT NOT NULL,
    PRIMARY KEY (NomeP, EnderecoP, Regra),
    FOREIGN KEY (NomeP, EnderecoP) REFERENCES Propriedade(Nome, Endereco)
);

CREATE TABLE PropriedadeComodidade (
    NomeP VARCHAR(255) NOT NULL,
    EnderecoP VARCHAR(255) NOT NULL,
    Comodidade TEXT NOT NULL,
    PRIMARY KEY (NomeP, EnderecoP, Comodidade),
    FOREIGN KEY (NomeP, EnderecoP) REFERENCES Propriedade(Nome, Endereco)
);

CREATE TABLE PontoDeInteresse (
    ID INT AUTO_INCREMENT,
    Nome VARCHAR(255) NOT NULL,
    Descricao TEXT,
    Cidade VARCHAR(100),
    Estado VARCHAR(100),
    Pais VARCHAR(100),
    PRIMARY KEY (ID)
);

CREATE TABLE Foto (
    Nome VARCHAR(255) NOT NULL,
    Conteudo BLOB NOT NULL,
    IdAvaliacao INT,
    PRIMARY KEY (Nome),
    FOREIGN KEY (IdAvaliacao) REFERENCES Avaliacao(Id)
);

CREATE TABLE Casa (
    Id INT AUTO_INCREMENT,
    NomeP VARCHAR(255) NOT NULL,
    EnderecoP VARCHAR(255) NOT NULL,
    NumeroBanheiros INT,
    NumeroQuartos INT,
    PRIMARY KEY (Id),
    FOREIGN KEY (NomeP, EnderecoP) REFERENCES Propriedade(Nome, Endereco)
);

CREATE TABLE Quarto (
    Id INT AUTO_INCREMENT,
    NomeP VARCHAR(255) NOT NULL,
    EnderecoP VARCHAR(255) NOT NULL,
    Tipo VARCHAR(100),
    QtdCamas INT,
    PRIMARY KEY (Id),
    FOREIGN KEY (NomeP, EnderecoP) REFERENCES Propriedade(Nome, Endereco)
);