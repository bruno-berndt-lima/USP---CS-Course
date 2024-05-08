#ifndef ARVORES_TREAPS_TREAP_H
#define ARVORES_TREAPS_TREAP_H

typedef int elem;

typedef struct node node_t;

typedef struct tree {
    node_t *root;
} tree_t;

tree_t *create();

void destroy(node_t *root);

void print_tree(node_t *root);

int height(node_t *root);

int search(node_t *root, elem x);

int insert(node_t **root, elem x, int priority);

node_t* delete_node(node_t * root, int key);

void pre_order(node_t *root);

void in_order(node_t *root);

void post_order(node_t *root);

void level_order(node_t *root);

#endif //ARVORES_TREAPS_TREAP_H
