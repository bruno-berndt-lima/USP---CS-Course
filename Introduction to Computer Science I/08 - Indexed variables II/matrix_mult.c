#include <stdio.h>
#include <stdlib.h>

int main(){
    int la, lb, ca ,cb;
    scanf("%d %d %d %d", &la, &ca, &lb, &cb);
    if(ca != lb) { // verificando se o numero de colunas de a = linhas de b para que seja possivel multiplicar
        printf("Valores invalidos para a multiplicacao.\n");
        exit(0);
    }
    if((la < 0) || (ca < 0) || (lb < 0) || (cb < 0)) { //verificando se os valores das linhas e colunas sao positivos
        printf("Valores invalidos para a multiplicacao.\n");
        exit(0);
    }
    int semente;
    scanf("%d", &semente);
    srand(semente);
    int matriz_a[la][ca], matriz_b[lb][cb], matriz_c[la][cb];
    for (int i = 0; i < la; i++) { //gerando matriz_a
        for (int j = 0; j < ca; j++) {
            matriz_a[i][j] = rand() % 50 - 25;
        }
    }
    for (int i = 0; i < lb; i++) { //gerando matriz_b
        for (int j = 0; j < cb; j++) {
            matriz_b[i][j] = rand() % 50 - 25;
        }
    }
    for (int i = 0; i < la; i++) { //loop para multiplicar AXB
        for (int j = 0; j < cb; j++) {
            matriz_c[i][j] = 0;
            for (int k = 0; k < lb; k++) {
                matriz_c[i][j] += matriz_a[i][k] * matriz_b[k][j];
            }
        }
    }
    for (int i = 0; i < la; i++) { //loop para imprimir matriz_c
        printf("Linha %d:", i);
        for (int j = 0; j < cb; j++) {
            printf(" %d", matriz_c[i][j]);
        }
        printf("\n");
    }
    return 0;
}