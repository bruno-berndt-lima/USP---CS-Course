from sqlalchemy import false


print("Digite um numero inteiro: ")
num = input()

smallest_divisor = 1
is_prime = True

for i in range(2, int(num)):
    if(int(num) % i == 0):
        is_prime = False
        smallest_divisor = i
        break

if(is_prime == False):
    print("O número digitado não é primo e seu menor divisor é: %d" % smallest_divisor)  
else:
    print("O número digitado é primo.")    
