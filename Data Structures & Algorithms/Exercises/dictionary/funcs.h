#ifndef DICIONARIO_PROJ1_ALG_FUNCS_H
#define DICIONARIO_PROJ1_ALG_FUNCS_H

#include "skip_lists.h"

char *read_line();

int change_definition(skip_lists_t *sl, char entry[50], char definition[140]);

int print(skip_lists_t *sl, char character);

#endif //DICIONARIO_PROJ1_ALG_FUNCS_H
