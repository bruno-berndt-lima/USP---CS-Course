// Bruno Berndt Lima - 12542550

#include <stdio.h>
#include "linked_list.h"

int main() {
    int n_tests;
    scanf("%d", &n_tests);

    char c;
    int count = 0;
    int n_polynomials, coef;

    // loop mais externo que ira controlar os casos testes
    while (count < n_tests) {
        scanf("%d", &n_polynomials);

        // criando um vetor de listas de acordo com a quantidade de polinomios
        list_t *l[n_polynomials];

        for (int i = 0; i < n_polynomials; i++) {
            l[i] = create();

            while ((c = getchar()) != ')') {
                if(c == '(' || c == ',' || c == '\n' || c == '\r') {
                    continue;
                } else {
                    ungetc(c, stdin);
                    scanf("%d", &coef);
                    insert(l[i], coef);
                }
            }
        }

        list_t *result = polynomial_coef_sum(l, n_polynomials);
        print_list(result);

        for (int i = 0; i < n_polynomials; i++) {
            destroy(l[i]);
        }
        destroy(result);

        count++;
    }

    return 0;
}
