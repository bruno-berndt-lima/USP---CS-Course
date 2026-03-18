#include <stdio.h>
#include <stdlib.h>

char *read_line() {
    char *line = NULL;
    char character;
    int size = 0;
    do {
        character = getchar();
        size++;
        line = realloc(line, size * sizeof(char));
        line[size - 1] = character; // *(line + (size - 1)) = character ... significa a mesma coisa
    } while(character != EOF && character != '\n');

    line = realloc(line, (size + 1) * sizeof(char)); // adicionar 1 espaco a mais para \0
    line[size] = '\0';

    return line;
}

int main() {
    int num_lines = 0;
    scanf(" %d ", &num_lines);

    char *lines[num_lines];
    for(int i = 0; i < num_lines; i++)
        lines[i] = read_line();

    int valid_lines;
    scanf("%d", &valid_lines);

    int index_valid_lines;
    for(int i = 0; i < valid_lines; i++) {
        scanf("%d", &index_valid_lines);
        printf("%s", lines[index_valid_lines]);
    }

    for(int i = 0; i < num_lines; i++)
        free(lines[i]);

    return 0;
}
