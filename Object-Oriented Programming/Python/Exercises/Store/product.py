class Product():
    def __init__(self, barcode):
        self.barcode = barcode


class Book(Product):
    def __init__(self, barcode, name, author, year):
        super().__init__(barcode)
        self.name = name
        self.author = author
        self.year = year

    def __str__(self):
        s = "Nome: {}\nAutor: {}\nAno de Lançamento: {}".format(self.name, self.author, self.year)
        return s
        

class Cd(Product):
    def __init__(self, barcode, name, genre, artist, year):
        super().__init__(barcode)
        self.name = name
        self.genre = genre
        self.artist = artist
        self.year = year

    def __str__(self):
        s = "Nome: {}\nGênero: {}\nArtista: {}\nAno de Lançamento: {}".format(self.name, self.genre, self.artist, self.year)
        return s
        

class Dvd(Product):
    def __init__(self, barcode, name, genre, director, year):
        super().__init__(barcode)
        self.name = name
        self.genre = genre
        self.director = director
        self.year = year

    def __str__(self):
        s = "Nome: {}\nGênero: {}\nDiretor: {}\nAno de Lançamento: {}".format(self.name, self.genre, self.director, self.year)
        return s