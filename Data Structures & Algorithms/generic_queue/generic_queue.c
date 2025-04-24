#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "generic_queue.h"

struct queue {
    int beginning, end, total;
    void **itens;
    int elem_size;
};

queue_t *create(int element_size) {
    queue_t *q;
    q = (queue_t *) malloc(sizeof(queue_t));
    assert(q != NULL);

    q->itens = malloc(sizeof(void *) * queue_size);
    assert(q->itens != NULL);

    q->elem_size = element_size;
    q->beginning = 0;
    q->end = 0;
    q->total = 0;

    return q;
}

int is_empty(queue_t *q) {
    assert(q != NULL);

    if (q->total == 0) {
        return 1;
    }

    return 0;
}

int is_full(queue_t *q) {
    assert(q != NULL);

    if (q->total == queue_size) {
        return 1;
    }

    return 0;
}

int insert_elem(queue_t *q, void *x) {
    if (is_full(q) == 1) {
        return  0;
    }
    q->itens[q->end] = malloc(q->elem_size);
    assert(q->itens[q->end] != NULL);

    memcpy(q->itens[q->end], x, q->elem_size);
    q->end = (q->end + 1) % queue_size;
    q->total++;

    return 1;
}

int remove_elem(queue_t *q, void *x) {
    if (is_empty(q) == 1) {
        return 0;
    }

    memcpy(x, q->itens[q->beginning], q->elem_size);
    free(q->itens[q->beginning]);

    q->beginning = (q->beginning + 1) % queue_size;
    q->total--;

    return 1;
}

void destroy(queue_t *q) {
    int i = 0;
    while (i < queue_size) {
        free(q->itens[i]);
        i++;
    }

    assert(q->itens != NULL);
    free(q->itens);

    assert(q != NULL);
    free(q);
}
