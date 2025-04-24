#include <stdio.h>
#include <stdlib.h>
#include "skip_lists.h"

struct node {
    int value;
    node_t **next;
};

struct skip_lists {
    int level;  // nivel atual do noh
    int max_level; // nivel maximo
    int n; // numeros de niveis de um noh
    node_t *upleft; // ponteiro para o noh header
};

node_t *new_node(int key, int level) {
     node_t *new_node = (node_t *) malloc(sizeof(node_t));

     if (new_node != NULL) {
         // cria um novo noh apontando para null
         new_node->value = key;
         new_node->next = malloc(sizeof(node_t *) * (level + 1));
         for (int i = 0; i < (level + 1); i++) {
             new_node->next[i] = NULL;
         }
     }
    return new_node;
}

skip_lists_t *create(int max_level, int n) {
    skip_lists_t *sl = (skip_lists_t *) malloc(sizeof(skip_lists_t));

    if (sl != NULL) {
        sl->max_level = max_level;
        sl->n = n;
        sl->level = 0;
        // cria o header com chave -1
        sl->upleft = new_node(-1, max_level);
    }

    return sl;
}

void destroy(skip_lists_t *sl) {
    if (sl == NULL) {
        return;
    }

    node_t *node, *current;
    current = sl->upleft->next[0];

    while (current != NULL) {
        node = current;
        current = current->next[0];
        free(node->next);
        free(node);
    }

    free(sl->upleft);
    free(sl);
}

int generate_level(skip_lists_t *sl) {
    int n = rand()/RAND_MAX;
    int level = 0;
    while (n < sl->n && level < sl->max_level) {
        level++;
        n = rand()/RAND_MAX;
    }

    return level;
}

int insert_elem(skip_lists_t *sl, int key) {
    if (sl == NULL) {
        return 0;
    }

    node_t *current = sl->upleft;
    //cria um vetor de nohs auxiliares apontando para null
    node_t **aux;
    aux = (node_t **) malloc(sizeof(node_t *) * (sl->max_level + 1));
    for (int i = 0; i < sl->max_level; i++) {
        aux[i] = NULL;
    }

    // partindo do maior nivel, vai ate o proximo noh enquanto a chave
    // for maior do que a do proximo noh, se nao insere o noh no vetor auxiliar
    // desce um nivel e continua a busca
    for (int i = sl->level; i >= 0 ; i--) {
        while (current->next[i] != NULL && current->next[i]->value < key) {
            current = current->next[i];
        }
        aux[i] = current;
    }

    // acessa o nivel 0 do proximo noh, onde o valor deve ser inserido
    current = current->next[0];

    // cria e insere um novo noh se a chave nao existir,
    // final da lista (current == NULL) ou entre aux[0] e current
    if (current == NULL || current->value != key) {
        // sorteia quantos niveis o novo noh tera
        int new_level = generate_level(sl);

        // cria um novo noh apontando para null
        node_t *new = new_node(key, new_level);
        if (new == NULL) {
            free(aux);
            return 0;
        }
        // se o nivel sorteado for maior do que o nivel
        // atual da skiplist, atualiza os novos niveis
        // do vetor auxiliar
        if (new_level > sl->level) {
            for (int i = sl->level + 1; i <= new_level; i++) {
                aux[i] = sl->upleft;
            }
            // atualiza o nivel da skiplist
            sl->level = new_level;
        }
        // insere o noh arrumando os ponteiros
        for (int i = 0; i <= new_level; i++) {
            new->next[i] = aux[i]->next[i];
            aux[i]->next[i] = new;
        }
        free(aux);

        return 1;
    }
    free(aux);

    return 0;
}

int search_elem(skip_lists_t *sl, int key) {
    if (sl == NULL) {
        return 0;
    }

    node_t *current = sl->upleft;

    // partindo do maior nivel, vai para o proximo noh
    // enquando a chave for maior do que a do proximo noh,
    // se nao desce um nivel e continua a busca
    for (int i = sl->level; i >= 0 ; i--) {
        while (current->next[i] != NULL && current->next[i]->value < key) {
            current = current->next[i];
        }
    }

    // acessa o nivel 0 do proximo noh, que eh onde a
    // chave desejada deve estar
    current = current->next[0];

    if (current != NULL && current->value == key) {
        return 1;
    } else {
        return 0;
    }
}

int remove_elem(skip_lists_t *sl, int key) {
    if (sl == NULL) {
        return 0;
    }

    node_t *current = sl->upleft;
    // cria um vetor de nohs auxiliares apontando para null
    node_t **aux;
    aux = (node_t **) malloc(sizeof(node_t *) * (sl->max_level + 1));

    for (int i = 0; i <= sl->max_level; i++) {
        aux[i] = NULL;
    }
    // partindo do maior nivel, vai para o proximo noh
    // enquando a chave for maior do que a do proximo noh,
    // se nao insere o noh no vetor auxiliar
    // desce um nivel e continua a busca
    for (int i = sl->level; i >= 0 ; i--) {
        while (current->next[i] != NULL && current->next[i]->value < key) {
            current = current->next[i];
        }
        aux[i] = current;
    }
    // acessa o nivel 0 do proximo noh, que eh onde a
    // chave desejada deve estar
    current = current->next[0];

    if (current != NULL && current->value == key) {
        // comecando no nivel 0, se o vetor auxliar
        // aponta para o noh a ser removido, ele apontara
        // para o proximo noh
        for (int i = 0; i <= sl->level; i++) {
            if (aux[i]->next[i] != current) {
                break;
            }
            aux[i]->next[i] = current->next[i];
        }
        // remover os niveis sem elementos
        while (sl->level > 0 && sl->upleft->next[sl->level] == NULL) {
            sl->level--;
        }
        free(current->next);
        free(current);
        free(aux);

        return 1;
    }
    free(aux);

    return 0;
}

