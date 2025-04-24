#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "priority_queue_heap.h"

struct node {
    elem data;
    int priority;
};

struct queue {
    int n; // num de elementos
    node_t *heap[MAX_HEAP_SIZE];
};

// sobe o elemento i no heap
void up(queue_t *q, int i) {
    int j; // indice do pai de i
    node_t *temp;

    j = (int) ((i - 1) / 2);

    // se i tem pai e que seja menor que i
    if (j >= 0 && q->heap[i]->priority > q->heap[j]->priority) {
        // troca ambos
        temp = q->heap[i];
        q->heap[i] = q->heap[j];
        q->heap[j] = temp;

        // e continua subindo esse elemento
        up(q, j);
    }
}

// desce o elemento i no heap de tamanho n
void down(queue_t *q, int i) {
    int j; // indice do filho de i
    node_t *temp;

    j = 2 * i + 1;

    // se i tem filhos
    if (j < q->n) {
        // se i tem filho na direita
        if (j < q->n - 1) {
            // pega o maior filho
            if (q->heap[j]->priority < q->heap[j + 1]->priority) {
                j++;
            }
        }
        // e compara com o pai
        if (q->heap[j]->priority > q->heap[i]->priority) {
            temp = q->heap[i];
            q->heap[i] = q->heap[j];
            q->heap[j] = temp;

            // e continua descendo o mesmo elemento
            down(q, j);
        }
    }
}

queue_t *create() {
    queue_t *q = (queue_t *) malloc(sizeof(queue_t));
    q->n = 0;

    return q;
}

// inserir e remover tem complexidade de O(log_2 n)
int insert(queue_t *q, elem key, int priority) {
    if (!is_full(q)) {
        node_t *p = (node_t *) malloc(sizeof(node_t));
        p->data = key;
        p->priority = priority;
        q->heap[q->n] = p;
        up(q, q->n);
        q->n++;
        return 1;
    }

    return 0;
}

int remove_elem(queue_t *q, elem *key) {
    if (!is_empty(q)) {
        *key = q->heap[0]->data;
        free(q->heap[0]);
        q->n--;
        q->heap[0] = q->heap[q->n];
        down(q, 0);
        return 1;
    }

    return 0;
}

int is_empty(queue_t *q) {
    assert(q != NULL);

    return q->n == 0;
}

int is_full(queue_t *q) {
    assert(q != NULL);

    return q->n == MAX_HEAP_SIZE;
}

void destroy(queue_t *q) {
    for (int i = 0; i < q->n; i++) {
        free(q->heap[i]);
    }
    free(q);
}
