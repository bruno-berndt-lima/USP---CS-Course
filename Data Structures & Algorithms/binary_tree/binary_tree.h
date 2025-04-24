typedef int elem;

typedef struct node node_t;

typedef struct tree {
    node_t *root;
} tree_t;

tree_t *create();

int is_empty(tree_t *t);

void destroy(node_t *root);

void print_tree(node_t *root);

int height(node_t *root);

node_t *search(node_t *root, elem x);

node_t *search_parent(node_t *root, elem x);

int insert_left(tree_t *t, elem x, elem parent);

int insert_right(tree_t *t, elem x, elem parent);

int remove_elem(tree_t *t, elem x);

void pre_order(node_t *root);

void in_order(node_t *root);

void post_order(node_t *root);
