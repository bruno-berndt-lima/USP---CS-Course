#define queue_size 100

typedef int elem;
typedef struct queue queue_t;

queue_t *create();

int is_empty(queue_t *q);

int is_full(queue_t *q);

int insert_elem(queue_t *q, elem *x);

int remove_elem(queue_t *q, elem *x);


