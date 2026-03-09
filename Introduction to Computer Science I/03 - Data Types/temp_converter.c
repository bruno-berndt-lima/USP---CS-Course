#include <stdio.h>

int main() {
    float celsius;
    printf("Digite a temperatura em graus Fahrenheit.\n");
    scanf("%f", &fahrenheit);
  
    float celsius = (5*fahrenheit-160)/9;
    printf("A temperatura em graus Celsius é: %.2f\n ", celsius);
}
