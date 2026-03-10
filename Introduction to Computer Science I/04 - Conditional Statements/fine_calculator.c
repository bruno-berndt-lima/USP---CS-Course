#include <stdio.h>

int main () {
    int limite = 80;
    float velocidade;
  
    scanf("%f", &velocidade);
  
    float multa = 2 * (velocidade - limite);
    if (velocidade > 80) {
        printf("Limite de velocidade excedido! Multado no valor de R$%.2f!\n", multa);
    }
    else {
        printf("Velocidade dentro do limite permitido.\n");
    }
    return 0;
}
