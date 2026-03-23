class Grupo():
    def __init__(self):
        self.integrantes = [] # lista dos integrantes do grupo
        self.turmaIntegrantes = [] # lista da turma de cada integrante do grupo
        self.nIntegrantes = 0
        self.turma = ""

    def __str__(self):
        s = ""
        for integrante in self.integrantes:
            s += "{} - {}\n".format(integrante.nUsp, integrante.nome)
        return s

    