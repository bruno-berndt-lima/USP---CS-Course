#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skip_lists.h"

struct node {
    char entry[50];
    char definition[140];
    node_t **next;
};

struct skip_lists {
    int level;  // nivel atual do noh
    node_t *header; // ponteiro para o noh header
};


char *read_line() {
    char *str = NULL;
    int counter = 0;
    char c;

    do {
        c = getchar();
        str = realloc(str, sizeof (char) * (counter + 1));
        str[counter++] = c;
    } while (c != '\n' && c != EOF && c != '\r');

    str[--counter] = '\0';

    return str;
}

// funcao de troca da definicao de uma palavra
int change_definition(skip_lists_t *sl, char entry[50], char definition[140]) {
    if (sl == NULL) {
        return 0;
    }

    // cria um noh apontando para o header da skiplist
    node_t  *current = sl->header;

    // comecando do ultimo level ate chegar em 1
    for (int i = sl->level; i >= 1; i--) {
        // enquanto o proximo for diferente de nulo e nao encontrar a palavra a ser trocada
        // avanca para o proximo
        while (current->next[i] != NULL && strcmp(current->next[i]->entry, entry) < 0) {
            current = current->next[i];
        }
    }
    current = current->next[1];

    // se nao foi encontrada a palavra a ser trocada
    // entao, eh uma operacao invalida
    if (strcmp(current->entry, entry) != 0) {
        printf("OPERACAO INVALIDA\n");
    } else { // caso contrario troca a definicao
        strcpy(current->definition, definition);
    }

    return 1;
}

// funcao para imprimir todas as palavras iniciadas por tal caracter
// e suas respectivas definicoes
int print(skip_lists_t *sl, char character) {
    if (sl == NULL) {
        return 0;
    }
    // cria um noh apontando para o header da skiplist
    node_t *current = sl->header;

    // comecando do ultimo level ate chegar em 1
    for (int i = sl->level; i >= 1 ; i--) {
        // enquanto o proximo for diferente de nulo e nao encontrar o caracter desejado
        // avanca para o proximo
        while (current->next[i] != NULL && current->next[i]->entry[0] < character) {
            current = current->next[i];
        }
    }
    current = current->next[1];

    // se chegou ao fim da skiplist e nao foi encontrada nenhuma palavra
    // iniciada por aquele caracter, entao nao ha palavras iniciadas
    // por aquele caracter
    if (current == NULL) {
        printf("NAO HA PALAVRAS INICIADAS POR %c\n", character);
        return 0;
    }

    // caso contrario, enquanto o noh atual for diferente de nulo
    // e existir palavras iniciadas pelo caracter, imprime as palavras
    while (current != NULL && current->entry[0] == character) {
        printf("%s %s\n", current->entry, current->definition);
        current = current->next[1];
    }

    return 1;
}

