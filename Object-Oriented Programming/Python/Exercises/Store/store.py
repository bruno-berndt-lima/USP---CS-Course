from produto import Product, Book, Cd, Dvd

def main():
    a = Store()
    chooseOption(a.products)


def chooseOption(prodList):
    while True:
        print("Escolha o número da opção desejada:")
        print("1: Adicionar produto no estoque")
        print("2: Vender produto")
        print("3: Procurar produto no estoque")
        print("4: Mostrar o estoque de produtos")
        print("5: Sair")

        option = int (input())


        if option == 1:
            prodType = input("Digite o produto (\"Livro\", \"Cd\" ou \"Dvd\") que deseja adicionar: ")
            if (prodType == "Livro"):
                print("Digite os dados do livro que deseja adicionar: ")
                barcode = input("Código de barras: ")
                name = input("Nome do livro: ")
                author = input("Autor: ")
                year = input("Ano de Lançamento: ")
                qtt = int (input("Quantidade a adicionar: "))
                p = Book(barcode, name, author, year)
                Store.storeProduct(p, prodList, qtt)
            
            elif (prodType == "Cd"):
                print("Digite os dados do CD que deseja adicionar: ")
                barcode = input("Código de barras: ")
                name = input("Nome do CD: ")
                artist = input("Artista: ")
                genre = input("Gênero: ")
                year = input("Ano de Lançamento: ")
                qtt = int (input("Quantidade a adicionar: "))
                p = Cd(barcode, name, genre, artist, year)
                Store.storeProduct(p, prodList, qtt)  
            
            elif (prodType == "Dvd"):
                print("Digite os dados do DVD que deseja adicionar: ")
                barcode = input("Código de barras: ")
                name = input("Nome do DVD: ")
                director = input("Diretor: ")
                genre = input("Gênero: ")
                year = input("Ano de Lançamento: ")
                qtt = int (input("Quantidade a adicionar: "))
                p = Dvd(barcode, name, genre, director, year)
                Store.storeProduct(p, prodList, qtt) 

        elif option == 2:
            barcode = input("Digite o código de barras do produto a vender: ")
            qtt = int (input("Digite a quantidade que deseja vender: "))
            Store.sellProduct(prodList, barcode, qtt) 

        elif option == 3:
            op = input("Como deseja fazer a busca? Digite \"Nome\" ou \"Codigo\"?\n")
            if op == "Nome":
                name = input("Digite o nome que deseja buscar: ")
                Store.searchProduct(prodList, name = name)
            elif op == "Codigo":
                codigo = input("Digite o código que deseja buscar: ")
                Store.searchProduct(prodList, barcode = codigo)
        
        elif option == 4:
            filter = input("Digite como deseja ver o estoque: \"Produto\" ou \"Categoria\"\n")
            Store.getStock(prodList, filter)

        else:
            return

class Store():
    def __init__(self):
        self.products = []

    def storeProduct(p:Product, products, num):
        products.append(p)
        products[len(products)-1].qtt = num

    def searchProduct(products, barcode = "", name = ""):
        for i, prod in enumerate(products):
            if prod.barcode == barcode or prod.name == name:
                if products[i].qtt > 0:
                    if isinstance(prod, Book):
                        print("             Livro")
                    elif isinstance(prod, Cd):
                        print("             CD")
                    elif isinstance(prod, Dvd):
                        print("             DVD")

                    print(prod)
                    print("Estoque: {}".format(products[i].qtt))
                    print("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=")
                    return
                else:
                    print("Produto esgotado\n")
                    return

        print("Produto não encontrado.\n")

    def sellProduct(products, barcode, qtt):
        for i, prod in enumerate(products):
            if prod.barcode == barcode and products[i].qtt > 0 and products[i].qtt - qtt > 0:
                products[i].qtt -= qtt
                return                

        print("Não foi possível realizar a venda.\n")
        return

    def getStock(products, filter):
        booksQtt = 0
        cdsQtt = 0
        dvdsQtt = 0

        for i, prod in enumerate(products):
            if filter == "Produto":
                if isinstance(prod, Book):
                    print("             Livro")
                elif isinstance(prod, Cd):
                    print("             CD")
                elif isinstance(prod, Dvd):
                    print("             DVD")

                print(prod)
                print("Estoque: {}".format(products[i].qtt))
                print("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=")

            elif filter == "Categoria":
                if isinstance(prod, Book):
                    booksQtt += products[i].qtt
                elif isinstance(prod, Cd):
                    cdsQtt += products[i].qtt
                elif isinstance(prod, Dvd):
                    dvdsQtt += products[i].qtt
                
                if i == len(products) - 1:
                    print("Estoque de livros: {}".format(booksQtt))
                    print("Estoque de CDs: {}".format(cdsQtt))
                    print("Estoque de DVDs: {}".format(dvdsQtt))

main()
