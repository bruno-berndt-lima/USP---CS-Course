typedef int elem;

typedef struct node node_t;

typedef union {
    elem atom;
    node_t *sublist;
} info_t;

struct node {
    int type;
    info_t info;
    node_t *next;
};

node_t *Atom(elem x);

node_t *Sublist(node_t *sublist);

node_t *concatenate(node_t *p, node_t *q);

info_t head(node_t *p, int *type);

node_t *tail(node_t *p);

void print_list(node_t *p);

int list_depth(node_t *p);

int list_contains_elem(node_t *p, elem x);

int equals(node_t *p, node_t *q);

void free_list(node_t *p);
