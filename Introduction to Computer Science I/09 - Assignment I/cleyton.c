#include <stdio.h>

enum ops{HLT, ADD, MUL, CLT, CEQ, JMP, JEQ, CPY, PUT, PTN};
int main() {
    int fita[512] = {0}, indice;
    for (indice = 0; indice < 512; indice++) {
        scanf("%d", &fita[indice]);
    }
    printf("Saida do programa: \n");
    indice = 0;

    do {
        switch (fita[indice]) {
            case ADD:
                fita[fita[indice + 3]] = fita[fita[indice + 1]] + fita[fita[indice + 2]];
                indice += 4;
                break;
            case MUL:
                fita[fita[indice + 3]] = fita[fita[indice + 1]] * fita[fita[indice + 2]];
                indice += 4;
                break;
            case CLT:
                if (fita[fita[indice + 1]] < fita[fita[indice + 2]]) {
                    fita[fita[indice + 3]] = 1;
                    indice += 4;
                } else {
                    fita[fita[indice + 3]] = 0;
                    indice += 4;
                }
                break;
            case CEQ:
                if (fita[fita[indice + 1]] == fita[fita[indice + 2]]) {
                    fita[fita[indice + 3]] = 1;
                    indice += 4;
                } else {
                    fita[fita[indice + 3]] = 0;
                    indice += 4;
                }
                break;
            case JMP:
                indice = fita[fita[indice + 1]];
                break;
            case JEQ:
                if (fita[fita[indice + 1]] != 0) {
                    indice = fita[fita[indice + 2]];
                } else {
                    indice = indice + 3;
                }
                break;
            case CPY:
                fita[fita[indice + 2]] = fita[fita[indice + 1]];
                indice += 3;
                break;
            case PUT:
                printf("%c", fita[fita[indice + 1]]);
                indice += 2;
                break;
            case PTN:
                printf("%d", fita[fita[indice + 1]]);
                indice += 2;
                break;
        }
    } while (fita[indice] != HLT);

    printf("\n");
    printf("Estado final da fita:");
    for (indice = 0; indice < 512; indice++) {
        printf("\n%d", fita[indice]);
    }

    return 0;
}
