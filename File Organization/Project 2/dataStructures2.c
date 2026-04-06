#include<stdio.h>
#include<stdlib.h>
#include <assert.h>
#include "dataStructures2.h"

//---------------------funções para a pilha---------------------//
Stack *create(int size) {
    Stack *p = malloc(sizeof(Stack));
    assert(p != NULL);
    p->top = -1;
    p->RRN = malloc(sizeof(int *) * size);

    return p;
}

int is_empty(Stack *p) {
    assert(p != NULL);
    if (p->top == -1) {
        return 1;
    }

    return 0;}

int push(Stack *p, int rrn) {
    assert(p != NULL);

    p->top = p->top + 1;
    p->RRN[p->top] = rrn;

    return 1;
}

int pop(Stack *p, int *x) {
    assert(p != NULL);

    if (is_empty(p) == 1) {
        return -1;
    }

    *x = p->RRN[p->top];
    p->top -= 1;

    return 1;
}

int top(Stack *p, int *x) {
    assert(p != NULL);

    if (is_empty(p) == 1) {
        return -1;
    }

    *x = p->RRN[p->top];

    return 1;
}

void destroy(Stack *p) {
    if (p != NULL) {
        free(p);
    }
    p = NULL;
}

//--------------------------------------------------------------//


//---------------------funções para a lista---------------------//
