#ifndef GRANDES_NUMEROS_FUNCS_H
#define GRANDES_NUMEROS_FUNCS_H

#include "doubly_linked_list.h"

int *read_number (int *size);

void free_all(list_t *l_result, list_t *l1, list_t *l2);

list_t *sum (list_t *l1, list_t *l2);

int is_bigger(list_t *l1, list_t *l2, int n1_size, int n2_size);

int is_smaller(list_t *l1, list_t *l2, int n1_size, int n2_size);

int is_equal (list_t *l1, list_t *l2, int n1_size, int n2_size);


#endif //GRANDES_NUMEROS_FUNCS_H
