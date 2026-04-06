#ifndef TRABALHO_2_SEARCH_H
#define TRABALHO_2_SEARCH_H

#include"utils.h"

typedef struct param {
    int qtdParam;
    char field[20];
    char *key;
} Param;


void printReg(Data record);

void readReg1(FILE *f, Data *record);

void readReg2(FILE *f, Data *record);

void freeMemReg(Data *record);




#endif