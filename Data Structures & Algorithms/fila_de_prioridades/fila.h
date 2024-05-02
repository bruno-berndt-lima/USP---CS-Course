#ifndef FILA_DE_PRIORIDADES_FILA_H
#define FILA_DE_PRIORIDADES_FILA_H

#define queue_size 100

typedef struct queue queue_t;

queue_t *create(int size);

int is_empty(queue_t *q);

int is_full(queue_t *q);

int insert_elem(queue_t *q, void *x);

int remove_elem(queue_t *q, void *x);


#endif //FILA_DE_PRIORIDADES_FILA_H
