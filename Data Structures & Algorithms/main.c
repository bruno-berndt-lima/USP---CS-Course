#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matriz.h"

int main () {
    tree_t *t = create();

    insert_left(t, 1, -1);
    insert_left(t, 2, 1);
    insert_right(t, 3, 1);
    insert_left(t, 4, 3);
    insert_right(t, 5, 3);
    insert_left(t, 6, 4);

    print_tree(t->root);
    printf("\n");

    pre_order(t->root);
    printf("\n");

    in_order(t->root);
    printf("\n");

    post_order(t->root);
    printf("\n");


    return 0;
}