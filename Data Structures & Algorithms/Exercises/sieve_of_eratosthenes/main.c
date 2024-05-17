// Bruno Berndt Lima - 12542550

#include <stdio.h>
#include <stdlib.h>
#include "crivo.h"

int main() {
    int n_primes_to_print;
    scanf("%d", &n_primes_to_print);

    char c;
    int i = 0;
    int *index;
    index = malloc(sizeof(int));
    while ((c = getchar()) != EOF) {
        ungetc(c, stdin);
        scanf("%d", &index[i]);
        i++;
        index = realloc(index, sizeof(int) * (i + 1));
    }

    list_t  *l = create();

    for (int j = 1; j <= 10000; j++) {  // criando uma lista de 1 a 10000
        insert(l, j);
    }

    remove_elem(l, 1);  // remove o 1 da lista

    // remove todos os multiplos dos primos, inicializando pelo 2
    for (int j = 2; j * j <= 10001; j++) {
        for (int k = j * j; k < 10001; k += j) {
            remove_elem(l, k);
        }
    }
    for (int j = 0; j < n_primes_to_print; j++) {
        print_elem_from_list(l, index[j]);
    }

    destroy(l);

    free(index);

    return 0;
}
