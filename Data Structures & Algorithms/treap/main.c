#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treap.h"

void print(tree_t *t, char print_type[15]) {
    if (strcmp(print_type, "preordem") == 0) {
        pre_order(t->root);
    } else if (strcmp(print_type, "ordem") == 0) {
        in_order(t->root);
    } else if (strcmp(print_type, "posordem") == 0) {
        post_order(t->root);
    } else if (strcmp(print_type, "largura") == 0) {
        level_order(t->root);
    }
}

int main() {
    tree_t *t = create();

    int n_lines, count = 0;

    scanf("%d", &n_lines);

    char command[15], print_type[15];
    int key, priority;
    while (count < n_lines) {
        scanf("%s", command);

        if (strcmp(command, "insercao") == 0) {
            scanf("%d %d", &key, &priority);
            insert(&t->root, key, priority);

        } else if (strcmp(command, "impressao") == 0) {
            scanf("%s", print_type);

            print(t, print_type);
            printf("\n");
        } else if (strcmp(command, "remocao") == 0) {
            scanf("%d", &key);
            if (search(t->root, key) == 1) {
                t->root = delete_node(t->root, key);
            } else {
                printf("Chave nao localizada\n");
            }
        } else if (strcmp(command, "buscar") == 0) {
            scanf("%d", &key);
            int ret = search(t->root, key);
            printf("%d\n", ret);
        }

        count++;
    }

    destroy(t->root);
    free(t);

    return 0;
}
