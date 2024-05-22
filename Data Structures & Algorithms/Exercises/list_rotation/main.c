// Bruno Berndt Lima - 12542550

#include <stdio.h>
#include "lista.h"

struct node {
    elem info;
    node_t *next;
};

struct list {
    node_t *beginning, *end;
    int list_size;
};

void rotate_list(list_t *l, int n_rotations, int list_size) {
    node_t *current, *temp, *node_x;

    // atribuindo a uma variavel temporaria o noh inicial
    temp = l->beginning;

    // loop para o temp apontar para o ultimo elemento da lista
    while (temp->next != NULL) {
        temp = temp->next;
    }

    if (n_rotations > list_size) {
        n_rotations = n_rotations % list_size;
    }
    n_rotations = list_size - n_rotations;

    // inicializando o noh atual no primeiro noh
    current = l->beginning;
    int count = 1;

    // enquanto o numero de rotacoes for menor que o contador e o noh
    // atual diferente de nulo, atual atualiza para o proximo noh
    while (count < n_rotations && current != NULL) {
        current = current->next;
        count++;
    }
    if (current == NULL) {
        return;
    }

    node_x = current;

    temp->next = l->beginning;

    l->beginning = node_x->next;

    node_x->next = NULL;

}

int main() {
    int n_cases;
    scanf("%d", &n_cases);

    int list_size, n_rotations, list_elem;

    for (int i = 0; i < n_cases; i++) {
        scanf("%d", &list_size);

        scanf("%d", &n_rotations);

        list_t *l = create();

        int count = 0;
        while (count < list_size) {
            scanf("%d", &list_elem);
            insert(l, list_elem);
            count++;
        }
        rotate_list(l, n_rotations, list_size);
        print_list(l);
        destroy(l);
    }

    return 0;
}
