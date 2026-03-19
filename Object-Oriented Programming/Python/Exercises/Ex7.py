eq = lambda x: x ** 3 - x ** 2 - 13 * x + 8

print("Digite o ponto inicial A do intervalo: ")
A = int(input())
print("Digite o ponto final B do intervalo: ")
B = int(input())

n_iteracoes = 0
erro = 0.0000001
C = (A + B) / 2

if((eq(A) * eq(B)) < 0):
    while(abs((B - A) / 2) >= erro):
        n_iteracoes += 1
        C = (A + B) / 2
        if(eq(C) == 0):
            print("A raíz encontrada no intervalo é: %f." % C)
            break
        else:
            if(eq(A) * eq(C) < 0):
                B = C
            else:
                A = C
    print("A raíz encontrada no intervalo é: %f." % C)
else:
    print("A raíz não foi encontrada nesse intervalo.")

print("O número de iterações necessárias foi: %d." % n_iteracoes)