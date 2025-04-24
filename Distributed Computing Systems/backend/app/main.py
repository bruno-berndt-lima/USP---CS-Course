from typing import Union

from utils.schema import *

from fastapi import FastAPI, HTTPException

from pyspark.sql import SparkSession, DataFrame
from pyspark.sql.types import *

from prometheus_fastapi_instrumentator import Instrumentator

import json

from utils.schema import *


# Cria uma instância de SparkSession com várias configurações
#   .master      -> Define o master node para o cluster Spark. Neste caso, está especificando o endereço do master node
#   .appName     -> Define o nome da aplicação Spark. Este nome aparecerá na interface de usuário do Spark
#   .config      -> Adiciona um arquivo JAR à sessão Spark. Neste caso, o arquivo JAR é um driver para conectar ao PostgreSQL
#   .getOrCreate -> Cria a sessão Spark com as configurações fornecidas
#
spark = SparkSession.Builder()\
        .master('spark://spark:7077')\
        .appName('teste')\
        .config("spark.jars", "/code/app/jars/postgresql-42.7.3.jar")\
        .getOrCreate()\

# Define a URL de conexão JDBC para um banco de dados PostgreSQL
url = "jdbc:postgresql://db:5432/scd"

# Define um dicionário com as propriedades de conexão ao banco de dados
properties = {
    "user": "scd",
    "password": "scd",
    "driver": "org.postgresql.Driver"
}

# Define o nome da tabela no banco de dados que será utilizada
table_name = "teste"

# Cria uma instância da aplicação FastAPI
app = FastAPI()

# Instrumenta a aplicação FastAPI para coletar métricas e as expõe
Instrumentator().instrument(app).expose(app)

# Como ativo e ativoremédio não são inseridos, alterados ou deletados
# foi criado somente as rotas para busca destes
@app.get("/ativo/")
def read_ativo():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "ativo")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/ativoremedio/")
def read_ativoremedio():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "ativoremedio")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

# Criação das rotas para leitura, inserção, deleção e alteração da tabela estoquelocal
@app.get("/estoquelocal/")
def read_estoquelocal():
    # Lê os dados da tabela 'estoquelocal' do banco de dados PostgreSQL
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "estoquelocal")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    # Converte o DataFrame em JSON e retorna como uma lista de dicionários
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/estoquelocal/{id}")
def read_estoquelocal(id: int):
    try:
        # Executa uma consulta SQL para obter o registro com o ID fornecido
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM estoquelocal WHERE ID = {id}")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/estoquelocal/")
def add_estoquelocal(data: estoquelocalData):
    try:
        # Cria um DataFrame a partir dos dados fornecidos
        df: DataFrame = spark.createDataFrame([data], estoquelocalSchema)
        
        # Escreve o DataFrame na tabela 'estoquelocal' do banco de dados PostgreSQL
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "estoquelocal", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    
    # Retorna os dados adicionados
    return data

@app.delete("/estoquelocal/")
def delete_estoquelocal(data: estoquelocalDeleteData):
    try:
        # Cria a consulta SQL para deletar o registro com o ID fornecido
        delete_query = f"DELETE FROM estoquelocal WHERE id = {data.id}"

        # Obtém uma conexão JDBC e executa a consulta de deleção
        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(delete_query)
        statement.close()
        connection.close()

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return {"detail": "Data deleted successfully"}

@app.put("/estoquelocal/")
def update_estoquelocal(data: estoquelocalUpdateData):
    try:
        # Cria a consulta SQL para atualizar o registro com o ID fornecido
        update_query = f"UPDATE estoquelocal SET regiao = {data.regiao} WHERE id = {data.id}"

        # Obtém uma conexão JDBC e executa a consulta de atualização
        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(update_query)
        statement.close()
        connection.close()

        return {"success": True}

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

# Criação das rotas para leitura, inserção, deleção e alteração da tabela estoquelocalremedio
@app.get("/estoquelocalremedio/")
def read_estoquelocalremedio():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "estoquelocalremedio")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/estoquelocalremedio/{id}")
def read_estoquelocalremedio(id: int):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM estoquelocalremedio WHERE estoquelocal = {id}")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/estoquelocalremedio/")
def add_estoquelocalremedio(data: estoquelocalremedioData):
    try:
        df: DataFrame = spark.createDataFrame([data], estoquelocalremedioSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "estoquelocalremedio", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.delete("/estoquelocalremedio/")
def delete_estoquelocalremedio(data: estoquelocalremedioDeleteData):
    try:
        delete_query = f"DELETE FROM estoquelocalremedio WHERE estoquelocal = {data.estoquelocal} AND remedio = '{data.remedio}'"

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(delete_query)
        statement.close()
        connection.close()

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return {"detail": "Data deleted successfully"}

@app.put("/estoquelocalremedio/")
def update_estoquelocalremedio(data: estoquelocalremedioData):
    try:
        update_query = f"UPDATE estoquelocalremedio SET quantidade = {data.quantidade} WHERE (estoquelocal, remedio) = ({data.estoquelocal}, '{data.remedio}')"
        print(update_query)

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(update_query)
        statement.close()
        connection.close()

        return {"success": True}

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

@app.get("/estoqueregional/")
def read_estoqueregional():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "estoqueregional")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

# Criação das rotas para leitura, inserção, deleção e alteração da tabela estoqueregional
@app.get("/estoqueregional/{id}")
def read_estoqueregional(id: int):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM estoqueregional WHERE ID = {id}")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/estoqueregional/")
def add_estoqueregional(data: estoqueregionalData):
    try:
        df: DataFrame = spark.createDataFrame([data], estoqueregionalSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "estoqueregional", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.delete("/estoqueregional/")
def delete_estoqueregional(data: estoqueregionalDeleteData):
    try:
        delete_query = f"DELETE FROM estoqueregional WHERE id = '{data.id}'"

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(delete_query)
        statement.close()
        connection.close()

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return {"detail": "Data deleted successfully"}

@app.put("/estoqueregional/")
def update_estoqueregional(data: estoqueregionalUpdateData):
    try:
        update_query = f"UPDATE estoqueregional SET regiao = {data.regiao} WHERE id = {data.id}"

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(update_query)
        statement.close()
        connection.close()

        return {"success": True}

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

# Criação das rotas para leitura, inserção, deleção e alteração da tabela estoqueregionalremedio
@app.get("/estoqueregionalremedio/")
def read_estoqueregionalremedio():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "estoqueregionalremedio")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/estoqueregionalremedio/{id}")
def read_estoqueregionalremedio(id: int):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM estoqueregionalremedio WHERE estoqueregional = {id}")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/estoqueregionalremedio/")
def add_estoqueregionalremedio(data: estoqueregionalremedioData):
    try:
        df: DataFrame = spark.createDataFrame([data], estoqueregionalremedioSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "estoqueregionalremedio", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.delete("/estoqueregionalremedio/")
def delete_estoqueregionalremedio(data: estoqueregionalremedioDeleteData):
    try:
        delete_query = f"DELETE FROM estoqueregionalremedio WHERE estoqueregional = {data.estoqueregional} AND remedio = '{data.remedio}'"

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(delete_query)
        statement.close()
        connection.close()

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return {"detail": "Data deleted successfully"}

@app.put("/estoqueregionalremedio/")
def update_estoqueregionalremedio(data: estoqueregionalremedioData):
    try:
        update_query = f"UPDATE estoqueregionalremedio SET quantidade = {data.quantidade} WHERE (estoqueregional, remedio) = ({data.estoqueregional}, '{data.remedio}')"
        print(update_query)

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(update_query)
        statement.close()
        connection.close()

        return {"success": True}

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

# Criação das rotas para leitura, inserção, deleção e alteração da tabela farmaceutico
@app.get("/farmaceutico/")
def read_farmaceutico():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "farmaceutico")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/farmaceutico/{cpf}")
def read_farmaceutico(cpf: str):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM farmaceutico WHERE usuario = '{cpf}'")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/farmaceutico/")
def add_farmaceutico(data: farmaceuticoData):
    try:
        df: DataFrame = spark.createDataFrame([data], farmaceuticoSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "farmaceutico", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.delete("/farmaceutico/")
def delete_farmaceutico(data: farmaceuticoDeleteData):
    try:
        delete_query = f"DELETE FROM farmaceutico WHERE usuario = '{data.usuario}'"

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(delete_query)
        statement.close()
        connection.close()

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return {"detail": "Data deleted successfully"}

@app.put("/farmaceutico/")
def update_farmaceutico(data: farmaceuticoData):
    try:
        update_query = f"UPDATE farmaceutico SET posto = {data.posto} WHERE usuario = '{data.usuario}'"

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(update_query)
        statement.close()
        connection.close()

        return {"success": True}

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

# Criação das rotas para leitura, inserção, deleção e alteração da tabela medico
@app.get("/medico/")
def read_medico():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "medico")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/medico/{cpf}")
def read_medico(cpf: str):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM medico WHERE usuario = '{cpf}'")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/medico/")
def add_medico(data: medicoData):
    try:
        df: DataFrame = spark.createDataFrame([data], medicoSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "medico", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.delete("/medico/")
def delete_medico(data: medicoDeleteData):
    try:
        delete_query = f"DELETE FROM medico WHERE usuario = '{data.usuario}'"

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(delete_query)
        statement.close()
        connection.close()

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return {"detail": "Data deleted successfully"}

@app.put("/medico/")
def update_medico(data: medicoData):
    try:
        update_query = f"UPDATE medico SET posto = {data.posto} WHERE usuario = '{data.usuario}'"

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(update_query)
        statement.close()
        connection.close()

        return {"success": True}

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

# Criação das rotas para leitura, inserção, deleção e alteração da tabela paciente
@app.get("/paciente/")
def read_paciente():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "paciente")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/paciente/{cpf}")
def read_paciente(cpf: str):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM paciente WHERE usuario = '{cpf}'")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/paciente/")
def add_paciente(data: pacienteData):
    try:
        df: DataFrame = spark.createDataFrame([data], pacienteSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "paciente", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.delete("/paciente/")
def delete_paciente(data: pacienteDeleteData):
    try:
        delete_query = f"DELETE FROM paciente WHERE usuario = '{data.usuario}'"

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(delete_query)
        statement.close()
        connection.close()

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return {"detail": "Data deleted successfully"}

@app.put("/paciente/")
def update_paciente(data: pacienteData):
    try:
        update_query = f"UPDATE paciente SET convenio = '{data.convenio}', posto = {data.posto} WHERE usuario = '{data.usuario}'"

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(update_query)
        statement.close()
        connection.close()

        return {"success": True}

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

# Criação das rotas para leitura, inserção, deleção e alteração da tabela posto
@app.get("/posto/")
def read_posto():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "posto")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/posto/{id}")
def read_posto(id: int):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM posto WHERE ID = {id}")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/posto/")
def add_posto(data: postoData):
    try:
        df: DataFrame = spark.createDataFrame([data], postoSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "posto", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.delete("/posto/")
def delete_posto(data: postoDeleteData):
    try:
        delete_query = f"DELETE FROM posto WHERE id = {data.id}"

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(delete_query)
        statement.close()
        connection.close()

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return {"detail": "Data deleted successfully"}

@app.put("/posto/")
def update_posto(data: postoUpdateData):
    try:
        update_query = f"UPDATE posto SET nome = '{data.nome}', regiao = {data.regiao} WHERE id = {data.id}"
        print(update_query)

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(update_query)
        statement.close()
        connection.close()

        return {"success": True}

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

# Criação das rotas para leitura, inserção, deleção e alteração da tabela receita
@app.get("/receita/")
def read_receita():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "receita")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/receita/{id}")
def read_receita(id: int):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM receita WHERE ID = {id}")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/receita/")
def add_receita(data: receitaData):
    try:
        df: DataFrame = spark.createDataFrame([data], receitaSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "receita", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.delete("/receita/")
def delete_receita(data: receitaDeleteData):
    try:
        delete_query = f"DELETE FROM receita WHERE id = {data.id}"

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(delete_query)
        statement.close()
        connection.close()

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return {"detail": "Data deleted successfully"}

@app.put("/receita/")
def update_receita(data: receitaUpdateData):
    try:
        update_query = f"UPDATE receita SET medico = '{data.medico}', paciente = '{data.paciente}', posto = {data.posto} WHERE id = {data.id}"

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(update_query)
        statement.close()
        connection.close()

        return {"success": True}

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

# Criação das rotas para leitura, inserção, deleção e alteração da tabela receitaremedio
@app.get("/receitaremedio/")
def read_receitaremedio():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "receitaremedio")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/receitaremedio/{id}")
def read_receitaremedio(id: int):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM receitaremedio WHERE receita = {id}")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/receitaremedio/")
def add_receitaremedio(data: receitaremedioData):
    try:
        df: DataFrame = spark.createDataFrame([data], receitaremedioSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "receitaremedio", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.delete("/receitaremedio/")
def delete_receitaremedio(data: receitaremedioDeleteData):
    try:
        delete_query = f"DELETE FROM receitaremedio WHERE receita = {data.receita} AND remedio = '{data.remedio}'"

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(delete_query)
        statement.close()
        connection.close()

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return {"detail": "Data deleted successfully"}

@app.put("/receitaremedio/")
def update_receitaremedio(data: receitaremedioData):
    try:
        update_query = f"UPDATE receitaremedio SET prontidao = '{data.prontidao}' WHERE (receita, remedio) = ({data.receita}, '{data.remedio}')"
        print(update_query)

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(update_query)
        statement.close()
        connection.close()

        return {"success": True}

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

# Criação das rotas para leitura, inserção, deleção e alteração da tabela regiao
@app.get("/regiao/")
def read_regiao():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "regiao")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/regiao/{id}")
def read_regiao(id: int):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM regiao WHERE ID = {id}")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/regiao/")
def add_regiao(data: regiaoData):
    try:
        df: DataFrame = spark.createDataFrame([data], regiaoSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "regiao", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.delete("/regiao/")
def delete_regiao(data: regiaoDeleteData):
    try:
        delete_query = f"DELETE FROM regiao WHERE id = {data.id}"

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(delete_query)
        statement.close()
        connection.close()

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return {"detail": "Data deleted successfully"}

@app.put("/regiao/")
def update_regiao(data: regiaoUpdateData):
    try:
        update_query = f"UPDATE regiao SET nome = '{data.nome}' WHERE id = {data.id}"

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(update_query)
        statement.close()
        connection.close()

        return {"success": True}

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

# Criação das rotas para leitura, inserção, deleção e alteração da tabela remedio
@app.get("/remedio/")
def read_remedio():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "remedio")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/remedio/{nome}")
def read_remedio_nome(nome: str):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM remedio WHERE NOME ILIKE '%{nome}%'")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/remedio/")
def add_remedio(data: remedioData):
    try:
        df: DataFrame = spark.createDataFrame([data], remedioSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "remedio", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.delete("/remedio/")
def delete_remedio(data: remedioDeleteData):
    try:
        delete_query = f"DELETE FROM remedio WHERE nome = '{data.nome}'"

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(delete_query)
        statement.close()
        connection.close()

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return {"detail": "Data deleted successfully"}

@app.put("/remedio/")
def update_remedio(data: remedioData):
    try:
        update_query = f"UPDATE remedio SET tarja = '{data.tarja}' WHERE nome = '{data.nome}'"
        print(update_query)

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(update_query)
        statement.close()
        connection.close()

        return {"success": True}

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

# Criação das rotas para leitura, inserção, deleção e alteração da tabela tarja
@app.get("/tarja/")
def read_tarja():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "tarja")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/tarja/{nome}")
def read_tarja_nome(nome: str):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM tarja WHERE NOME ILIKE '%{nome}%'")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/tarja/")
def add_tarja(data: tarjaData):
    try:
        df: DataFrame = spark.createDataFrame([data], tarjaSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "tarja", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.delete("/tarja/")
def delete_tarja(data: tarjaDeleteData):
    try:
        delete_query = f"DELETE FROM tarja WHERE nome = '{data.nome}'"

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(delete_query)
        statement.close()
        connection.close()

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return {"detail": "Data deleted successfully"}

@app.put("/tarja/")
def update_tarja(data: tarjaData):
    try:
        update_query = f"UPDATE tarja SET retencao = {'TRUE' if data.retencao else 'FALSE'} WHERE nome = '{data.nome}'"
        print(update_query)

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(update_query)
        statement.close()
        connection.close()

        return {"success": True}

    except Exception as e:

        raise HTTPException(status_code=500, detail=str(e))

# Criação das rotas para leitura, inserção, deleção e alteração da tabela usuario
@app.get("/usuario/")
def read_usuario():
    df = spark.read\
        .format("jdbc")\
        .option("url", url)\
        .option("dbtable", "usuario")\
        .option("user", properties["user"])\
        .option("password", properties["password"])\
        .option("driver", properties["driver"])\
        .load()
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.get("/usuario/{cpf}")
def read_usuario(cpf: int):
    try:
        df = spark.read\
            .format("jdbc")\
            .option("url", url)\
            .option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .option("query", f"SELECT * FROM usuario WHERE CPF = '{cpf}'")\
            .load()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return df.toJSON().map(lambda row: json.loads(row)).collect()

@app.post("/usuario/")
def add_usuario(data: usuarioData):
    try:
        df: DataFrame = spark.createDataFrame([data], usuarioSchema)
        df.write.option("user", properties["user"])\
            .option("password", properties["password"])\
            .option("driver", properties["driver"])\
            .jdbc(url, "usuario", mode="append")
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return data

@app.delete("/usuario/")
def delete_usuario(data: usuarioDeleteData):
    try:
        delete_query = f"DELETE FROM usuario WHERE cpf = '{data.cpf}'"

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(delete_query)
        statement.close()
        connection.close()

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    return {"detail": "Data deleted successfully"}

@app.put("/usuario/")
def update_usuario(data: usuarioData):
    try:
        update_query = f"UPDATE usuario SET senha = '{data.senha}', email = '{data.email}' WHERE cpf = '{data.cpf}'"

        connection = spark._sc._gateway.jvm.java.sql.DriverManager.getConnection(url, properties["user"], properties["password"])
        statement = connection.createStatement()
        statement.executeUpdate(update_query)
        statement.close()
        connection.close()

        return {"success": True}

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

























































