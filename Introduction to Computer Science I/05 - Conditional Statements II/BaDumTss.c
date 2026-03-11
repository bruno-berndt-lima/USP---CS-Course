#include <stdio.h>

int main() {
    int a;
    int divs = 0;
    scanf("%d", &a);
    if (a % 11 == 0 ) {
        divs++;
    }
    if (a % 13 == 0 ) {
        divs++;
    }
    if (a % 19 == 0 ) {
        divs++;
    }
    if (divs == 0) {
        printf("%d\n", a);
    }
    else if (divs == 1) {
        printf("Ba");
        if (a % 11 == 0) {
            printf("Ba\n");
        }
        if (a % 13 == 0) {
            printf("Dum\n");
        }
        if (a % 19 == 0) {
            printf("Tss\n");
        }
    }
    else if (divs == 2) {
        if (a % 11 == 0) {
            printf("BaDum");
            if (a % 13 == 0){
                printf("Dum\n");
            }
            else {
                printf("Tss\n");
            }
        }
        else {
            printf("DumDumTss\n");
        }
    }
    else {
        printf("BaDumTssTss\n");

    }
}
