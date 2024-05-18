#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

struct node {
    int id;
    elem data;
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

// funcao para verificar se o valor da soma dos nohs filhos
// eh igual ao valor do noh pai
int sum_verify(node_t *root) {
    // se a raiz passada no parametro da funcao for diferente de nula
    if (root != NULL) {
        // se o filho da esquerda ou direita for nulo, retorna 0
        if (root->left_child == NULL || root->right_child == NULL) {
            return 0;
        }
        // se a soma dos nohs filhos for diferente do valor do noh pai, retorna -1
        if (root->data != root->left_child->data + root->right_child->data) {
            return -1;
        }
        // caso contrario, chama recursivamente a funcao para os dois filhos
        sum_verify(root->left_child);
        sum_verify(root->right_child);
    }
    return 1;
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

int insert_left(tree_t *t, elem x, elem parent, int id) {
    node_t *p = (node_t *) malloc(sizeof(node_t));
    p->left_child = NULL;
    p->right_child = NULL;
    p->data = x;
    p->id = id;

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

int insert_right(tree_t *t, elem x, elem parent, int id) {
    node_t *p = (node_t *) malloc(sizeof(node_t));
    p->left_child = NULL;
    p->right_child = NULL;
    p->data = x;
    p->id = id;

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
