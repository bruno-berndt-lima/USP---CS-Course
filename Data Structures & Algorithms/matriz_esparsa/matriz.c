#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matriz.h"

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
    }
    if (root->data == x) {
        return root;
    }
    node_t *p = search(root->left_child, x);
    if (p == NULL) {
        p = search(root->right_child, x);
    }

    return p;
}

node_t *search_parent(node_t *root, elem x) {
    if (root == NULL) {
        return NULL;
    }
    if (root->left_child != NULL && root->left_child->data == x) {
        return root;
    }
    if (root->right_child != NULL && root->right_child->data == x) {
        return root;
    }
    node_t *p = search_parent(root->left_child, x);
    if (p == NULL) {
        p = search_parent(root->right_child, x);
    }

    return p;
}

// se o pai == -1 insere na raiz
// caso contrario, insere na esquerda de pai
int insert_left(tree_t *t, elem x, elem parent) {
    node_t *p = (node_t *) malloc(sizeof(node_t));
    p->left_child = NULL;
    p->right_child = NULL;
    p->data = x;

    if (parent == -1) {
        if (t->root == NULL) {
            t->root = p;
        } else {
            free(p);
            return 0;
        }
    } else {
        node_t *aux = search(t->root, parent);
        if (aux != NULL && aux->left_child == NULL) {
            aux->left_child = p;
        } else {
            free(p);
            return 0;
        }
    }

    return 1;
}

int insert_right(tree_t *t, elem x, elem parent) {
    node_t *p = (node_t *) malloc(sizeof(node_t));
    p->left_child = NULL;
    p->right_child = NULL;
    p->data = x;

    if (parent == -1) {
        if (t->root == NULL) {
            t->root = p;
        } else {
            free(p);
            return 0;
        }
    } else {
        node_t *aux = search(t->root, parent);
        if (aux != NULL && aux->right_child == NULL) {
            aux->right_child = p;
        } else {
            free(p);
            return 0;
        }
    }

    return 1;
}

int remove_elem(tree_t *t, elem x) {
    node_t *p, *parent;
    int is_left_child;

    // setar p e pai
    if (t->root != NULL && t->root->data == x) {
        p = t->root;
        parent = NULL;
    } else {
        parent = search_parent(t->root, x);
        if (parent != NULL) {
            if (parent->left_child != NULL && parent->left_child->data == x) {
                p = parent->left_child;
                is_left_child = 1;
            } else {
                p = parent->right_child;
                is_left_child = 0;
            }
        } else {
            p = NULL;
        }
    }

    // fazer a remocao de p
    if (p == NULL) {
        return 0;
    } else {
        // remocao de p como folha
        if (p->left_child == NULL && p->right_child == NULL) {
            if (parent == NULL) {
                t->root = NULL;
            } else {
                if (is_left_child) {
                    parent->left_child = NULL;
                } else {
                    parent->right_child = NULL;
                }
            }
            free(p);

            return 1;
        } else {
            if (p->left_child != NULL) {
                p->data = p->left_child->data;
                p->left_child->data = x;
            } else {
                p->data = p->right_child->data;
                p->right_child->data = x;
            }
            return remove_elem(t, x);
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