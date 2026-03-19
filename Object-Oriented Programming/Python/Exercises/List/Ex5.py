print("Digite um numero inteiro: ")
num = input()

previous_prime = -1
is_prime = True

for i in range(int(num) - 1, 1, -1):
    for j in range(2, i):
        if(i % j == 0):
            is_prime = False
            break
        is_prime = True
    if(is_prime == True):
        previous_prime = i
        break
    
if(previous_prime != -1):
    print("O primeiro número primo menor que o número informado é: %d." % previous_prime)
else:
    print("Não existe número primo menor que o número informado.")



