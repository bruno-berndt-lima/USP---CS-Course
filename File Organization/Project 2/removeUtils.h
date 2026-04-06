#ifndef TRABALHO_2_REMOVE_H
#define TRABALHO_2_REMOVE_H

#include"dataStructures.h"
#include"search.h"

void searchAndRemove(int arqType, char *dataFileName, char *indexFileName, Param **p, int qtdReg);

long int getRRN(long int byteOffset);

long int getByteOffset(int rrn);

#endif