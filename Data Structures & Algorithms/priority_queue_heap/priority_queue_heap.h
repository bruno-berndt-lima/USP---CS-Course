#define MAX_HEAP_SIZE 100

typedef int elem;
typedef struct node node_t;
typedef struct queue queue_t;

queue_t *create();

int insert(queue_t *q, elem key, int priority);

int remove_elem(queue_t *q, elem *key);

int is_empty(queue_t *q);

int is_full(queue_t *q);

void destroy(queue_t *q);
