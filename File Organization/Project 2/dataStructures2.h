#ifndef TRABALHO_2_DATASTRUCTURES2_H
#define TRABALHO_2_DATASTRUCTURES2_H

//--------------stack--------------------
typedef struct stack {
    int top;
    int *RRN;
} Stack;

Stack *create(int size);
int is_empty(Stack *stack);
int push(Stack *p, int rrn);
int pop(Stack *p, int *x);
int top(Stack *p, int *x);
void destroy(Stack *p);


#endif //TRABALHO_2_DATASTRUCTURES2_H
