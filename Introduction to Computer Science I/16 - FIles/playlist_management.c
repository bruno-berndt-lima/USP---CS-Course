#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void binaryToNum(char *binFilename) {
    FILE *fp = fopen(binFilename, "rb");

    double binValue = 0;
    double accumulator = 0.01;
    char ch;
    while (fread(&ch, sizeof(char), 1, fp)) {
        binValue += (double) ch * accumulator;
        accumulator += 0.01;
    }

    fclose(fp);
    printf("%lf\n", binValue);
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
    FILE *arquivo;
    int comando = 0, i = 0, size, cont_muda_musica = 0;
    bool finalizar = false;
    char *nome_do_arquivo;

    Playlist *playlist = (Playlist *) malloc(sizeof(Playlist));

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

                    printf("Musica %s de %s adicionada com sucesso.\n", playlist->musicas[i].nome_musica,
                           playlist->musicas[i].artista);
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
                nome_do_arquivo = read_line(&size);
                arquivo = fopen(nome_do_arquivo, "wb");

                int tamanho_nome_playlist = strlen(playlist->nome_playlist);
                fwrite(&tamanho_nome_playlist, sizeof(int), 1, arquivo);
                fwrite(playlist->nome_playlist, sizeof(char), strlen(playlist->nome_playlist), arquivo);

                int num_de_musicas = playlist->qtd_musicas;
                fwrite(&num_de_musicas, sizeof(int), 1, arquivo);
                playlist->qtd_musicas = num_de_musicas;

                for (int j = 0; j < playlist->qtd_musicas; j++) {
                    int tamanho_nome_musica = strlen(playlist->musicas[j].nome_musica);
                    fwrite(&tamanho_nome_musica, sizeof(int), 1, arquivo);
                    fwrite(playlist->musicas[j].nome_musica, sizeof(char), strlen(playlist->musicas[j].nome_musica),arquivo);

                    int tamanho_nome_artista = strlen(playlist->musicas[j].artista);
                    fwrite(&tamanho_nome_artista, sizeof(int), 1, arquivo);
                    fwrite(playlist->musicas[j].artista, sizeof(char), strlen(playlist->musicas[j].artista), arquivo);

                    int tamanho_duracao_musica = playlist->musicas[j].tempo_de_duracao;
                    fwrite(&tamanho_duracao_musica, sizeof(int), 1, arquivo);
                }

                printf("Playlist %s salva com sucesso.\n", nome_do_arquivo);
                fclose(arquivo);
                binaryToNum(nome_do_arquivo);
                break;
            case 6:
                /*  como deseja-se carregar uma playlist nova de um arquivo, damos free na struct
                 * playlist inteira e eh inicializada como NULL.
                 */
                for (i = 0; i < playlist->qtd_musicas; i++) {
                    free(playlist->musicas[i].nome_musica);
                    free(playlist->musicas[i].artista);
                    playlist->musicas[i].nome_musica = NULL;
                    playlist->musicas[i].artista = NULL;
                }
                free(playlist->nome_playlist);
                playlist->nome_playlist = NULL;
                free(playlist);
                playlist = NULL;

                cont_muda_musica = 0;

                nome_do_arquivo = read_line(&size);
                arquivo = fopen(nome_do_arquivo, "rb");

                if (arquivo == NULL) {
                    printf("Arquivo %s nao existe.\n", nome_do_arquivo);
                    exit(0);
                }
                else {
                    playlist = (Playlist *) malloc(sizeof(Playlist));
                    fread(&tamanho_nome_playlist, sizeof(int), 1, arquivo);
                    playlist->nome_playlist = realloc(playlist->nome_playlist, sizeof(char) * tamanho_nome_playlist);
                    fread(playlist->nome_playlist, sizeof(char), tamanho_nome_playlist, arquivo);
                    // Realloc para add o '\0' que nao eh lido do arquivo.
                    playlist->nome_playlist = realloc(playlist->nome_playlist,sizeof(char) * (tamanho_nome_playlist + 1));
                    playlist->nome_playlist[tamanho_nome_playlist] = '\0';

                    fread(&num_de_musicas, sizeof(int), 1, arquivo);
                    playlist->qtd_musicas = num_de_musicas;
                    i = num_de_musicas;

                    for (int j = 0; j < num_de_musicas; j++) {
                        int tamanho_nome_musica;
                        fread(&tamanho_nome_musica, sizeof(int), 1, arquivo);
                        playlist->musicas[j].nome_musica = realloc(playlist->musicas[j].nome_musica, sizeof(char) * tamanho_nome_musica);
                        fread(playlist->musicas[j].nome_musica, sizeof(char), tamanho_nome_musica, arquivo);
                        playlist->musicas[j].nome_musica = realloc(playlist->musicas[j].nome_musica, sizeof(char) * (tamanho_nome_musica + 1));
                        playlist->musicas[j].nome_musica[tamanho_nome_musica] = '\0';

                        int tamanho_nome_artista;
                        fread(&tamanho_nome_artista, sizeof(int), 1, arquivo);
                        playlist->musicas[j].artista = realloc(playlist->musicas[j].artista, sizeof(char) * tamanho_nome_artista);
                        fread(playlist->musicas[j].artista, sizeof(char), tamanho_nome_artista, arquivo);
                        playlist->musicas[j].artista = realloc(playlist->musicas[j].artista, sizeof(char) * (tamanho_nome_artista + 1));
                        playlist->musicas[j].artista[tamanho_nome_artista] = '\0';

                        fread(&playlist->musicas[j].tempo_de_duracao, sizeof(int), 1, arquivo);
                    }

                    printf("Playlist %s carregada com sucesso.\n", nome_do_arquivo);
                    fclose(arquivo);
                    binaryToNum(nome_do_arquivo);
                }
                break;
            case 7:
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
    free(nome_do_arquivo);
}

