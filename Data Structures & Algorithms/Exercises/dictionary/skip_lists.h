#ifndef DICIONARIO_PROJ1_ALG_SKIP_LISTS_H
#define DICIONARIO_PROJ1_ALG_SKIP_LISTS_H

typedef struct node node_t;

typedef struct skip_lists skip_lists_t;

skip_lists_t *create();

void destroy(skip_lists_t *sl);

int insert_elem(skip_lists_t *sl, char entry[50], char definition[140]);

int search(skip_lists_t *sl, char entry[50]);

int remove_elem(skip_lists_t *sl, char entry[50]);

#endif //DICIONARIO_PROJ1_ALG_SKIP_LISTS_H
