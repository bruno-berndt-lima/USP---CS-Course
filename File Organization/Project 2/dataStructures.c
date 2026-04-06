#include<stdio.h>
#include<stdlib.h>
#include"dataStructures.h"


//---------------------funções para a pilha-----------------
rmStack *createStack(long int capacity) {
    rmStack *stack = malloc(sizeof(rmStack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->id = malloc(capacity * sizeof(int));

    return stack;
}

int isEmpty(rmStack *stack) {
    return(stack->top == -1);
}

void stackPush(rmStack *stack, int id) {
    if(stack->top == stack->capacity - 1) {
        printf("Erro ao inserir na stack");
        return;
    }
    stack->id[(stack->top) + 1] = id;
    stack->top = stack->top + 1;
}

int stackPop(rmStack *stack) {
    if(isEmpty(stack)) {
        return -1;
    }
    stack->top = stack->top - 1;
    return stack->id[stack->top + 1];
    
}

int getTop(rmStack *stack) {
    return stack->top;
}

int getTopid(rmStack *stack) {
    return stack->id[stack->top];
}

void stackDestroy(rmStack *stack) {
    free(stack->id);
    free(stack);
}

//---------funções para a lista ligada----------------------------

RList *createList() {
    RList *list = malloc(sizeof(RList));
    list->qtyNodes = 0;
    list->head = NULL;
    
    return list;
}


void insertNodeList(RList *list, int id, int size, long int byteOffset) {
    Node *insert = malloc(sizeof(Node));
    insert->id = id;
    insert->size = size;
    insert->byteOffset = byteOffset;
    insert->next = NULL;

    if(list->head == NULL) {
        list->head = insert;
        list->qtyNodes = list->qtyNodes + 1;
        return;
    }

    Node *x = list->head;
    Node *temp = NULL;

    if(x->size < insert->size) {
        insert->next = x;
        list->head = insert;
        list->qtyNodes = list->qtyNodes + 1;
        return;
    }
    
    while(x->next != NULL && insert->size < x->next->size) {
        x = x->next;
    }

    temp = x->next;
    x->next = insert;
    insert->next = temp;
    list->qtyNodes = list->qtyNodes + 1;

}

long int getFirstNode(RList *list, int *key, int *size) {
    Node *x = list->head;
    *key = x->id;
    *size = x->size;
    long int offset = x->byteOffset;

    return offset;
}

long int removeFirstNode(RList *list, int *key) {
    if(list->head == NULL)
        return -1;
    Node *x = list->head;
    *key = x->id;
    long int offset = x->byteOffset;
    list->head = x->next;
    free(x);
    return offset;
}

void printList(RList *list) {
    Node *x = list->head;
    while(x != NULL) {
        printf("id %d, size %d, byteoffset %ld\n", x->id, x->size, x->byteOffset);
        x = x->next;
    }
}

void destroyList(RList *list) {
    Node *x = list->head;
    while(x != NULL) {
        Node *temp = x->next;
        free(x);
        x = temp;
    }
    free(list);
}