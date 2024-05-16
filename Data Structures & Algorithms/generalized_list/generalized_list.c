#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "generalized_list.h"

// cria um noh do tipo atomo e inicializa seu campos
node_t *Atom(elem x) {
    node_t *p = (node_t *) malloc(sizeof(node_t));
    p->type = 0;
    p->next = NULL;
    p->info.atom = x;

    return p;
}

// cria um noh do tipo sublista e inicializa seus campos
node_t *Sublist(node_t *sublist) {
    node_t *p = (node_t *) malloc(sizeof(node_t));
    p->type = 1;
    p->next = NULL;
    p->info.sublist = sublist;

    return p;
}

// concatena dois nos
node_t *concatenate(node_t *p, node_t *q) {
    assert(p != NULL);
    p->next = q;

    return p;
}

info_t head(node_t *p, int *type) {
    assert(p != NULL);
    *type = p->type;

    return p->info;
}

node_t *tail(node_t *p) {
    assert(p != NULL);

    return p->next;
}

void print(node_t *p) {
    if (p == NULL) {
        return;
    }
    printf("(");
    while (p != NULL) {
        if (p->type == 0) {
            printf("%d", p->info.atom);
        } else {
            print(p->info.sublist);
        }
        if (p->next != NULL) {
            printf(", ");
        }
        p = p->next;
    }
    printf(")");
}

void print_list(node_t *p) {
    print(p);
    printf("\n");
}

int list_depth(node_t *p) {
    if (p == NULL) {
        return 0;
    }

    int count;

    if (p->type == 0) {
        count = 1;
    } else {
        count = 1 + list_depth(p->info.sublist);
    }

    int aux = list_depth(p->next);
    if (aux > count) {
        return aux;
    }

    return count;
}

int list_contains_elem(node_t *p, elem x) {
    if (p == NULL) {
        return 0;
    }

    if (p->type == 0) {
        if (p->info.atom == x) {
            return 1;
        }
        return list_contains_elem(p->next, x);
    } else {
        if (list_contains_elem(p->info.sublist, x)) {
            return 1;
        }
        return list_contains_elem(p->next, x);
    }
}

int equals(node_t *p, node_t *q) {
    if (p == NULL && q == NULL) {
        return 1;
    }
    if (p == NULL || q == NULL) {
        return 0;
    }
    if (p->type == 0 && q->type == 0 && p->info.atom == q->info.atom) {
        return equals(p->next, q->next);
    }
    if (p->type == 1 && q->type == 1 && equals(p->info.sublist, q->info.sublist)) {
        return equals(p->next, q->next);
    }

    return 0;
}

void free_list(node_t *p) {
    node_t *aux;

    while (p != NULL) {
        // se for uma sublista, primeiro libera os elementos da sublista
        if (p->type == 1) {
            free_list(p->info.sublist);
        }
        aux = p;
        p = p->next;
        free(aux);
    }
}





