#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stack.h"

struct stack {
    int top;
    elem itens[stack_size];
};

stack_t *create() {
    stack_t *p = (stack_t *) malloc(sizeof(stack_t));
    assert(p != NULL);

    p->top = -1;

    return p;
}

void destroy(stack_t *p) {
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

int push(stack_t *p, elem x) {
    assert(p != NULL);

    if (is_full(p) == 1) {
        return -1;
    }

    p->top = p->top + 1;
    p->itens[p->top] = x;

    return 1;
}

int pop(stack_t *p, elem *x) {
    assert(p != NULL);

    if (is_empty(p) == 1) {
        return -1;
    }

   *x = p->itens[p->top];
    p->top -= 1;

    return 1;
}

int top(stack_t *p, elem *x) {
    assert(p != NULL);

    if (is_empty(p) == 1) {
        return -1;
    }

    *x = p->itens[p->top];

    return 1;
}
