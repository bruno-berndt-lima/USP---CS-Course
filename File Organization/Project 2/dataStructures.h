#ifndef TRABALHO_2_DATASTRUCTURES_H
#define TRABALHO_2_DATASTRUCTURES_H
//--------------stack--------------------
typedef struct removedStack {
    int top;
    long int capacity;
    int *id;
} rmStack;

rmStack *createStack(long int capacity);
int isEmpty(rmStack *stack);
void stackPush(rmStack *stack, int id);
int stackPop(rmStack *stack);
int getTop(rmStack *stack);
void stackDestroy(rmStack *stack);

//--------------linked list--------------------

typedef struct listNode Node;
struct listNode {
    int id;
    int size;
    long int byteOffset;
    Node *next;
};

typedef struct removedList {
    int qtyNodes;
    Node *head;
} RList;


RList *createList();
void insertNodeList(RList *list, int id, int size, long int byteOffset);
long int getFirstNode(RList *list, int *key, int *size);
long int removeFirstNode(RList *list, int *key);
void printList(RList *list);
void destroyList(RList *list);



#endif