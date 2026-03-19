import random

class Adivinha:

    print("Digite um numero:")
    N = int(input())

    guess = random.randint(0, N)
    menor = 0
    maior = N
    while(True):
        print(guess)        

        value = input()    

        if(value == "menor"):
            if(guess < maior):
                maior = guess
            guess = random.randint(menor + 1, maior - 1)
        elif(value == "maior"):
            if(guess > menor):
                menor = guess
            guess = random.randint(menor + 1, maior - 1)
        else:
            print("Acertou o numero")
            break

    



