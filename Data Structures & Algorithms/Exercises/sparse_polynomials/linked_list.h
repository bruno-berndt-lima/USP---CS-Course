#ifndef POLINOMIOS_ESPARSOS_LINKED_LIST_H
#define POLINOMIOS_ESPARSOS_LINKED_LIST_H

typedef int elem;
typedef struct list list_t;
typedef struct node node_t;

list_t *create();

list_t *polynomial_coef_sum(list_t *l[], int n_polynomials);

void destroy(list_t *l);

void insert(list_t *l, elem x);

int size(list_t *l);

void print_list(list_t *l);

#endif //POLINOMIOS_ESPARSOS_LINKED_LIST_H
