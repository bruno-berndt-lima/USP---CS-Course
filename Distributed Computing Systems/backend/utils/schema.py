from pyspark.sql.types import *
from pydantic import BaseModel

# Schema para a tabela "regiao"
regiaoSchema = StructType([
    StructField("nome", StringType())
])

# Schema para a tabela "estoqueregional"
estoqueregionalSchema = StructType([
    StructField("regiao", IntegerType())
])

# Schema para a tabela "estoquelocal"
estoquelocalSchema = StructType([
    StructField("regiao", IntegerType())
])

# Schema para a tabela "tarja"
tarjaSchema = StructType([
    StructField("nome", StringType()),
    StructField("retencao", BooleanType())
])

# Schema para a tabela "remedio"
remedioSchema = StructType([
    StructField("nome", StringType()),
    StructField("tarja", StringType())
])

# Schema para a tabela "ativo"
ativoSchema = StructType([
    StructField("nome", StringType())
])

# Schema para a tabela "ativoremedio"
ativoremedioSchema = StructType([
    StructField("remedio", StringType()),
    StructField("ativo", StringType())
])

# Schema para a tabela "estoqueregionalremedio"
estoqueregionalremedioSchema = StructType([
    StructField("estoqueregional", LongType()),
    StructField("remedio", StringType()),
    StructField("quantidade", LongType())
])

# Schema para a tabela "estoquelocalremedio"
estoquelocalremedioSchema = StructType([
    StructField("estoquelocal", LongType()),
    StructField("remedio", StringType()),
    StructField("quantidade", LongType())
])

# Schema para a tabela "posto"
postoSchema = StructType([
    StructField("nome", StringType()),
    StructField("regiao", LongType())
])

# Schema para a tabela "usuario"
usuarioSchema = StructType([
    StructField("cpf", StringType()),
    StructField("senha", StringType()),
    StructField("email", StringType())
])

# Schema para a tabela "farmaceutico"
farmaceuticoSchema = StructType([
    StructField("usuario", StringType()),
    StructField("posto", LongType())
])

# Schema para a tabela "medico"
medicoSchema = StructType([
    StructField("usuario", StringType()),
    StructField("posto", LongType())
])

# Schema para a tabela "paciente"
pacienteSchema = StructType([
    StructField("usuario", StringType()),
    StructField("convenio", StringType()),
    StructField("posto", LongType())
])

# Schema para a tabela "receita"
receitaSchema = StructType([
    StructField("medico", StringType()),
    StructField("paciente", StringType()),
    StructField("posto", LongType())
])

# Schema para a tabela "receitaremedio"
receitaremedioSchema = StructType([
    StructField("receita", LongType()),
    StructField("remedio", StringType()),
    StructField("prontidao", CharType(1))
])

# Define uma classe de dados para a tabela 'regiao' para inserção
class regiaoData(BaseModel):
    nome: str

# Define uma classe de dados para a tabela 'regiao' para fazer update
class regiaoUpdateData(BaseModel):
    id: int
    nome: str

# Define uma classe de dados para a tabela 'regiao' para fazer delete
class regiaoDeleteData(BaseModel):
    id: int

# Define uma classe de dados para a tabela 'estoqueregional' para inserção
class estoqueregionalData(BaseModel):
    regiao: int

# Define uma classe de dados para a tabela 'estoqueregional' para update
class estoqueregionalUpdateData(BaseModel):
    id: int
    regiao: int
    
# Define uma classe de dados para a tabela 'estoqueregional' para delete
class estoqueregionalDeleteData(BaseModel):
    id: int

# Define uma classe de dados para a tabela 'estoquelocal' para inserção
class estoquelocalData(BaseModel):
    regiao: int

# Define uma classe de dados para a tabela 'estoquelocal' para update
class estoquelocalUpdateData(BaseModel):
    id: int
    regiao: int

# Define uma classe de dados para a tabela 'estoquelocal' para delete
class estoquelocalDeleteData(BaseModel):
    id: int

# Define uma classe de dados para a tabela 'tarja' para inserção
class tarjaData(BaseModel):
    nome: str
    retencao: bool

# Define uma classe de dados para a tabela 'tarja' para delete
class tarjaDeleteData(BaseModel):
    nome: str

# Define uma classe de dados para a tabela 'remedio' para inserção
class remedioData(BaseModel):
    nome: str
    tarja: str

# Define uma classe de dados para a tabela 'remedio' para update
class remedioDeleteData(BaseModel):
    nome: str

# Define uma classe de dados para a tabela 'ativo' para inserção
class ativoData(BaseModel):
    nome: str

# Define uma classe de dados para a tabela 'ativoremedio' para inserção
class ativoremedioData(BaseModel):
    remedio: str
    ativo: str

# Define uma classe de dados para a tabela 'estoqueregionalremedio' para inserção
class estoqueregionalremedioData(BaseModel):
    estoqueregional: int
    remedio: str
    quantidade: int

# Define uma classe de dados para a tabela 'estoqueregionalremedio' para delete
class estoqueregionalremedioDeleteData(BaseModel):
    estoqueregional: int
    remedio: str

# Define uma classe de dados para a tabela 'estoquelocalremedio' para inserção
class estoquelocalremedioData(BaseModel):
    estoquelocal: int
    remedio: str
    quantidade: int

# Define uma classe de dados para a tabela 'estoquelocaalremedio' para delete
class estoquelocalremedioDeleteData(BaseModel):
    estoquelocal: int
    remedio: str

# Define uma classe de dados para a tabela 'posto' para inserção
class postoData(BaseModel):
    nome: str
    regiao: int

# Define uma classe de dados para a tabela 'posto' para delete
class postoDeleteData(BaseModel):
    id: int

# Define uma classe de dados para a tabela 'posto' para update
class postoUpdateData(BaseModel):
    id: int
    nome: str
    regiao: int

# Define uma classe de dados para a tabela 'usuario' para inserção
class usuarioData(BaseModel):
    cpf: str
    senha: str
    email: str

# Define uma classe de dados para a tabela 'usuario' para delete
class usuarioDeleteData(BaseModel):
    cpf: str

# Define uma classe de dados para a tabela 'farmaceutico' para inserção
class farmaceuticoData(BaseModel):
    usuario: str
    posto: int

# Define uma classe de dados para a tabela 'farmaceutico' para delete
class farmaceuticoDeleteData(BaseModel):
    usuario: str

# Define uma classe de dados para a tabela 'medico' para inserção
class medicoData(BaseModel):
    usuario: str
    posto: int

# Define uma classe de dados para a tabela 'medico' para delete
class medicoDeleteData(BaseModel):
    usuario: str

# Define uma classe de dados para a tabela 'paciente' para inserção
class pacienteData(BaseModel):
    usuario: str
    convenio: str
    posto: int

# Define uma classe de dados para a tabela 'paciente' para delete
class pacienteDeleteData(BaseModel):
    usuario: str

# Define uma classe de dados para a tabela 'receita' para inserção
class receitaData(BaseModel):
    medico: str
    paciente: str
    posto: int

# Define uma classe de dados para a tabela 'receita' para delete
class receitaDeleteData(BaseModel):
    id: int

# Define uma classe de dados para a tabela 'receita' para update
class receitaUpdateData(BaseModel):
    id: int
    medico: str
    paciente: str
    posto: int

# Define uma classe de dados para a tabela 'receitaremedio' para inserção
class receitaremedioData(BaseModel):
    receita: int
    remedio: str
    prontidao: str

# Define uma classe de dados para a tabela 'receitaremedio' para delete
class receitaremedioDeleteData(BaseModel):
    receita: int
    remedio: str


