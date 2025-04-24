#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stack.h"

struct stack {
    int top;
    void **itens;
    int elem_size;
};

stack_t *create(int elem_size) {
    stack_t *p = (stack_t *) malloc(sizeof(stack_t));
    assert(p != NULL);

    p->itens = (void **) malloc(sizeof(void *) * stack_size);
    assert( p != NULL);

    p->top = -1;
    p->elem_size = elem_size;

    return p;
}

void destroy(stack_t *p) {
    while (p->top >= 0) {
        free(p->itens[p->top]);
        p->top -= 1;
    }
    if (p->itens != NULL) {
        free(p->itens);
    }
    if (p != NULL) {
        free(p);
    }
    p = NULL;
}

int is_full(stack_t *p) {
    assert(p != NULL);

    if (p->top == stack_size - 1) {
        return 1;
    }

    return 0;
}

int is_empty(stack_t *p) {
    assert(p != NULL);

    if (p->top == -1) {
        return 1;
    }

    return 0;
}

int push(stack_t *p, void *x) {
    assert(p != NULL);

    if (is_full(p) == 1) {
        return -1;
    }

    p->top = p->top + 1;
    p->itens[p->top] = (void *) malloc(sizeof(p->elem_size));
    assert(p->itens[p->top] != NULL);

    memcpy(p->itens[p->top], x, p->elem_size);

    return 1;
}

int pop(stack_t *p, void *x) {
    assert(p != NULL);

    if (is_empty(p) == 1) {
        return -1;
    }

    memcpy(x, p->itens[p->top], p->elem_size);
    free(p->itens[p->top]);
    p->top -= 1;

    return 1;
}

int top(stack_t *p, void *x) {
    assert(p != NULL);

    if (is_empty(p) == 1) {
        return -1;
    }
    memcpy(x, p->itens[p->top], p->elem_size);

    return 1;
}
