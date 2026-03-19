print("Digite um valor para se calcular a raiz quadrada: ")
x = input()

print("Digite um valor como chute inicial: ")
x0 = input()

xi = x0
error_out_of_range = True

while error_out_of_range == True:
    prev_xi = xi
    xi = (float (prev_xi) + ((float (x) / float(prev_xi)))) / 2

    if (float (xi) - float (prev_xi)) <= 0.000000001:
        prev_xi = xi
        xi = (float (prev_xi) + ((float (x) / float(prev_xi)))) / 2
        error_out_of_range = False


print("A raiz quadrada de {:.7f} é: {:.7f}\n".format(float(x), float (xi)))