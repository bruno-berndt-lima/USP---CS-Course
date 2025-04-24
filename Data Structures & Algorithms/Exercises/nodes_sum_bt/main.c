// Bruno Berndt Lima - 12542550

#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

struct node {
    elem data;
    int id, right_child_id, left_child_id;
    node_t *right_child, *left_child;
};

int main() {
    tree_t *t = create();

    int n_nodes;
    scanf("%d ", &n_nodes);

    // criacao de um vetor de ponteiros do tipo node_t
    node_t **p = (node_t **) malloc(sizeof(node_t *) * n_nodes);
    for (int i = 0; i < n_nodes; i++) {
        p[i] = (node_t *) malloc(sizeof(node_t));
    }

    int count = 0;
    while (count < n_nodes) {
        scanf("%d %d %d %d", &p[count]->id, &p[count]->data, &p[count]->left_child_id, &p[count]->right_child_id);
        count++;
    }

    count = 0;
    while (count < n_nodes) {
        if (count == 0) {
            // se count == 0, entao sera inserido a raiz da arvore
            insert_left(t, p[p[count]->id]->data, -1, p[count]->id);
            count++;
            continue;
        }
        // se o id do filho da esquerda do noh atual for diferente de -1
        if (p[p[count - 1]->id]->left_child_id != -1) {
            // entao, insere o filho da esquerda
            insert_left(t, p[p[count - 1]->left_child_id]->data, p[p[count - 1]->id]->data, p[p[count - 1]->left_child_id]->id);
        }
        // se o id do filho da direita do noh atual for diferente de -1
        if (p[p[count - 1]->id]->right_child_id != -1) {
            // entao, insere o filho da direita
            insert_right(t, p[p[count - 1]->right_child_id]->data, p[p[count - 1]->id]->data, p[p[count - 1]->right_child_id]->id);
        }
        count++;
    }

    // se a funcao que faz a verificacao se a soma dos 2 nohs filho
    // eh igual ao valor do noh pai retornar 1, entao o valor eh igual
    if (sum_verify(t->root) == 1) {
        printf("VERDADEIRO\n");
    } else if (sum_verify(t->root) == -1) {
        printf("FALSO\n");
    }

    for (int i = 0; i < n_nodes; i++) {
        free(p[i]);
    }
    free(p);
    destroy(t->root);
    free(t);

    return 0;
}
