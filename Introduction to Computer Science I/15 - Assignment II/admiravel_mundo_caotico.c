#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rows, columns;

int verifying_neighbors(char **board, int row, int column) {
    //utilizando modulo para verificar os casos em que os vizinhos estao em extremos na matriz
    row = (row + rows) % rows;
    column = (column + columns) % columns;
    if (board[row][column] != 'x') {
        return 0;
    }
    else {
        return 1;

    }
}

int moore_neighborhood_count (char **board, int row, int column) {
    int count_neighbor = 0;
    count_neighbor += verifying_neighbors(board, row - 1, column - 1);
    count_neighbor += verifying_neighbors(board, row - 1, column);
    count_neighbor += verifying_neighbors(board, row - 1, column + 1);
    count_neighbor += verifying_neighbors(board, row, column - 1);
    count_neighbor += verifying_neighbors(board, row, column + 1);
    count_neighbor += verifying_neighbors(board, row + 1, column - 1);
    count_neighbor += verifying_neighbors(board, row + 1, column);
    count_neighbor += verifying_neighbors(board, row + 1, column + 1);

    return count_neighbor;
}

int neumann_neighborhood_count (char **board, int row, int column) {
    int count_neighbor = 0;
    count_neighbor += verifying_neighbors(board, row - 2, column);
    count_neighbor += verifying_neighbors(board, row - 1, column);
    count_neighbor += verifying_neighbors(board, row, column - 2);
    count_neighbor += verifying_neighbors(board, row, column - 1);
    count_neighbor += verifying_neighbors(board, row, column + 1);
    count_neighbor += verifying_neighbors(board, row, column + 2);
    count_neighbor += verifying_neighbors(board, row + 1, column);
    count_neighbor += verifying_neighbors(board, row + 2, column);

    return count_neighbor;
}

/* msleep(): Sleep for the requested number of milliseconds. */
void msleep(long msec){
    struct timespec ts;

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    nanosleep(&ts, &ts);
}

int main() {
    int generations;
    char **board = NULL, **temp_board = NULL, neighborhood_type;

    scanf("%d %d", &rows, &columns);
    scanf("%d", &generations);
    scanf(" %c", &neighborhood_type);

    if (rows <= 0 || columns <= 0 || generations <= 0 || (neighborhood_type != 'M' && neighborhood_type != 'N')) {
        printf("Dados de entrada apresentam erro.\n");
    }
    else {
        board = (char **) malloc(sizeof(char *) * rows);
        temp_board = (char **) malloc(sizeof(char *) * rows);

        for (int i = 0; i < rows; i++) {
            board[i] = (char *) malloc(sizeof(char) * columns);
            temp_board[i] = (char *) malloc(sizeof(char) * columns);
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                scanf(" %c", &board[i][j]);
            }
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                temp_board[i][j] = board[i][j];
            }
        }

        int count_neighbors = 0;
        for (int k = 0; k < generations; k++) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    if (neighborhood_type == 'M') {
                        count_neighbors = moore_neighborhood_count(board, i, j);
                    }
                    else if (neighborhood_type == 'N') {
                        count_neighbors = neumann_neighborhood_count(board, i, j);
                    }
                    if (temp_board[i][j] == 'x') {
                        if (count_neighbors < 2 || count_neighbors > 3) {
                            temp_board[i][j] = '.';
                        }
                        else {
                            temp_board[i][j] = 'x';
                        }
                    }
                    else if (temp_board[i][j] == '.') {
                        if (count_neighbors == 3) {
                            temp_board[i][j] = 'x';
                        }
                        else {
                            temp_board[i][j] = '.';
                        }
                    }
                }
            }
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    printf("%c", temp_board[i][j]);
                    msleep(1);
                    board[i][j] = temp_board[i][j];
                }
                printf("\n");

            }
        }

       /* for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                board[i][j] = temp_board[i][j];
                printf("%c", board[i][j]);
            }
            printf("\n");
        }
*/
        for (int i = 0; i < rows; i++) {
            free(board[i]);
        }
        free(board);

        for (int i = 0; i < rows; i++) {
            free(temp_board[i]);
        }
        free(temp_board);
    }

    return 0;
}
