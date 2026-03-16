#include <stdio.h>

int main() {
    char keyboard[49];
    int i, size, msg;
    for (i = 0; i < 49; i++)
        scanf("%c ", &keyboard[i]);
    scanf("%d", &size);
    for (i = 0; i < size; i++) {
        scanf("%d", &msg);
        if(keyboard[msg] == '_')
            keyboard[msg] = ' ';
        if(keyboard[msg] == 'E')
            keyboard[msg] = '\n';
        printf("%c", keyboard[msg]);
    }
    return 0;
}
