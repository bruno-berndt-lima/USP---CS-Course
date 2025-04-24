// Bruno Berndt Lima - 12542550

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcs.h"
#include "skip_lists.h"

int main() {
    skip_lists_t *sl = create();

    // palavra e definicao a ser inserido na skiplist
    char *entry, *definition;
    entry = (char *) malloc(sizeof(char) * 50);

    char c, command[15];
    while ((c = getchar()) != EOF) {
        ungetc(c, stdin);
        scanf("%s ", command);

        if (strcmp(command, "insercao") == 0) {
            scanf("%s ", entry);
            definition = read_line();
            insert_elem(sl, entry, definition);
            free(definition);
        }
        else if (strcmp(command, "busca") == 0) {
            scanf("%s ", entry);
            search(sl, entry);
        }
        else if (strcmp(command, "alteracao") == 0) {
            scanf("%s ", entry);
            definition = read_line();
            change_definition(sl, entry, definition);
            free(definition);
        }
        else if (strcmp(command, "impressao") == 0) {
            char character;
            scanf("%c ", &character);
            print(sl, character);
        }
        else if (strcmp(command, "remocao") == 0){
            scanf("%s ", entry);
            remove_elem(sl, entry);
        }
    }

    free(entry);
    destroy(sl);

    return 0;
}
