#ifndef TRABALHO_2_INDEXU_H
#define TRABALHO_2_INDEXU_H

#include"dataStructures.h"

typedef struct indexEntry {
    int key;
    long int location;
} IDE;

int binSearch(IDE *entries, int key, int max);
IDE *readIndexFile1(FILE **f, int *qtdEntries);
IDE *readIndexFile2(FILE **f, int *qtdEntries);
void insertEntry(int key, long int pos, IDE **entries, int *qtdEnt);
void writeIndexFile(FILE **f, IDE *entries, int entryCount, int arqType);
long int getLocation(IDE *entries, int key, int max);

long int removeFromEntries(IDE *entries, int *qtyEnt, int key, long int freePos);

#endif