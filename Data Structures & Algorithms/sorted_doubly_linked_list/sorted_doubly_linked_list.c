#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "sorted_linked_list.h"

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

    while (aux != NULL && x > aux->info) {
        previous = aux;
        aux = aux->next;
    }

    // caso onde x ja existe na lista
    if (aux != NULL && x == aux->info) {
        free(p);
        return 0;
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

int remove_elem(list_t *l, elem x) {
    assert(l != NULL);

    node_t *p = l->beginning;
    node_t *previous = NULL;

    while (p != NULL && x > p->info) {
        previous = p;
        p = p->next;
    }

    if (p == NULL || p->info != x) {
        return 0;
    }

    // remocao do primeiro elemento
    if (previous == NULL) {
        l->beginning = l->beginning->next;
        if (l->beginning != NULL) {
            l->beginning->prev = NULL;
        } else {
            l->end = NULL;
        }
        free(p);
    } else { // remocao de elemento no meio ou no fim
        if (p->next == NULL) { //remocao do fim da lista
            l->end = p->prev;
            previous->next = NULL;
            free(p);
        } else { // remocao do meio da lista
            previous->next = p->next;
            p->next->prev = previous;
            free(p);
        }
    }

    return 1;
}

void print_list(list_t *l) {
    assert(l != NULL);

    node_t *p = l->beginning;

    while (p != NULL) {
        printf("%d ", p->info);
        p = p->next;
    }
    printf("\n");
}

void print_inv_list(list_t *l) {
    assert(l != NULL);
    node_t *p = l->end;

    while (p != NULL) {
        printf("%d ", p->info);
        p = p->prev;
    }
    printf("\n");
}


