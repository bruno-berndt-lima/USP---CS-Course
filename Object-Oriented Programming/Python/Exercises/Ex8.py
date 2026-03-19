f = lambda x: x ** 3 - x ** 2 - 13 * x + 8
f_deriv = lambda x: 3 * x ** 2 - 2 * x - 13

print("Digite o chute inicial: ")
X = int(input())

n_iteracoes = 0
erro = 0.0000001
X0 = 0

while(abs(X0 - X) >= erro):
    X0 = X
    A = f(X)
    B = f_deriv(X)
    X = X0 - (A / B)
    n_iteracoes += 1

print("A raíz encontrada é: %f." % X)
print("O número de iterações necessárias foi: %d." % n_iteracoes)
