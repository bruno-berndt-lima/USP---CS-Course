#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "queue.h"

struct queue {
    int beginning, end, total;
    elem itens[queue_size];
};

queue_t *create() {
    queue_t *q;
    q = (queue_t *) malloc(sizeof(queue_t));
    assert(q != NULL);

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

int insert_elem(queue_t *q, elem x) {
    if (is_full(q) == 1) {
        return  0;
    }
  
    q->itens[q->end] = x;
    q->end = (q->end + 1) % queue_size;
    q->total++;

    return 1;
}

int remove_elem(queue_t *q, elem *x) {
    if (is_empty(q) == 1) {
        return 0;
    }

    *x = q->itens[q->beggining];
    q->beginning = (q->beginning + 1) % queue_size;
    q->total--;

    return 1;
}

void destroy(queue_t *q) {
    if (q != NULL) {
        free(q);
    }
}
