#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "binary_search_tree.h"

struct node {
    elem data;
    node_t *right_child, *left_child;
};

tree_t *create() {
    tree_t *t = (tree_t *) malloc(sizeof(tree_t));
    t->root = NULL;

    return t;
}

int is_empty(tree_t *t) {
    assert(t != NULL);

    if (t->root == NULL) {
        return 1;
    }

    return 0;
}

void destroy(node_t *root) {
    if (root != NULL) {
        destroy(root->left_child);
        destroy(root->right_child);
        free(root);
    }
}

void print_tree(node_t *root) {
    if (root != NULL) {
        printf("%d(", root->data);
        print_tree(root->left_child);
        printf(",");
        print_tree(root->right_child);
        printf(")");
    } else {
        printf("null");
    }
}

int height(node_t *root) {
    if (root == NULL) {
        return 0;
    }
    int left_height = 1 + height(root->left_child);
    int right_height = 1 + height(root->right_child);

    if (left_height > right_height) {
        return left_height;
    } else {
        return right_height;
    }
}

node_t *search(node_t *root, elem x) {
    if (root == NULL) {
        return NULL;
    } else if (root->data == x) {
        return root;
    } else if (x < root->data) {
        return search(root->left_child, x);
    } else {
        return search(root->right_child, x);
    }
}

int insert(node_t **root, elem x) {
    if (*root == NULL) {
        *root = (node_t *) malloc(sizeof(node_t));
        (*root)->data = x;
        (*root)->left_child = NULL;
        (*root)->right_child = NULL;
        return 1;
    } else if (x == (*root)->data) {
        return 0;
    } else if (x < (*root)->data) {
        return insert(&(*root)->left_child, x);
    } else {
        return insert(&(*root)->right_child, x);
    }
}

int remove_elem(node_t **root, elem x) {
    if (*root == NULL) {
        return 0;
    } else if (x < (*root)->data) {
        return remove_elem(&(*root)->left_child, x);
    } else if (x > (*root)->data) {
        return remove_elem(&(*root)->right_child, x);
    } else {
        if ((*root)->left_child == NULL && (*root)->right_child == NULL) {
            free(*root);
            *root = NULL;
            return 1;
        } else if ((*root)->left_child == NULL) {
            node_t *aux = *root;
            *root = (*root)->right_child;
            free(aux);
            return 1;
        } else if ((*root)->right_child == NULL) {
            node_t *aux = *root;
            *root = (*root)->left_child;
            free(aux);
            return 1;
        } else {
            node_t *aux = (*root)->left_child;
            while (aux->right_child != NULL) {
                aux = aux->right_child;
            }
            (*root)->data = aux->data;
            return remove_elem(&(*root)->left_child, aux->data);
        }
    }
}

void pre_order(node_t *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        pre_order(root->left_child);
        pre_order(root->right_child);
    }
}

void in_order(node_t *root) {
    if (root != NULL) {
        in_order(root->left_child);
        printf("%d ", root->data);
        in_order(root->right_child);
    }
}

void post_order(node_t *root) {
    if (root != NULL) {
        post_order(root->left_child);
        post_order(root->right_child);
        printf("%d ", root->data);
    }
}
