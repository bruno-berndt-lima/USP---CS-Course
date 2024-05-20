// Bruno Berndt Lima - 12542550

#include <stdio.h>
#include <string.h>
#include "funcs.h"
#include "doubly_linked_list.h"

int main() {
    list_t *l_result;
    int n_lines;
    scanf("%d", &n_lines);

    int *n1, *n2;
    int count = 0;
    char command[5]; // sum, big, sml ou eql
    while (n_lines > count) {
        scanf("%s ", command);

        // variaveis que armazenarao o tamanho do numero
        int size_n1;
        int size_n2;

        n1 = read_number(&size_n1);
        n2 = read_number(&size_n2);

        list_t *l1 = create();
        list_t *l2 = create();

        // insercao dos elementos na ordem inversa
        // para ficar mais facil as contas
        for (int i = size_n1 - 1; i >= 0; i--) {
            insert_elem(l1, n1[i]);
        }
        for (int i = size_n2 - 1; i >= 0; i--) {
            insert_elem(l2, n2[i]);
        }

        if (strcmp(command, "SUM") == 0) {
            l_result = sum(l1, l2);
            print_inv_list(l_result);
            free_all(l_result, l1, l2);

        } else if (strcmp(command, "BIG") == 0) {
            int ret = is_bigger(l1,l2, size_n1, size_n2);
            printf("%d\n", ret);
            free_all(NULL, l1, l2);

        } else if (strcmp(command, "SML") == 0) {
            int ret = is_smaller(l1, l2, size_n1, size_n2);
            printf("%d\n", ret);
            free_all(NULL, l1, l2);

        } else if (strcmp(command, "EQL") == 0) {
            int ret = is_equal(l1, l2, size_n1, size_n2);
            printf("%d\n", ret);
            free_all(NULL, l1, l2);
        }
        count++;
    }

    return 0;
}

