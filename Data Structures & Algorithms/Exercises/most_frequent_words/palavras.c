#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_alphabetic(char character) {
    if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z')) {
        return 1;
    } else {
        return 0;
    }
}




