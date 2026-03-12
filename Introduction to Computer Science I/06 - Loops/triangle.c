#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i ,j;
    char c;
    scanf("%d %c", &n, &c);
    if (n > 0 && n <= 25) {
        for (i = 0; i < n; i++) {
            for (j = 1; j < n - i; j++) {
                printf(" ");
            }
                for (j = 0; j < i * 2 + 1; j++) {
                    printf("%c", c);
                }
                printf("\n");
        }
    }
    else {
        printf("Altura invalida\n");
        exit(0);
    }
    return 0;
}
