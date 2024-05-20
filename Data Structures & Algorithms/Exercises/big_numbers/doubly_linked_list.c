#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "doubly_linked_list.h"

typedef struct node node_t;

struct node {
    elem info;
    node_t *prev, *next;
};

struct list {
    node_t *beginning, *end;
};

list_t *create() {
    list_t *p;
    p = (list_t *) malloc(sizeof(list_t));
    p->beginning = NULL;
    p->end = NULL;

    return p;
}

void free_list(list_t *l) {
    if (l != NULL) {
        node_t *aux = l->beginning;
        while (aux != NULL) {
            l->beginning = l->beginning->next;
            free(aux);
            aux = l->beginning;
        }
        free(l);
    }
}

int insert_elem(list_t *l, elem x) {
    assert(l != NULL);

    node_t *p = (node_t *) malloc(sizeof(node_t));
    p->info = x;
    p->next = NULL;
    p->prev = NULL;

    node_t *aux, *previous;
    previous = NULL;
    aux = l->beginning;

    while (aux != NULL) {
        previous = aux;
        aux = aux->next;
    }

    // inserindo no inicio, lista vazia ou
    // lista com elementos
    if (previous == NULL) {
        p->next = l->beginning;
        if (l->beginning != NULL) {
            l->beginning->prev = p;
        } else {
            l->end = p;
        }
        l->beginning = p;
    } else { // inserindo no meio ou fim da lista
        p->next = previous->next;
        previous->next = p;
        if (p->next != NULL) {
            p->next->prev = p;
        } else {
            l->end = p;
        }
        p->prev = previous;
    }

    return 1;
}

void print_inv_list(list_t *l) {
    assert(l != NULL);
    node_t *p = l->end;

    while (p != NULL) {
        printf("%d", p->info);
        p = p->prev;
    }
    printf("\n");
}


