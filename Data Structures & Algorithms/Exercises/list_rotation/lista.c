#include <stdlib.h>
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

void print_list(list_t *l) {
    if (l != NULL) {
        node_t *p = l->beginning;
        while (p != NULL) {
            printf("%d ", p->info);
            p = p->next;
        }
    }
    printf("\n");
}
