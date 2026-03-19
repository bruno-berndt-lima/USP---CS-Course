tmp = 0
maior = menor = 0
x = -1

while(x != 0) :
    x = float(input())
    if(tmp == 0):
        menor = x
        maior = x
    if(x > maior and x != 0):
        maior = x
    elif(x < menor and x != 0): 
        menor = x			
    tmp += 1

print("O maior número digitado é {:.7f} e o menor é {:.7f}.".format(maior, menor))