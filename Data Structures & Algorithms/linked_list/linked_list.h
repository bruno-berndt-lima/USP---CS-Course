typedef int elem;
typedef struct list list_t;
typedef struct node node_t;

list_t *create();

void destroy(list_t *l);

void insert(list_t *l, elem x);

int size(list_t *l);

void print_elem_from_list(list_t *l, int index);

int  list_contains_elem(list_t *l, elem x);

int remove_elem(list_t *list, elem x);


