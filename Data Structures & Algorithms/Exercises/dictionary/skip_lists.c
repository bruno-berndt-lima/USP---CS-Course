#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skip_lists.h"

#define MAX_LEVEL 20

struct node {
    char entry[50];
    char definition[140];
    node_t **next;
};

struct skip_lists {
    int level;  // nivel atual do noh
    node_t *header; // ponteiro para o noh header
};

node_t *create_new_node(int level) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));

    if (new_node != NULL) {
        // cria um novo noh apontando para null
        new_node->next = malloc(sizeof(node_t *) * (level + 1));
        for (int i = 1; i < (level + 1); i++) {
            new_node->next[i] = NULL;
        }
    }
    return new_node;
}

skip_lists_t *create() {
    skip_lists_t *sl = (skip_lists_t *) malloc(sizeof(skip_lists_t));

    if (sl != NULL) {
        sl->level = MAX_LEVEL;
        // cria o header
        sl->header = create_new_node(MAX_LEVEL);
    }

    return sl;
}

void destroy(skip_lists_t *sl) {
    node_t *current_node = sl->header;
    while(current_node != sl->header) {
        node_t *next_node = current_node->next[1];
        free(current_node->next);
        free(current_node);
        current_node = next_node;
    }
    free(current_node->next);
    free(current_node);
    free(sl);
}

int generate_level() {
    int level = 1;
    while (rand() < RAND_MAX / 2 && level < MAX_LEVEL) {
        level++;
    }
    return level;
}

void skiplist_node_free(node_t *node) {
    if (node) {
        free(node->next);
        free(node);
    }
}

int search(skip_lists_t *sl, char entry[50]) {
    // inicializa um noh apontando para o header
    node_t *node = sl->header;
    int i;
    // comecando do ultimo level ate chegar em 1
    for (i = sl->level; i >= 1; i--) {
        // enquanto o proximo for diferente de nulo e nao encontrar a palavra desejada
        // avanca para o proximo
        while (node->next[i] != NULL && strcmp(node->next[i]->entry, entry) < 0) {
            node = node->next[i];
        }
    }
    // se o noh nao for nulo e encontrar a palavra desejada,
    // imprime a palavra e sua definicao
    if (node != NULL && strcmp(node->next[1]->entry, entry) == 0) {
        printf("%s %s\n", node->next[1]->entry, node->next[1]->definition);
        return 1;
    } else if (node != NULL && strcmp(node->next[1]->entry, entry) != 0) {
        printf("OPERACAO INVALIDA\n");
        return 0;
    }
    return 0;
}

int insert_elem(skip_lists_t *sl, char entry[50], char definition[140]) {
    // cria um noh para serem feitas as atualizacoes
    node_t *update[MAX_LEVEL + 1];
    // cria um noh apontando para o header
    node_t *node = sl->header;

    int i, level;
    // comecando do ultimo level ate chegar em 1
    for (i = sl->level; i >= 1; i--) {
        // enquanto o proximo for diferente de nulo e nao encontrar a
        // posicao correta da palavra desejada avanca para o proximo
        while (node->next[i] != NULL && strcmp(node->next[i]->entry, entry) < 0) {
            node = node->next[i];
        }
        // atualiza o noh update
        update[i] = node;
    }
    node = node->next[1];

    // se o noh for nulo ou entao nao encontrar nenhuma palavra igual a entrada
    if (node == NULL || strcmp(node->entry, entry) != 0) {
        // gera a quantidade de niveis aleatoriamente
        level = generate_level();

        // aloca espaco para um novo noh
        node = (node_t *) malloc(sizeof(node_t));

        // copia a palavra e sua definicao
        strcpy(node->entry, entry);
        strcpy(node->definition, definition);

        // aloca espaco para o proximo noh
        node->next = (node_t **) malloc(sizeof(node_t *) * (level + 1));
        // comecando de 1 ate a quantidade de niveis
        for (i = 1; i <= level; i++) {
            // proximo noh recebe o update
            node->next[i] = update[i]->next[i];
            // update recebe o noh alocado
            update[i]->next[i] = node;
        }
        return 1;
    } else if (strcmp(node->entry, entry) == 0) {
        // se ja existir uma palavra igual a entrada, entao eh uma operacao invalida
        printf("OPERACAO INVALIDA\n");
        return  0;
    }

    free(node->next);
    free(node);

    return 0;
}


int remove_elem(skip_lists_t *sl, char entry[50]) {
    int i;
    // cria um noh para serem feitas as atualizacoes
    node_t *update[MAX_LEVEL + 1];
    // cria um noh apontando para o header
    node_t *node = sl->header;

    // comecando do ultimo level ate chegar em 1
    for (i = sl->level; i >= 1; i--) {
        // enquanto o proximo for diferente de nulo e nao encontrar a
        // palavra desejada avanca para o proximo
        while (node->next[i] != NULL && strcmp(node->next[i]->entry, entry) < 0) {
            node = node->next[i];
        }
        // atualiza o noh update
        update[i] = node;
    }
    node = node->next[1];

    // se encontrou a palvra desejada
    if (strcmp(node->entry, entry) == 0) {
        // comecando de 1 ate a quantidade de niveis
        for (i = 1; i <= sl->level; i++) {
            // se o proximo de update for diferente do noh, da um break
            if (update[i]->next[i] != node) {
                break;
            }
            // atualiza o proximo de update para o proximo do noh
            update[i]->next[i] = node->next[i];
        }
        // da um free no noh
        skiplist_node_free(node);

        // enquanto o nivel for maior que 1 e o proximo noh do header for igual ao header
        while (sl->level > 1 && sl->header->next[sl->level] == sl->header) {
            // diminui uma quantidade de nivel
            sl->level--;
        }
        return 1;
    } else { // se nao encontrou a palavra desejada, entao eh uma operacao invalida
        printf("OPERACAO INVALIDA\n");
        return 0;
    }

}
