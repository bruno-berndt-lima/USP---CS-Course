class Aluno():
    def __init__(self, numeroUsp, nome):
        self.nUsp = numeroUsp
        self.nome = nome
        self.temGrupo = False

    def __str__(self):
        return "{} - {}".format(self.nUsp, self.nome)




