#ifndef AB_SOMA_NOS__BINARY_TREE_H
#define AB_SOMA_NOS__BINARY_TREE_H

typedef int elem;

typedef struct node node_t;

typedef struct tree {
    node_t *root;
} tree_t;

tree_t *create();

void destroy(node_t *root);

int sum_verify(node_t *root);

int insert_left(tree_t *t, elem x, elem parent, int id);

int insert_right(tree_t *t, elem x, elem parent, int id);

#endif //AB_SOMA_NOS__BINARY_TREE_H
