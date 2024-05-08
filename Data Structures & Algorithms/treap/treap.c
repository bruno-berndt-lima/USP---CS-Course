#include <stdio.h>
#include <stdlib.h>
#include "treap.h"

struct node {
    elem data;
    int priority;
    node_t *right_child, *left_child;
};

tree_t *create() {
    tree_t *t = (tree_t *) malloc(sizeof(tree_t));
    t->root = NULL;

    return t;
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

node_t *right_rotate(node_t *y) {
    node_t *x = y->left_child,  *T2 = x->right_child;

    x->right_child = y;
    y->left_child = T2;

    return x;
}

node_t *left_rotate(node_t *x) {
    node_t *y = x->right_child, *T2 = y->left_child;

    y->left_child = x;
    x->right_child = T2;

    return y;
}

int search(node_t *root, elem x) {
    if (root == NULL) {
        return 0;
    } else if (root->data == x) {
        return 1;
    } else if (x < root->data) {
        return search(root->left_child, x);
    } else {
        return search(root->right_child, x);
    }
}

int insert(node_t **root, elem x, int priority) {
    if (*root == NULL) {
        *root = (node_t *) malloc(sizeof(node_t));
        (*root)->data = x;
        (*root)->priority = priority;
        (*root)->left_child = NULL;
        (*root)->right_child = NULL;
        return 1;
    } else if (x == (*root)->data) {
        printf("Elemento ja existente\n");
        return 0;
    } else if (x < (*root)->data) {
        insert(&(*root)->left_child, x, priority);
        if ((*root)->left_child->priority > (*root)->priority) {
            (*root) = right_rotate((*root));
        }
        return 1;

    } else {
        insert(&(*root)->right_child, x, priority);
        if ((*root)->right_child->priority > (*root)->priority) {
            (*root) = left_rotate((*root));
        }
        return 1;

    }
}

node_t* delete_node(node_t *root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->data) {
        root->left_child = delete_node(root->left_child, key);
    }
    else if (key > root->data) {
        root->right_child = delete_node(root->right_child, key);
    } 
    else {
        if (root->left_child == NULL && root->right_child == NULL) {
            free(root);
            root = NULL;
        } else if (root->left_child && root->right_child) {
            root = left_rotate(root);
            root->left_child = delete_node(root->left_child, key);
        } else {
            node_t *child = (root->left_child) ? root->left_child : root->right_child;
            node_t *curr = root;
            root = child;
            free(curr);
        }
    }

    return root;
}

void pre_order(node_t *root) {
    if (root != NULL) {
        printf("(%d, %d) ", root->data, root->priority);
        pre_order(root->left_child);
        pre_order(root->right_child);
    }
}

void in_order(node_t *root) {
    if (root != NULL) {
        in_order(root->left_child);
        printf("(%d, %d) ", root->data, root->priority);
        in_order(root->right_child);
    }
}

void post_order(node_t *root) {
    if (root != NULL) {
        post_order(root->left_child);
        post_order(root->right_child);
        printf("(%d, %d) ", root->data, root->priority);
    }
}

void print_current_level(node_t *root, int level) {
    if (root == NULL) {
        return;
    }
    if (level == 1) {
        printf("(%d, %d) ", root->data, root->priority);
    }
    else if (level > 1) {
        print_current_level(root->left_child, level - 1);
        print_current_level(root->right_child, level - 1);
    }
}
void level_order(node_t *root) {
    int h = height(root);

    for (int i = 1; i <= h; i++) {
        print_current_level(root, i);
    }
}




