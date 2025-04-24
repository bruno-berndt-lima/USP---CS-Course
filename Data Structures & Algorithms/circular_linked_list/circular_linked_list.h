typedef struct list list_t;

list_t *create();

int insert_at_beginning(list_t *list, int value);

int insert_at_end(list_t *list, int value);

int insert_ordered(list_t *list, int value);

int remove_elem(list_t *list, int value);

int search(list_t *list, int value);

void print_list(list_t *list);
