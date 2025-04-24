#ifndef ROTACAO_DE_LISTA_LISTA_H
#define ROTACAO_DE_LISTA_LISTA_H

typedef int elem;
typedef struct list list_t;
typedef struct node node_t;

list_t *create();

void destroy(list_t *l);

void insert(list_t *l, elem x);

void print_list(list_t *l);

#endif //ROTACAO_DE_LISTA_LISTA_H
