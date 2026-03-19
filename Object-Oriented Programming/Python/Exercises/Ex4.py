print("Digite um numero inteiro: ")
num = input()

space = tmp = 0

for i in range(int(num), 0, -1):
    for j in range(i, 0, -1):
        if(space != 0):
            while(tmp < space) :
                print(" ", end="")
                tmp += 1
        print("*", end="")
    space += 1
    tmp = 0
    print("\n")
    