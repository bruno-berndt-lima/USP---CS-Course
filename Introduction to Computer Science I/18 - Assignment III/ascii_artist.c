#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define valid_matrix_boundaries (x_coordinate >= 0 && x_coordinate < num_lines \
                                && y_coordinate >= 0 && y_coordinate < num_columns)

char *read_line (FILE *p_file, int *columns) {
    char *line = NULL;
    char c = ' ';
    int size = 0;

    while(c != '\n' && !feof(p_file)) {
        fscanf(p_file, "%c", &c);
        line = (char *) realloc(line, (++size) * sizeof(char));
        line[size - 1] = c;
    }
    line[size - 1] = '\0';
    *columns = size - 1;

    return line;
}

void recursive_fill_art (char character, int x_coordinate,int y_coordinate, char **art,
                         int num_lines, int num_columns , char previous_character) {

    if (valid_matrix_boundaries && art[x_coordinate][y_coordinate] == previous_character) {
        art[x_coordinate][y_coordinate] = character;
        // chamando a funcao recursiva para as 4 direcoes (direita, esquerda, cima, baixo)
        recursive_fill_art(character, x_coordinate - 1,y_coordinate,
                           art, num_lines, num_columns, previous_character);
        recursive_fill_art(character, x_coordinate + 1, y_coordinate,
                           art, num_lines, num_columns, previous_character);
        recursive_fill_art(character, x_coordinate, y_coordinate - 1,
                           art, num_lines, num_columns, previous_character);
        recursive_fill_art(character, x_coordinate, y_coordinate + 1,
                           art, num_lines, num_columns, previous_character);
    }
}

void enquadra_arte (
        char *nome_do_arquivo_da_arte,
        int  altura_do_quadro,
        int  largura_do_quadro
) {
    FILE *f_arte_ptr = fopen(nome_do_arquivo_da_arte, "r");
    if (f_arte_ptr == NULL) {
        printf(
                "Erro na abertura do arquivo, "
                "Você esqueceu de fechar o arquivo antes? "
                "Ou deu free na string com o nome sem querer?\n"
        );

        exit(EXIT_FAILURE);
    }

    int qtd_espc_comeco;
    const char *apoio;
    if (largura_do_quadro % 2 == 0) {
        qtd_espc_comeco = largura_do_quadro / 2;
        apoio           = "/\\";
    } else {
        qtd_espc_comeco = largura_do_quadro / 2 + 1;
        apoio           = "Ʌ";
    }

    for (int i = 0; i < qtd_espc_comeco; i++) printf(" ");
    printf("%s\n", apoio);

    printf("╭");
    for (int i = 0; i < largura_do_quadro; i++) printf("—");
    printf("╮\n");

    for (int i = 0; i < altura_do_quadro; i++) {
        printf("|");
        for (int j = 0; j < largura_do_quadro; j++) {
            char pixel_atual = fgetc(f_arte_ptr);
            printf("%c", pixel_atual);
        }
        printf("|");

        char quebra = fgetc(f_arte_ptr);
        if (quebra != EOF) printf("%c", quebra);
    };
    fclose(f_arte_ptr);

    printf("\n╰");
    for (int i = 0; i < largura_do_quadro; i++) printf("—");
    printf("╯\n");
}

int main() {
    FILE *ptr_file;

    int num_of_columns = 0, num_of_lines = 0;
    char *art_name = NULL;
    art_name = read_line(stdin, &num_of_columns);

    char **art = NULL;
    ptr_file = fopen(art_name, "r");
    while (!feof(ptr_file)) {
        num_of_lines++;
        art = (char **) realloc(art, sizeof (char *) * num_of_lines);
        art[num_of_lines - 1] = read_line(ptr_file, &num_of_columns);
    }
    fclose(ptr_file);

    printf("Arte inicial:\n");

    for (int i = 0; i < num_of_lines; i++) {
        for (int j = 0; j < num_of_columns; j++) {
            printf("%c", art[i][j]);
        }
        printf("\n");
    }

    int num_of_fills;
    scanf("%d\n", &num_of_fills);

    char character;
    int x_coordinate, y_coordinate;
    for (int i = 0; i < num_of_fills; i++) {
        scanf(" %c", &character);
        scanf("%d", &x_coordinate);
        scanf("%d", &y_coordinate);
        recursive_fill_art(character, x_coordinate, y_coordinate, art,num_of_lines,
                           num_of_columns, art[x_coordinate][y_coordinate]);

        printf("\nArte apos a etapa %d:\n", i);

        for (int j = 0; j < num_of_lines; j++) {
            for (int k = 0; k < num_of_columns; k++) {
                printf("%c", art[j][k]);
            }
            printf("\n");
        }
    }

    ptr_file = fopen(art_name, "w");

    for (int j = 0; j < num_of_lines; j++) {
        for (int k = 0; k < num_of_columns; k++) {
            fprintf(ptr_file,"%c", art[j][k]);
        }
        if (j < num_of_lines - 1) {
            fprintf(ptr_file,"\n");
        }
    }
    fclose(ptr_file);
    printf("\nArte enquadrada:\n");
    enquadra_arte(art_name, num_of_lines, num_of_columns);

    for (int i = 0; i < num_of_lines; i++) {
        free(art[i]);
    }
    free(art);
    free(art_name);

    return 0;
}
