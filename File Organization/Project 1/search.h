#include "utils.h"

typedef struct param {
    char field[20];
    char *key;
} Param;

void searchRegisters(int funcType, int arqType, Param *p, FILE *f);

void printReg(Data record);

void readReg1(FILE *f, Data *record);

void freeMemReg(Data *record);