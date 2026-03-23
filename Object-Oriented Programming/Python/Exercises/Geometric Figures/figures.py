import math

def main():
    fig = chooseFigure()

    Figure.calcArea(fig)    
    Figure.calcPerimeter(fig)  
    print("Cor: {}".format(fig.color))
    print(fig.filled) 

def chooseFigure():
    print("Escolha o número da figura desejada:")
    print("1: Círculo")
    print("2: Retângulo")
    print("3: Quadrado")   

    figure = int (input())

    if(figure == 1):
        fig = Circle()
    elif(figure == 2):
        fig = Rectangle()
    elif(figure == 3):
        fig = Square()

    return fig

class Figure():
    def __init__(self):  
        self.color = "" 
        self.filled = "Figura vazia"
        color = input("Digite a cor que deseja preencher a figura, caso não queira aperte \"ENTER\": \n")
        if(color != ""):
            self.color = color
            self.filled = "Figura preenchida"

    def calcArea(self):
        if isinstance(self, Circle):
            area = Circle.calcArea(self)
        elif isinstance(self, Rectangle):
            area = Rectangle.calcArea(self)
        elif isinstance(self, Square):
            area = Square.calcArea(self)

        print("Área: {:.3f}".format(area))

    def calcPerimeter(self):
        if isinstance(self, Circle) :
            perimeter = Circle.calcPerimeter(self)
        elif isinstance(self, Rectangle):
            perimeter = Rectangle.calcPerimeter(self)
        elif isinstance(self, Square):
            perimeter = Square.calcPerimeter(self)

        print("Perímetro: {:.3f}".format(perimeter))


class Circle(Figure):
    def __init__(self):
        super().__init__()
        self.radius = float (input("Digite o raio do círculo: "))

    def calcArea(self):
        return math.pi * (self.radius ** 2)

    def calcPerimeter(self):
        return 2 * math.pi * self.radius

class Rectangle(Figure):
    def __init__(self):
        super().__init__()
        self.length = float (input("Digite o tamanho da base do retângulo: "))
        self.width = float (input("Digite o tamanho da altura do retângulo: "))

    def calcArea(self):
        return self.length * self.width

    def calcPerimeter(self):
        return 2 * (self.length + self.width)

class Square(Figure):
    def __init__(self):
        super().__init__()
        self.side = float (input("Digite o tamanho do lado do quadrado: "))

    def calcArea(self):
        return self.side ** 2

    def calcPerimeter(self):
        return 4 * self.side


main()

