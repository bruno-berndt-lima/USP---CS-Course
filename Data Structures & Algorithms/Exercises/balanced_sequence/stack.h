#ifndef SEQUENCIA_BALANCEADA_STACK_H
#define SEQUENCIA_BALANCEADA_STACK_H

#define stack_size 400

typedef struct stack stack_t;

stack_t *create(int elem_size);

void destroy(stack_t *p);

int is_full(stack_t *p);

int is_empty(stack_t *p);

int push(stack_t *p, void *x);

int pop(stack_t *p, void *x);

int top(stack_t *p, void *x);


#endif //SEQUENCIA_BALANCEADA_STACK_H
