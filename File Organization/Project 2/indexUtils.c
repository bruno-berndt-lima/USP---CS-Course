#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"indexUtils.h"
#include"utils.h"
#include"dataStructures.h"


// função que realiza busca binária iterativa nas entries baseado na key e retorna índice da key buscada
int binSearch(IDE *entries, int key, int max) {
    max = max - 1;
    int min = 0;

    while(min <= max) {
        int meio = (int)((min + max) / 2);
        if(key == entries[meio].key) {
            return meio;
        }
        if(key < (entries[meio].key)) {
            max = meio - 1;
            continue;
        }
        min = meio + 1;
    }

    return -1;
}

// função que realiza busca binária e retorna o campo location do registro buscado pela key (id)
long int getLocation(IDE *entries, int key, int max) {
    max = max - 1;
    int min = 0;

    while(min <= max) {
        int meio = (int)((min + max) / 2);
        if(key == entries[meio].key) {
            return entries[meio].location;
        }
        if(key < (entries[meio].key)) {
            max = meio - 1;
            continue;
        }
        min = meio + 1;
    }

    return -1;
}
// função de busca binária usada na hora de inserir uma entry ordenadamente; retorna o índice
// da posição anterior a qual a nova entry deve ficar em entries
int returnIndex(IDE **entries, int max, int key) {
    max = max - 2;
    int min = 0;

    while(min < max) {
        int meio = (int)((min + max) / 2);
        if(key < ((*entries)[meio].key)) {
            max = meio - 1;
        }
        else {
            min = meio + 1;
        }
    }

    if(((*entries)[min].key - key) < (key - (*entries)[max].key)) {
        return min;
    }
    return max;
}

// função que remove uma entry de entries e retorna a posição do removido, caso ela seja menor (anterior no registro)
// do que a última posição livre registrada
long int removeFromEntries(IDE *entries, int *qtyEnt, int key, long int freePos) {
    long int retorno = freePos;

    int indexRem = binSearch(entries, key, *qtyEnt);
    if(indexRem == -1) {
        printf("Erro na busca binária\nkey: %d\n", key);
        return retorno;
    }

    if(entries[indexRem].location < retorno) {
        retorno = entries[indexRem].location;
    }
    // fazendo a shiftada após remoção
    for(int i = indexRem; i < *qtyEnt - 1; i++) {
        entries[i].key = entries[i + 1].key;
        entries[i].location = entries[i + 1].location;
    }

    *qtyEnt = ((*qtyEnt) - 1);

    return retorno;
}

// lê um arquivo de índices do tipo 1, nos quais a location é int
// retorna a struct entries preenchida
IDE *readIndexFile1(FILE **f, int *qtdEntries) {
    *qtdEntries = *qtdEntries + 1;
    IDE *entries = malloc(sizeof(IDE));

    while(feof(*f) == 0) {
        fread(&(entries[*qtdEntries - 1].key), sizeof(int), 1, *f);
        //printf("%d ", entries[*qtdEntries - 1].key);
        fread(&(entries[*qtdEntries - 1].location), sizeof(int), 1, *f);
        //printf("%ld\n", entries[*qtdEntries - 1].location);
        *qtdEntries = *qtdEntries + 1;
        entries = realloc(entries, (*qtdEntries * sizeof(IDE)));
    }

    return entries;
}

// lê um arquivo de índices do tipo 2, nos quais a location é long int
// retorna a struct entries preenchida
IDE *readIndexFile2(FILE **f, int *qtdEntries) {
    *qtdEntries = *qtdEntries + 1;
    IDE *entries = malloc(sizeof(IDE));

    while(feof(*f) == 0) {
        fread(&(entries[*qtdEntries - 1].key), sizeof(int), 1, *f);
        fread(&(entries[*qtdEntries - 1].location), sizeof(long int), 1, *f);
        *qtdEntries = *qtdEntries + 1;
        entries = realloc(entries, (*qtdEntries * sizeof(IDE)));
    }

    //*qtdEntries = ((*qtdEntries) - 1);
    return entries;
}


// função que insere uma entry ordenadamente na struct entries
void insertEntry(int key, long int pos, IDE **entries, int *qtdEnt) {
    *qtdEnt = *qtdEnt + 1;
    *entries = realloc(*entries, *qtdEnt * sizeof(IDE));

    int insert = 0;

    if(*qtdEnt > 1) {
        if((*entries)[*qtdEnt - 2].key < key) {
            insert = *qtdEnt - 1;
        } else {
            if((*entries)[0].key < key) {
                //printf("busca\n");
                insert = (returnIndex(entries, *qtdEnt, key) + 1);
            }            
            //printf("shiftada\n");
            for(int i = *qtdEnt - 1; i > insert; i--) {
                (*entries)[i].key = (*entries)[i-1].key;
                (*entries)[i].location = (*entries)[i-1].location;

            }
        }
    }

    (*entries)[insert].key = key;
    (*entries)[insert].location = pos;
}

// escreve um novo arquivo de índice, já aberto, com as entries salvas
void writeIndexFile(FILE **f, IDE *entries, int entryCount, int arqType) {
    fseek(*f, 0, SEEK_SET);
    fwrite("0", sizeof(char), 1, *f);

    if(arqType == 1) {
        for(int i = 0; i < entryCount; i++) {
            fwrite(&(entries[i].key), sizeof(int), 1, *f);
            int loc = (int)(entries[i].location);
            fwrite(&loc, sizeof(int), 1, *f);
        }
    } else {
        for(int i = 0; i < entryCount; i++) {
            fwrite(&(entries[i].key), sizeof(int), 1, *f);
            fwrite(&(entries[i].location), sizeof(long int), 1, *f);
        }
    }
}