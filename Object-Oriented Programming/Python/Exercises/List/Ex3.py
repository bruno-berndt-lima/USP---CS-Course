print("Digite um numero inteiro: ")
num = input()
count = int(num)

for i in range(int(num), 0, -1):
    for j in range(i, 0, -1):
        print("*", end="")
    print("\n")
