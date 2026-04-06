/*
* SCC0215 - Organização de Arquivos
* TRABALHO 1
* profa Cristina Dutra de Aguiar
* Alunos:
*   Bruno Berndt Lima - 12542550
*   Gabriela Bacarin Marcondes - 10873351
*/

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "functionalities.h"

int main() {

    int func;
    scanf("%d ", &func);
    char* arqType = readWord();
    char* inputFile = readWord();
    char* outputFile;

    Header header_rec; // registro de cabecalho (Header Record)
    allocHeaderRecord(&header_rec);
    fillHeaderRecord(&header_rec);

    int RRN;
    Data data_rec; // registro de dados (Data Record)
    switch (func) {
        case 1:
            outputFile = readWord();
            functionality1(arqType, inputFile, outputFile, data_rec, header_rec);
            free(outputFile);
            break;
        case 2:
            functionality2(arqType, inputFile);
            break;
        case 3:
            functionality3(arqType, inputFile);
            break;
        case 4:
            scanf("%d", &RRN);
            functionality4(arqType, inputFile, data_rec, RRN);
            break;
        default:
            printf("Falha no processamento do arquivo.\n");
            break;
    }

    free(arqType);
    free(inputFile);
    freeHeaderRecord(&header_rec);

    return 0;
}



