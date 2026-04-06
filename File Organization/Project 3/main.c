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
    char* outputFile = NULL;

    int n;

    switch (func) {
        case 9:
            outputFile = readWord();
            functionality9(arqType, inputFile, outputFile);
            break;
        case 10:
            outputFile = readWord();
            readWord();
            scanf(" %d ", &n);
            functionality10(arqType, inputFile, outputFile, n);
            break;
        case 11:
            outputFile = readWord();
            scanf(" %d ", &n);
            functionality11(arqType, inputFile, outputFile, n);
            break;
        case 13:
            functionalityPrintIndex(arqType, inputFile);
            break;
        default:
            printf("Falha no processamento do arquivo.\n");
            break;
    }

    free(arqType);
    free(inputFile);

    return 0;
}



