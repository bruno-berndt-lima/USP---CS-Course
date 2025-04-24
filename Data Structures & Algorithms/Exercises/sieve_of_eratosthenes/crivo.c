#include <stdlib.h>
#include <stdio.h>
#include "crivo.h"

typedef struct node node_t;

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

        if (list_contains_elem(l, x) == 1) { // lista de elementos distintos
            return;
        }

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

void print_elem_from_list(list_t *l, int index) {
    if (l != NULL) {
        int i = 1;
        node_t *p = l->beginning;
        while (p != NULL) {
            if (index == i) {
                printf("%d ", p->info);
            }
            i++;
            p = p->next;
        }
    }
}

int  list_contains_elem(list_t *l, elem x) {
    if (l != NULL) {

        node_t *p = l->beginning;
        while (p != NULL) {
            if (p->info == x) {
                return 1;
            }
            p = p->next;
        }
    }
    return 0;

}

int remove_elem(list_t *l, elem x) {
    if (l != NULL) {

        node_t *previous = NULL;
        node_t *p = l->beginning;

        while (p != NULL) {
            if (p->info == x) {
                // remover do inicio
                if (p == l->beginning) {
                    l->beginning = l->beginning->next;
                    free(p);
                } else if (p == l->end) {   // remover do fim
                    l->end = previous;
                    l->end->next = NULL;
                    free(p);
                } else {    // remover do meio
                    previous->next = p->next;
                    free(p);
                }
                l->list_size--;
                return 1;
            } else {
                previous = p;
                p = p->next;
            }
        }
    }
    return 0;
}
