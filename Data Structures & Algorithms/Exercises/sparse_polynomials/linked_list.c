#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "linked_list.h"

typedef struct node node_t;

struct node {
    elem info;
    node_t *next;
};

struct list {
    node_t *beginning, *end;
    int list_size;
};

// funcao que ira calcular a soma dos coeficientes de um polinomio
list_t *polynomial_coef_sum(list_t *l[], int n_polynomials) {
    node_t *p[n_polynomials];
    list_t *l_result = create();

    int soma = 0, count = 0, list_size = 0, aux;

    for (int i = 0; i < n_polynomials; ++i) {
        // inicializando cada ponteiro para o inicio de cada lista
        p[i] = l[i]->beginning;

        // list_size sera usado para controlar o loop de
        // soma dos coeficientes, a partir da maior lista
        // que sera encontrada a seguir no if/else
        aux = list_size;
        list_size = size(l[i]);
        if(list_size > aux) {
            continue;
        } else {
            list_size = aux;
        }
    }

    while (count < list_size) {
        for (int i = 0; i < n_polynomials; i++) {
            // para cada polinomio, os coeficientes de mesmo grau,
            // ou seja, mesma posicao na lista encadeada, serao somados
            // e atribuidos a variavel soma
            if(p[i] != NULL) {
                soma += p[i]->info;
                p[i] = p[i]->next;
            }
        }
        insert(l_result, soma);
        soma = 0;
        count++;
    }

    return l_result;
}

list_t *create() {
    list_t *l;
    l = (list_t *) malloc(sizeof(list_t));

    if (l != NULL) {
        l->beginning = NULL;
        l->end = NULL;
        l->list_size = 0;
    }

    return l;
}

void destroy(list_t *l) {
    if (l != NULL) {
        node_t *p = l->beginning;
        while (p != NULL) {
            l->beginning = p->next;
            free(p);
            p = l->beginning;
        }
        free(l);
    }
}

void insert(list_t *l, elem x) {
    if (l != NULL) {

        node_t *p = (node_t *) malloc(sizeof(node_t));
        p->info = x;
        p->next = NULL;

        //lista vazia
        if (l->beginning == NULL) {
            l->beginning = p;
        } else {    //lista com pelo menos um elemento
            l->end->next = p;
        }
        l->end = p;

        l->list_size++;
    }
}

int size(list_t *l) {
    if (l != NULL) {
        return l->list_size;
    }
    return 0;
}

void print_list(list_t *l) {
    assert(l != NULL);
    node_t *p = l->beginning;

    printf("(");
    while (p != NULL) {
        if(p->next != NULL) {
            printf("%d,", p->info);
        } else {
            printf("%d)", p->info);
        }
        p = p->next;
    }
    printf("\n");
}

