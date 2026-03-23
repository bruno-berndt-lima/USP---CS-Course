import io
from aluno import Aluno
from grupo import Grupo
from zipfile import ZipFile

def main():
    turma1 = []
    turma2 = []
    grupos = []
    
    # Arquivo dos alunos da turma 1
    with open("/home/bruno/ssc103 - POO - Python/VerificaçãoDosGrupos/ListadeApoioaoDocente-SSC01032022101.csv", "r") as t1File:
        for line in t1File:
            num, nome = line.split(",")
            aluno = Aluno(num, nome)
            turma1.append(aluno)
            #print(aluno)

    # Arquivo dos alunos da turma 2
    with open("/home/bruno/ssc103 - POO - Python/VerificaçãoDosGrupos/ListadeApoioaoDocente-SSC01032022102.csv", "r") as t2File:
        for line in t2File:
            num, nome = line.split(",")
            aluno = Aluno(num, nome)
            turma2.append(aluno)
            #print(aluno)
    
    # Arquivo Zip dos grupos
    with ZipFile("/home/bruno/ssc103 - POO - Python/VerificaçãoDosGrupos/SSC0103-2022-Definição dos grupos-4240978.zip", "r") as zipGrupos:
        arqsError = [] # lista para armazenar arquivos com problema na abertura ou leitura, caso exista
        for grupo in zipGrupos.namelist():
            gr = Grupo()
            nIntegrantes = 0
            with zipGrupos.open(grupo) as g:
                try:
                    for line in io.TextIOWrapper(g, 'utf-8'):
                        if line != "" and line != "\n" and line != "\r\n": # se nao for uma linha vazia
                            cleanLine = line.strip("\"\r\n") # remove aspas e quebra-de-linha da linha em questão
                            num, nome = cleanLine.split(",")
                            aluno = Aluno(num, nome)
                            gr.integrantes.append(aluno)
                            nIntegrantes += 1
                        else:
                            continue
                except:
                    arqsError.append(grupo)
                    continue

                gr.nIntegrantes = nIntegrantes
                gr.turmaIntegrantes = [0] * gr.nIntegrantes
                grupos.append(gr)

    # checa a turma de todos os grupos
    checkTurma(grupos, turma1, turma2)

    printGrupos(grupos)

    print("------------ Alunos sem grupo da Turma 1: ------------\n")
    naoTemGrupo(turma1) # mostra os alunos sem grupo da turma 1
    print("------------ Alunos sem grupo da Turma 2: ------------\n")
    naoTemGrupo(turma2) # mostra os alunos sem grupo da turma 2

    # mostra os grupos com número de participantes diferente de 4
    print("------------ Grupos com número inválido de participantes ------------\n")
    grupoDiff4Integrantes(grupos)

    # mostra os arquivos que tiveram algum erro e portanto não foi possível a leitura do grupo
    if len(arqsError) > 0:
        print("------------ Falha ao processar seguinte(s) arquivo(s) ------------\n")
        for arquivo in arqsError:
            print(arquivo)


def checkTurma(grupos, turma1, turma2):
    for grupo in grupos:
        for aluno in turma1:
            for i in range(grupo.nIntegrantes):
                if grupo.integrantes[i].nUsp == aluno.nUsp:
                    aluno.temGrupo = True
                    grupo.turmaIntegrantes[i] = 1

        # se todos os alunos forem da turma 1
        if all(x == 1 for x in grupo.turmaIntegrantes):
            grupo.turma = "Turma 1"
            continue
                
        for aluno in turma2:
            for i in range(grupo.nIntegrantes):
                if grupo.integrantes[i].nUsp == aluno.nUsp:
                    aluno.temGrupo = True
                    grupo.turmaIntegrantes[i] = 2

        # se todos os alunos forem da turma 2
        if all(x == 2 for x in grupo.turmaIntegrantes):
            grupo.turma = "Turma 2"
            continue

        # se todos os alunos forem da turma 1 ou 2
        if all(x in grupo.turmaIntegrantes for x in [1, 2]):        
            grupo.turma = "Duas Turmas"
            continue

        # se algum aluno não pertence a nenhuma das turmas, então esse aluno não existe
        for i in range(grupo.nIntegrantes):
            if grupo.turmaIntegrantes[i] == 0:
                grupo.turma = "Grupo com aluno que não existe"
                


def naoTemGrupo(turma):
    for aluno in turma:
        if aluno.temGrupo == False:
            print(aluno, end = "")  
    print("\n") 

# Grupos com numero de participantes diferente de 4
def grupoDiff4Integrantes(grupos):
    for grupo in grupos:
        if grupo.nIntegrantes != 4:
            print("Grupo com {} integrante{}".format(grupo.nIntegrantes, 's' if grupo.nIntegrantes > 1 else ''))
            print(grupo)   

# printa todos os grupos
def printGrupos(grupos):
    # printa os grupos da turma 1
    print("------------ Grupos com alunos da Turma 1 ------------\n")
    existe = False
    for grupo in grupos:
        if grupo.turma == "Turma 1":
            existe = True
            print(grupo, end = "")
            print("\n")
    if not existe:
        print("Não existe\n")

    # printa os grupos da turma 2
    print("------------ Grupos com alunos da Turma 2 ------------\n")
    existe = False
    for grupo in grupos:
        if grupo.turma == "Turma 2":
            existe = True
            print(grupo, end = "")
            print("\n")
    if not existe:
        print("Não existe\n")

    # printa os grupos com alunos das duas turmas
    print("------------ Grupos com alunos das duas Turmas ------------\n")
    existe = False
    for grupo in grupos:
        if grupo.turma == "Duas Turmas":
            existe = True
            print(grupo, end = "")
            print("\n")
    if not existe:
        print("Não existe\n")

    
    # printa os grupos com alunos que não existem
    print("------------ Grupo com aluno que não existe ------------\n")
    existe = False
    for grupo in grupos:
        if grupo.turma == "Grupo com aluno que não existe":
            existe = True
            print(grupo, end = "")
            print("\n")  
    if not existe:
        print("Não existe\n")

 
main()