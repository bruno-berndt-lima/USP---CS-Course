#ifndef TRABALHO_2_SEARCH_H
#define TRABALHO_2_SEARCH_H

#include"utils.h"

typedef struct param {
    int qtdParam;
    char field[20];
    char *key;
} Param;


int regComp(Data record, Param *p);

void searchRegisters(int funcType, int arqType, Param *p, FILE *f, int** RRNs, long int** byteOffsets);

void printReg(Data record);

void readReg1(FILE *f, Data *record);

void readReg2(FILE *f, Data *record);

void freeMemReg(Data *record);

void readInputForFunc8(Param **p, Param **new, int* qtdParamP, int* qtdParamNew);

void editFields(FILE *f, Data* record, Header header, Param *new, char* arqType, int RRN, long int byteOffset);



#endif