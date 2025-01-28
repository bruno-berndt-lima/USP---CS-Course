CREATE TABLE Regra (
    ID_Regra            SERIAL NOT NULL,
    Nome                VARCHAR(50),
    Descricao           TEXT,
        CONSTRAINT PK_REGRA PRIMARY KEY(ID_Regra)
);

CREATE TABLE Comodidade (
    ID_Comodidade       SERIAL NOT NULL,
    Nome                VARCHAR(50),
    Descricao           TEXT,
        CONSTRAINT PK_COMODIDADE PRIMARY KEY(ID_Comodidade)
);

CREATE TABLE Localizacao (
    Cidade              VARCHAR(40) NOT NULL,
    Estado              VARCHAR(40) NOT NULL,
    Pais                VARCHAR(40) NOT NULL,
    Bairro              VARCHAR(40),
        CONSTRAINT PK_LOCALIZACAO PRIMARY KEY(Cidade, Estado, Pais)
);

CREATE TABLE Ponto_Interesse (
    ID_PontoInteresse   SERIAL NOT NULL,

    Cidade              VARCHAR(40) NOT NULL,
    Estado              VARCHAR(40) NOT NULL,
    Pais                VARCHAR(40) NOT NULL,

    Nome                VARCHAR(100),
    Descricao           TEXT,
    
        CONSTRAINT PK_PONTO_INTERESSE PRIMARY KEY(ID_PontoInteresse, Cidade, Estado, Pais),
        CONSTRAINT FK_PONTO_INTERESSE FOREIGN KEY (Cidade, Estado, Pais)
            REFERENCES Localizacao(Cidade, Estado, Pais)
);

CREATE TABLE Usuario (
    Nome                VARCHAR(50) NOT NULL,
    Sobrenome           VARCHAR(50) NOT NULL,
    Telefone            VARCHAR(30) NOT NULL,
    Tipo                VARCHAR(15),
    Data_Nasc           DATE,
    Endereco            VARCHAR(70),
    Sexo                CHAR(1),
    Email               VARCHAR(40),
    Senha               VARCHAR(256),

    Cidade              VARCHAR(40),
    Estado              VARCHAR(40),
    Pais                VARCHAR(40),

        CONSTRAINT PK_USUARIO PRIMARY KEY(Nome, Sobrenome, Telefone),
        CONSTRAINT FK_USUARIO FOREIGN KEY (Cidade, Estado, Pais)
            REFERENCES Localizacao(Cidade, Estado, Pais)
);

CREATE TABLE Conta_Bancaria (
    Nome_Anf            VARCHAR(50) NOT NULL,
    Sobrenome_Anf       VARCHAR(50) NOT NULL,
    Tel_Anf             VARCHAR(30) NOT NULL,

    Numero_Conta        VARCHAR(25) NOT NULL,

    Tipo                VARCHAR(15),
    Numero_Roteamento   VARCHAR(9),

        CONSTRAINT PK_CONTA_BANCARIA PRIMARY KEY(Nome_Anf, Sobrenome_Anf, Tel_Anf, Numero_Conta),
        CONSTRAINT FK_CONTA_BANCARIA FOREIGN KEY (Nome_Anf, Sobrenome_Anf, Tel_Anf)
            REFERENCES Usuario(Nome, Sobrenome, Telefone)
);

CREATE TABLE Locacao (
    ID_Locacao          SERIAL NOT NULL,
    Preco_Estadia       MONEY,
    Numero_Hospedes     DECIMAL(2),
    Codigo_Promocional  VARCHAR(15),
    Imposto_Pago        MONEY,
    Preco_Total         MONEY,
    Desconto            MONEY,

        CONSTRAINT PK_LOCACAO PRIMARY KEY(ID_Locacao)
);

CREATE TABLE Propriedade (
    Nome                VARCHAR(50) NOT NULL,
    Endereco            VARCHAR(70) NOT NULL,

    Tipo                VARCHAR(10),
    Forma_Uso           VARCHAR(20),
    Preco_Noite         MONEY,
    Numero_Banheiros    DECIMAL(2),
    Numero_Quartos      DECIMAL(2),
    Min_Noites          DECIMAL(2),
    Max_Noites          DECIMAL(2),
    Taxa_Limpeza        MONEY,
    Maximo_Hospedes     DECIMAL(2),
    
    Nome_Anf            VARCHAR(50),
    Sobrenome_Anf       VARCHAR(50),
    Tel_Anf             VARCHAR(30),

    Cidade              VARCHAR(40),
    Estado              VARCHAR(40),
    Pais                VARCHAR(40),

    Data_Inicial        TIMESTAMP,
    Data_Final          TIMESTAMP,

        CONSTRAINT PK_PROPRIEDADE PRIMARY KEY(Nome, Endereco),
        CONSTRAINT FK1_PROPRIEDADE FOREIGN KEY(Nome_Anf, Sobrenome_Anf, Tel_Anf)
            REFERENCES Usuario(Nome, Sobrenome, Telefone),
        CONSTRAINT FK2_PROPRIEDADE FOREIGN KEY(Cidade, Estado, Pais)
            REFERENCES Localizacao(Cidade, Estado, Pais)
);

CREATE TABLE Propriedade_Regra (
    Nome_Prop           VARCHAR(50) NOT NULL,
    Endereco_Prop       VARCHAR(70) NOT NULL,

    Regra               SERIAL NOT NULL,

        CONSTRAINT PK_PROPRIEDADE_REGRA PRIMARY KEY(Nome_Prop, Endereco_Prop, Regra),
        CONSTRAINT FK1_PROPRIEDADE_REGRA FOREIGN KEY(Nome_Prop, Endereco_Prop)
            REFERENCES Propriedade(Nome, Endereco),
        CONSTRAINT FK2_PROPRIEDADE_REGRA FOREIGN KEY(Regra)
            REFERENCES Regra(ID_Regra)
);

CREATE TABLE Propriedade_Comodidade (
    Nome_Prop           VARCHAR(50) NOT NULL,
    Endereco_Prop       VARCHAR(70) NOT NULL,

    Comodidade          SERIAL NOT NULL,

    Tipo                VARCHAR(40),
    Quantidade          DECIMAL(2),

        CONSTRAINT PK_PROPRIEDADE_COMODIDADE PRIMARY KEY(Nome_Prop, Endereco_Prop, Comodidade),
        CONSTRAINT FK1_PROPRIEDADE_COMODIDADE FOREIGN KEY(Nome_Prop, Endereco_Prop)
            REFERENCES Propriedade(Nome, Endereco),
        CONSTRAINT FK2_PROPRIEDADE_COMODIDADE FOREIGN KEY(Comodidade)
            REFERENCES Comodidade(ID_Comodidade)
);

CREATE TABLE Reserva (
    Nome_Propriedade        VARCHAR(50) NOT NULL,
    Endereco_Propriedade    VARCHAR(70) NOT NULL,

    Nome_Locatario          VARCHAR(50) NOT NULL,
    Sobrenome_Locatario     VARCHAR(50) NOT NULL,
    Tel_Locatario           VARCHAR(30) NOT NULL,

    Locacao                 SERIAL NOT NULL,

    Data_Reserva            TIMESTAMP,
    Check_In                TIMESTAMP,
    Check_Out               TIMESTAMP,
    Status                  VARCHAR(30),
    

        CONSTRAINT PK_RESERVA PRIMARY KEY(Nome_Propriedade, Endereco_Propriedade, Nome_Locatario, Sobrenome_Locatario, Tel_Locatario, Locacao),
        CONSTRAINT FK1_RESERVA FOREIGN KEY(Nome_Propriedade, Endereco_Propriedade)
            REFERENCES Propriedade(Nome, Endereco),
        CONSTRAINT FK2_RESERVA FOREIGN KEY(Nome_Locatario, Sobrenome_Locatario, Tel_Locatario)
            REFERENCES Usuario(Nome, Sobrenome, Telefone),
        CONSTRAINT FK3_RESERVA FOREIGN KEY(Locacao)
            REFERENCES Locacao(ID_Locacao)
);

CREATE TABLE Avaliacao (
    ID_Avaliacao            SERIAL NOT NULL,
    Timestamp               TIMESTAMP,
    Nota_Limpeza            DECIMAL(1),
    Nota_Comunicacao        DECIMAL(1),
    Nota_Localizacao        DECIMAL(1),
    Nota_Preco              DECIMAL(1),
    Mensagem                TEXT,

        CONSTRAINT PK_AVALIACAO PRIMARY KEY(ID_Avaliacao)
);

CREATE TABLE Fotos (
    Nome                    VARCHAR(50) NOT NULL,

    Avaliacao               SERIAL NOT NULL,

    Conteudo                VARCHAR(200),

        CONSTRAINT PK_FOTOS PRIMARY KEY(Nome, Avaliacao),
        CONSTRAINT FK_FOTOS FOREIGN KEY(Avaliacao)
            REFERENCES Avaliacao(ID_Avaliacao)
);

CREATE TABLE Fazer_Avaliacao (
    Nome_Locatario      VARCHAR(50) NOT NULL,
    Sobrenome_Locatario VARCHAR(50) NOT NULL,
    Tel_Locatario       VARCHAR(30) NOT NULL,

    Avaliacao               SERIAL NOT NULL,

    Nome_Propriedade     VARCHAR(50) NOT NULL,
    Endereco_Propriedade VARCHAR(70) NOT NULL,

    CONSTRAINT PK_FAZER_AVALIACAO PRIMARY KEY(Nome_Locatario, Sobrenome_Locatario, Tel_Locatario, Avaliacao,
    Nome_Propriedade, Endereco_Propriedade),
    CONSTRAINT FK1_FAZER_AVALIACAO FOREIGN KEY(Nome_Locatario, Sobrenome_Locatario, Tel_Locatario)
        REFERENCES Usuario(Nome, Sobrenome, Telefone),
    CONSTRAINT FK2_FAZER_AVALIACAO FOREIGN KEY(Avaliacao)
        REFERENCES Avaliacao(ID_Avaliacao),
    CONSTRAINT FK3_FAZER_AVALIACAO FOREIGN KEY(Nome_Propriedade, Endereco_Propriedade)
        REFERENCES Propriedade(Nome, Endereco)
);
