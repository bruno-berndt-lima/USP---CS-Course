#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct musicas {
    char *nome_musica;
    char *artista;
    int tempo_de_duracao;
} Musicas;

typedef struct playlist {
    char *nome_playlist;
    int qtd_musicas;
    Musicas musicas[15];
} Playlist;

char *read_line (int *size_variable) {
    char *str = NULL;
    int counter = 0;
    char c;

    do {
        c = getchar();
        str = realloc(str, sizeof (char) * (counter + 1));
        str[counter++] = c;
    } while (c != '\n' && c != EOF);

    str[--counter] = '\0';
    *size_variable = counter;
    return str;
}

void imprime_playlist (Playlist *playlist, int cont_muda_musica) {
    char *musica_tocando = playlist->musicas[cont_muda_musica].nome_musica;
    for (int k = 0; k < playlist->qtd_musicas; k++) {
        if (playlist->musicas[k].nome_musica == musica_tocando) {
            printf("=== NOW PLAYING ===\n");
            printf("(%d). '%s'\n", k + 1, playlist->musicas[k].nome_musica);
            printf("Artista: %s\n", playlist->musicas[k].artista);
            printf("Duracao: %d segundos\n\n", playlist->musicas[k].tempo_de_duracao);
        }
        else {
            printf("(%d). '%s'\n", k + 1, playlist->musicas[k].nome_musica);
            printf("Artista: %s\n", playlist->musicas[k].artista);
            printf("Duracao: %d segundos\n\n", playlist->musicas[k].tempo_de_duracao);
        }
    }
}

int main() {
    int comando = 0, i = 0, size, cont_muda_musica = 0;
    bool finalizar = false;

    Playlist *playlist = (Playlist*) malloc(sizeof (Playlist));

    playlist->nome_playlist = read_line(&size);

    playlist->qtd_musicas = 0;

    while (!finalizar) {
        scanf("%d\n", &comando);

        switch (comando) {
            case 1:
                if (playlist->qtd_musicas < 15) {
                    playlist->musicas[i].nome_musica = read_line(&size);
                    playlist->musicas[i].artista = read_line(&size);
                    scanf("%d", &(playlist->musicas[i].tempo_de_duracao));

                    printf("Musica %s de %s adicionada com sucesso.\n", playlist->musicas[i].nome_musica, playlist->musicas[i].artista);
                    playlist->qtd_musicas++;
                    i++;
                }
                else {
                    printf("Playlist cheia!\n");
                }
                break;
            case 2:
                printf("---- Playlist: %s ----\n", playlist->nome_playlist);
                printf("Total de musicas: %d\n\n", playlist->qtd_musicas);
                imprime_playlist(playlist, cont_muda_musica);
                break;
            case 3:
                cont_muda_musica++;
                break;
            case 4:
                cont_muda_musica--;
                break;
            case 5:
            default:
                finalizar = true;
                break;
        }
    }

    for (i = 0; i < playlist->qtd_musicas; i++) {
        free(playlist->musicas[i].nome_musica);
        free(playlist->musicas[i].artista);
    }
    free(playlist->nome_playlist);
    free(playlist);

    return 0;
}
