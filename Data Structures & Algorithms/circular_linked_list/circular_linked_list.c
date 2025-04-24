#include <stdio.h>
#include <stdlib.h>
#include "circular_linked_list.h"

typedef struct node node_t;

struct node {
    int value;
    struct node *next;
};

// estrutura lista
struct list {
    node_t *beginning;
    node_t *end;
    int size;
};

list_t *create() {
    list_t *l;
    l = (list_t *) malloc(sizeof(list_t));

    if (l != NULL) {
        l->beginning = NULL;
        l->end = NULL;
        l->size = 0;
    }

    return l;
}


int insert_at_beginning(list_t *list, int value) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));

    if (new_node != NULL) {
        new_node->value = value;
        // o próximo aponta para o início da list
        new_node->next = list->beginning;
        // new_node se torna o início da list
        list->beginning = new_node;
        // se end for nulo (list vazia), end aponta para new_node nó
        if(list->end == NULL) {
            list->end = new_node;
        }
        // end aponta para início
        list->end->next = list->beginning;
        list->size++;

        return 1;
    }

    return 0;
}

int insert_at_end(list_t *list, int value) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));

    if (new_node != NULL) {
        new_node->value = value;

        if (list->beginning == NULL) {
            list->beginning = new_node;
            list->end = new_node;
            list->end->next = list->beginning;
        } else {
            list->end->next = new_node;
            list->end = new_node;
            list->end->next = list->beginning;
        }
        list->size++;

        return 1;
    }

    return 0;
}

int insert_ordered(list_t *list, int value) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    node_t *aux = (node_t *) malloc(sizeof(node_t));

    if (new_node != NULL) {
        new_node->value = value;

        if (list->beginning == NULL || new_node->value < list->beginning->value) {
            insert_at_beginning(list, value);
            return 1;
        } else {
            aux = list->beginning;
            while (aux->next != list->beginning && new_node->value > aux->next->value) {
                aux = aux->next;
            }
            if (aux->next == list->beginning) {
                insert_at_end(list, value);
                return 1;
            } else {
                new_node->next = aux->next;
                aux->next = new_node;
                list->size++;
                return 1;
            }
        }
    }

    return 0;
}

int remove_elem(list_t *list, int value) {
    node_t *aux, *remove = NULL;

    if (list->beginning != NULL) {
        if (list->beginning == list->end && list->beginning->value == value) {
            list->beginning = NULL;
            list->end = NULL;
            list->size--;
            return 1;
        } else if (list->beginning->value == value) {
              remove =  list->beginning;
              list->beginning = remove->next;
              list->end->next = list->beginning;
              list->size--;

        } else {
            aux = list->beginning;
            while (aux->next != list->beginning && aux->next->value !=  value) {
                aux = aux->next;
            }
            if (aux->next->value == value) {
                if (list->end == aux->next) {
                    remove = aux->next;
                    aux->next = remove->next;
                    list->end = aux;
                } else {
                    remove = aux->next;
                    aux->next = remove->next;
                }
                list->size--;
            }
            return 1;
        }
    }

    return 0;
}

int search(list_t *list, int value) {
    node_t *aux = list->beginning;

    if (aux != NULL) {
        do {
            if (aux->value == value) {
                return 1;
            }
            aux = aux->next;
        } while (aux != list->beginning);
    }

    return 0;
}

void print_list(list_t *list) {
    node_t *node = list->beginning;

    if (node != NULL) {
        while (node != list->end) {
            printf("%d ", node->value);
            node = node->next;
        }
        printf("%d ", node->value);
    }
    printf("\n");
}
