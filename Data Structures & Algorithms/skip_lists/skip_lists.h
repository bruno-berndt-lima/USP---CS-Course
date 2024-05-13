typedef struct node node_t;

typedef struct skip_lists skip_lists_t;

skip_lists_t *create(int max_level, int n);

void destroy(skip_lists_t *sl);

int insert_elem(skip_lists_t *sl, int key);

int search_elem(skip_lists_t *sl, int key);

int remove_elem(skip_lists_t *sl, int key);

