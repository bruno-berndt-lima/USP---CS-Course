import math
import sys

print("Digite os coeficientes a, b, c, respectivamente:")
valid_coef = False

while valid_coef == False:
    try:
        print("a:")
        a = int(input())
        print("b:")
        b = int(input())
        print("c:")
        c = int(input())
        valid_coef = True
    except ValueError:
        print("Digite um número válido:")

delta = pow(b,2) - 4 * a * c

if delta < 0:
    print("A equação não possui raízes reais.\n")
    sys.exit()

x1 = (-b + math.sqrt(delta)) / (2*a)
x2 = (-b - math.sqrt(delta)) / (2*a) 

print("As raízes da equação são: {:.7f} e {:.7f}.\n".format(x1, x2))
    
