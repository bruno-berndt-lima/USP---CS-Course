#define stack_size 400

typedef int elem;
typedef struct stack stack_t;

stack_t *create();

void destroy(stack_t *p);

int is_full(stack_t *p);

int is_empty(stack_t *p);

int push(stack_t *p, elem x);

int pop(stack_t *p, elem *x);

int top(stack_t *p, elem *x);


