#ifndef GRANDES_NUMEROS_DOUBLY_LINKED_LIST_H
#define GRANDES_NUMEROS_DOUBLY_LINKED_LIST_H

typedef int elem;
typedef struct list list_t;
typedef struct node node_t;

list_t *create();

void free_list(list_t *l);

int insert_elem(list_t *l, elem x);

void print_inv_list(list_t *l);


#endif //GRANDES_NUMEROS_DOUBLY_LINKED_LIST_H
