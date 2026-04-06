#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "removeUtils.h"
#include "search.h"
#include "utils.h"

// função que lê uma palavra
char *readWord() {
    char *str = NULL;
    int counter = 0;
    char c;

    do {
        c = getchar();
        str = realloc(str, sizeof (char) * (counter + 1));
        str[counter++] = c;
    } while (c != ' ' && c != '\n' && c != '\r' && c != EOF);
    str[--counter] = '\0';

    return str;
}

void binarioNaTela(char* nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

    /* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
    *  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

    unsigned long i, cs;
    unsigned char *mb;
    size_t fl;
    FILE *fs;
    if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
        fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
        return;
    }
    fseek(fs, 0, SEEK_END);
    fl = ftell(fs);
    fseek(fs, 0, SEEK_SET);
    mb = (unsigned char *) malloc(fl);
    fread(mb, 1, fl, fs);

    cs = 0;
    for(i = 0; i < fl; i++) {
        cs += (unsigned long) mb[i];
    }
    printf("%lf\n", (cs / (double) 100));
    free(mb);
    fclose(fs);
}

// função para ler input entre aspas
// sem considerar a existência de um campo NULO
char *readQuoted() {
    char *str = malloc(0);
    int size = 0;
    char c;

    if(fgetc(stdin) == '"') {
        do {
            c = fgetc(stdin);
            str = realloc(str, (size + 1) * sizeof(char));
            if(c != '"')
                str[size++] = c;
            else
                str[size++] = '\0';
        } while(c != '"');
        do {
            c = fgetc(stdin);
        } while(c != '\n' && c != EOF && c != ' ' && c != '\r');
    }

    return str;
}

// função para ler input entre aspas considerando
// a existência de um campo NULO e retornando NULL caso exista
char *readQuoted2() {
    char *str = malloc(0);
    int size = 0;
    char c;

    if(fgetc(stdin) == '"') {
        do {
            c = fgetc(stdin);
            str = realloc(str, (size + 1) * sizeof(char));
            if(c != '"')
                str[size++] = c;
            else
                str[size++] = '\0';
        } while(c != '"');
    } else { // caso em que le 'N' de NULO
        getchar();      // get 'U'
        getchar();      // get 'L'
        getchar();      // get 'O'
        do {
            c = fgetc(stdin);
        } while(c != '\n' && c != EOF && c != ' ' && c != '\r');
        return NULL;
    }
    do {
        c = fgetc(stdin);
    } while(c != '\n' && c != EOF && c != ' ');

    return str;
}

// função para ler input entre aspas considerando a existência
// de um campo NULO e retornando a string "NULO" caso exista
char *readQuoted3() {
    char *str = malloc(0);
    int size = 0;
    char c;

    if(fgetc(stdin) == '"') {
        do {
            c = fgetc(stdin);
            str = realloc(str, (size + 1) * sizeof(char));
            if(c != '"' && c != '\n' && c != '\r')
                str[size++] = c;
            else
                str[size++] = '\0';
        } while(c != '"');
    } else { // caso em que le 'N' de NULO
        getchar();      // get 'U'
        getchar();      // get 'L'
        getchar();      // get 'O'
        str = malloc(sizeof(char ) * 4);
        memcpy(str, "NULO", sizeof(char) * 4);
    }
    do {
        c = fgetc(stdin);
    } while(c != '\n' && c != EOF && c != ' ' && c != '\r');

    return str;
}

char *readParams() {
    char *str = malloc(0);
    int size = 0;
    char c;

    if(fgetc(stdin) == '"') {
        do {
            c = fgetc(stdin);
            str = realloc(str, (size + 1) * sizeof(char));
            if(c != '"')
                str[size++] = c;
            else
                str[size++] = '\0';
        } while(c != '"');
        fgetc(stdin);
    }

    return str;
}

// função que aloca memória para os campos do regitro de cabecalho
Header allocHeaderRecord(Header* header) {
    header->status = malloc(sizeof(char));
    header->description = malloc(sizeof(char) * 40);
    header->desC1 = malloc(sizeof(char) * 22);
    header->desC2 = malloc(sizeof(char) * 19);
    header->desC3 = malloc(sizeof(char) * 24);
    header->desC4 = malloc(sizeof(char) * 8);
    header->codC5 = malloc(sizeof(char));
    header->desC5 = malloc(sizeof(char) * 16);
    header->codC6 = malloc(sizeof(char));
    header->desC6 = malloc(sizeof(char) * 18);
    header->codC7 = malloc(sizeof(char));
    header->desC7 = malloc(sizeof(char) * 19);

    return *header;
}

// função que desaloca memória dos campos do regitro de cabecalho
void freeHeaderRecord(Header* header) {
    free(header->status);
    free(header->description);
    free(header->desC1);
    free(header->desC2);
    free(header->desC3);
    free(header->desC4);
    free(header->codC5);
    free(header->desC5);
    free(header->codC6);
    free(header->desC6);
    free(header->codC7);
    free(header->desC7);
}

// função que preenche os campos do registro de cabecalho
void fillHeaderRecord(Header* header) {
    memcpy(header->description, "LISTAGEM DA FROTA DOS VEICULOS NO BRASIL", 40);
    memcpy(header->desC1, "CODIGO IDENTIFICADOR: ", 22);
    memcpy(header->desC2, "ANO DE FABRICACAO: ", 19);
    memcpy(header->desC3, "QUANTIDADE DE VEICULOS: ", 24);
    memcpy(header->desC4, "ESTADO: ", 8);
    memcpy(header->codC5, "0", 1);
    memcpy(header->desC5, "NOME DA CIDADE: ", 16);
    memcpy(header->codC6, "1", 1);
    memcpy(header->desC6, "MARCA DO VEICULO: ", 18);
    memcpy(header->codC7, "2", 1);
    memcpy(header->desC7, "MODELO DO VEICULO: ", 19);
    header->top1 = -1;
    header->top2 = -1;
    header->nextRRN = 0;
    header->nextByteOffset = 0;
    header->numRemRec = 0;
}

// função que escreve num arquivo binário os campos do registro de cabecalho
void writeHeaderRecord(FILE* pFileBin , Header header, char* fileType) {
    fwrite(header.status, sizeof(char), 1, pFileBin);
    if(strcmp(fileType, "tipo1") == 0) {
        fwrite(&header.top1, sizeof(int), 1, pFileBin);
    } else if(strcmp(fileType, "tipo2") == 0) {
        fwrite(&header.top2, sizeof(long long int), 1, pFileBin);
    }
    fwrite(header.description, sizeof(char), 40, pFileBin);
    fwrite(header.desC1, sizeof(char), 22, pFileBin);
    fwrite(header.desC2, sizeof(char), 19, pFileBin);
    fwrite(header.desC3, sizeof(char), 24, pFileBin);
    fwrite(header.desC4, sizeof(char), 8, pFileBin);
    fwrite(header.codC5, sizeof(char), 1, pFileBin);
    fwrite(header.desC5, sizeof(char), 16, pFileBin);
    fwrite(header.codC6, sizeof(char), 1, pFileBin);
    fwrite(header.desC6, sizeof(char), 18, pFileBin);
    fwrite(header.codC7, sizeof(char), 1, pFileBin);
    fwrite(header.desC7, sizeof(char), 19, pFileBin);

    if(strcmp(fileType, "tipo1") == 0) {
        fwrite(&header.nextRRN, sizeof(int), 1, pFileBin);
    } else if(strcmp(fileType, "tipo2") == 0) {
        fwrite(&header.nextByteOffset, sizeof(long long int), 1, pFileBin);
    }
    fwrite(&header.numRemRec, sizeof(int), 1, pFileBin);
}

// função que inicializa os campos do registro de dados
void initData(Data* data) {
    data->city = NULL;
    data->brand = NULL;
    data->model = NULL;
    data->state = NULL;
    data->id = -1;
    data->qtt = -1;
    data->year = -1;
    data->next1 = -1;
    data->next2 = -1;
    data->cityLenght = 0;
    data->modelLenght = 0;
    data->brandLenght = 0;
    // tamanho fixo do registro de dados tipo2 contado a partir do field next2
    data->recordLenght = 22;
    memcpy(data->removed, "0", 1);
}


// le os dados do arquivo.csv e preenche os campos do registro de dados
Data getData(Data data, char* line) {
    char *str;
    char *str1;
    char *token;

    initData(&data);

    // duplica a linha lida para str e str1
    str1 = str = strdup(line);

    // strsep separa a string cópia str a cada delimitador "," ,
    // salva em token a substring obtida e elimina o delimitador
    token = strsep(&str, ",");
    data.id = atoi(token);

    token = strsep(&str, ",");
    if(strcmp(token, "") != 0) {
        data.year = atoi(token);
    }

    token = strsep(&str, ",");
    if(strcmp(token, "") != 0) {
        data.cityLenght = (int) strlen(token);
        data.city = malloc(sizeof(char) * data.cityLenght);
        memcpy(data.city, token, data.cityLenght);
        // 5 bytes -> int (cityLenght) + char (codC5)
        data.recordLenght += 5 + data.cityLenght;
    }

    token = strsep(&str, ",");
    if(strcmp(token, "") != 0) {
        data.qtt = atoi(token);
    }

    token = strsep(&str, ",");
    if(strcmp(token, "") != 0) {
        data.state = malloc(sizeof(char) * 2);
        memcpy(data.state, token, 2);
    }

    token = strsep(&str, ",");
    if(strcmp(token, "") != 0) {
        data.brandLenght = (int) strlen(token);
        data.brand = malloc(sizeof(char) * data.brandLenght);
        memcpy(data.brand, token, data.brandLenght);
        data.recordLenght += 5 + data.brandLenght;
    }

    token = strsep(&str, ",");
    if(strcmp(token, "\r\n") != 0) {
        data.modelLenght = (int) strlen(token) - 2; // (-2) -> nao copiar o \r\n
        data.model = malloc(sizeof(char) * data.modelLenght);
        memcpy(data.model, token, data.modelLenght);
        data.recordLenght += 5 + data.modelLenght;
    }

    free(str1);

    return data;
}

// função que escreve um arquivo em binário com as infos dos registros de cabecalho e de dados
void writeBinFile(FILE* pFileBin, Data* data, Header header, char* fileType) {
    fwrite(data->removed, sizeof(char), 1, pFileBin);

    if(strcmp(fileType, "tipo1") == 0) {
        fwrite(&data->next1, sizeof(int), 1, pFileBin);
    } else if(strcmp(fileType, "tipo2") == 0){
        fwrite(&data->recordLenght, sizeof(int), 1, pFileBin);
        fwrite(&data->next2, sizeof(long long int), 1, pFileBin);
    }
    fwrite(&data->id, sizeof(int), 1, pFileBin);
    fwrite(&data->year, sizeof(int), 1, pFileBin);
    fwrite(&data->qtt, sizeof(int), 1, pFileBin);

    if(data->state != NULL) fwrite(data->state, sizeof(char), 2, pFileBin);
    else fwrite("$$", sizeof(char), 2, pFileBin);

    if(data->city != NULL) {
        fwrite(&data->cityLenght, sizeof(int), 1, pFileBin);
        fwrite(header.codC5, sizeof(char), 1, pFileBin);
        fwrite(data->city, sizeof(char), data->cityLenght, pFileBin);
    }
    if(data->brand != NULL) {
        fwrite(&data->brandLenght, sizeof(int), 1, pFileBin);
        fwrite(header.codC6, sizeof(char), 1, pFileBin);
        fwrite(data->brand, sizeof(char), data->brandLenght, pFileBin);
    }
    if(data->model != NULL) {
        fwrite(&data->modelLenght, sizeof(int), 1, pFileBin);
        fwrite(header.codC7, sizeof(char), 1, pFileBin);
        fwrite(data->model, sizeof(char), data->modelLenght, pFileBin);
    }

    if(strcmp(fileType, "tipo1") == 0) {
        long size;
        size = ftell(pFileBin);
        int rrn = getRRN(size);
        if (size < 182 + ((rrn + 1) * 97)) {
            while (size < 182 + ((rrn  + 1) * 97)) {
                fwrite("$", sizeof(char), 1, pFileBin);
                size++;
            }
        }
    }
}

void removeRec(FILE *f, long int byteOffset) {
    int size;
    long int top;
    fseek(f, 1, SEEK_SET);
    fread(&top, sizeof(long int), 1, f);
    fseek(f, -8, SEEK_CUR);
    fwrite(&byteOffset, sizeof(long int), 1, f);
    fseek(f, byteOffset, SEEK_SET);
    fwrite("1", sizeof(char), 1, f);
    fread(&(size), sizeof(int), 1, f);
    fwrite(&top, sizeof(long int), 1, f);
}

void insertRec(FILE *f, Data* record, Header header, char* arqType) {
    long int next;
    int size;
    char removed[1];
    fseek(f, 1, SEEK_SET);
    fread(&next, sizeof(long int), 1, f);
    while(next != -1) {
        fseek(f, next, SEEK_SET);
        fread(removed, sizeof(char), 1, f);
        fread(&size, sizeof(int), 1, f);
        fread(&next, sizeof(long int), 1, f);
        if (record->recordLenght <= size) {
            fseek(f, next, SEEK_SET); // tentar fazer com seek cur
            writeBinFile(f, record, header, arqType);
            return;
        }
    }
}

// função que edita os campos desejados na struct de registro para posterior escrita no arquivo
void editFields(FILE *f,Data* record, Header header, Param *new, char* arqType, int RRN, long int byteOffset) {
    int qtyReg = atoi(new[0].field);
    int oldRecLenght;
    bool hasToRemoveByCity = false;
    bool hasToRemoveByBrand = false;
    bool hasToRemoveByModel = false;


    for (int i = 1; i <= qtyReg; i++) {
        if(strcmp(arqType, "tipo1") == 0) {
            if (strcmp(new[i].field, "id") == 0) {
                if(strncmp(new[i].key, "NULO", 4) == 0) {
                    record->id = -1;
                } else {
                    record->id = atoi(new[i].key);
                }
            } else if (strcmp(new[i].field, "ano") == 0) {
                if(strncmp(new[i].key, "NULO", 4) == 0) {
                    record->year = -1;
                } else {
                    record->year = atoi(new[i].key);
                }
            } else if (strcmp(new[i].field, "qtt") == 0) {
                if(strncmp(new[i].key, "NULO", 4) == 0) {
                    record->qtt = -1;
                } else {
                    record->qtt = atoi(new[i].key);
                }
            } else if (strcmp(new[i].field, "sigla") == 0) {
                if(strncmp(new[i].key, "NULO", 4) == 0) {
                    record->state = NULL;
                } else {
                    record->state = malloc(sizeof(char) * 2);
                    memcpy(record->state, new[i].key, 2);
                }
            } else if (strcmp(new[i].field, "cidade") == 0) {
                if(strncmp(new[i].key, "NULO", 4) == 0) {
                    record->city = NULL;
                } else {
                    record->cityLenght = strlen(new[i].key);
                    record->city = malloc(sizeof(char) * record->cityLenght);
                    memcpy(record->city, new[i].key, record->cityLenght);
                }
            } else if (strcmp(new[i].field, "marca") == 0) {
                if(strncmp(new[i].key, "NULO", 4) == 0) {
                    record->brand = NULL;
                } else {
                    record->brandLenght = strlen(new[i].key);
                    record->brand = malloc(sizeof(char) * record->brandLenght);
                    memcpy(record->brand, new[i].key, record->brandLenght);
                }
            } else if (strcmp(new[i].field, "modelo") == 0) {
                if(strncmp(new[i].key, "NULO", 4) == 0) {
                    record->model = NULL;
                } else {
                    record->modelLenght = strlen(new[i].key);
                    record->model = malloc(sizeof(char) * record->modelLenght);
                    memcpy(record->model, new[i].key, record->modelLenght);
                }
            }
        } else { // tipo2
            if (strcmp(new[i].field, "id") == 0) {
                if (strncmp(new[i].key, "NULO", 4) == 0) {
                    record->id = -1;
                } else {
                    record->id = atoi(new[i].key);
                }
            } else if (strcmp(new[i].field, "ano") == 0) {
                if (strncmp(new[i].key, "NULO", 4) == 0) {
                    record->year = -1;
                } else {
                    record->year = atoi(new[i].key);
                }
            } else if (strcmp(new[i].field, "qtt") == 0) {
                if (strncmp(new[i].key, "NULO", 4) == 0) {
                    record->qtt = -1;
                } else {
                    record->qtt = atoi(new[i].key);
                }
            } else if (strcmp(new[i].field, "sigla") == 0) {
                if (strncmp(new[i].key, "NULO", 4) == 0) {
                    record->state = NULL;
                } else {
                    record->state = malloc(sizeof(char) * 2);
                    memcpy(record->state, new[i].key, 2);
                }
            } else if (strcmp(new[i].field, "cidade") == 0) {
                if (strncmp(new[i].key, "NULO", 4) == 0) {
                    record->city = NULL;
                } else {
                    int oldCityLenght = record->cityLenght;
                    //printf("old city tam: %d\n", record->cityLenght);
                    record->cityLenght = strlen(new[i].key);
                    //printf("new city tam: %d\n", record->cityLenght);
                    oldRecLenght = record->recordLenght;
                    //printf("old rec tam: %d\n", record->recordLenght);
                    record->recordLenght = oldRecLenght - oldCityLenght + record->cityLenght;
                    //printf("new rec tam: %d\n", record->recordLenght);
                    //free(record->city);
                    //record->city = malloc(sizeof(char) * record->cityLenght);
                    record->city = realloc(record->city, sizeof(char) * record->cityLenght);
                    memcpy(record->city, new[i].key, record->cityLenght);
                    if(record->recordLenght <= oldRecLenght) {
                        hasToRemoveByCity = false;
                    } else {
                        hasToRemoveByCity = true;
                    }
                }
            } else if (strcmp(new[i].field, "marca") == 0) {
                if (strncmp(new[i].key, "NULO", 4) == 0) {
                    record->brand = NULL;
                } else {
                    int oldBrandLenght = record->brandLenght;
                    record->brandLenght = strlen(new[i].key);
                    oldRecLenght = record->recordLenght;
                    record->recordLenght = oldRecLenght - oldBrandLenght + record->brandLenght;
                    record->brand = realloc(record->brand, sizeof(char) * record->brandLenght);
                    memcpy(record->brand, new[i].key, record->brandLenght);
                    if (record->recordLenght <= oldRecLenght) {
                        hasToRemoveByBrand = false;
                    } else {
                        hasToRemoveByBrand = true;
                    }
                }
            } else if (strcmp(new[i].field, "modelo") == 0) {
                if (strncmp(new[i].key, "NULO", 4) == 0) {
                    record->model = NULL;
                } else {
                    int oldModelLenght = record->modelLenght;
                    record->modelLenght = strlen(new[i].key);
                    oldRecLenght = record->recordLenght;
                    record->recordLenght = oldRecLenght - oldModelLenght + record->modelLenght;
                    record->model = realloc(record->model, sizeof(char) * record->modelLenght);
                    memcpy(record->model, new[i].key, record->modelLenght);
                    if (record->recordLenght <= oldRecLenght) {
                        hasToRemoveByBrand = false;
                    } else {
                        hasToRemoveByBrand = true;
                    }
                }
            }
        }
    }

    if(strcmp(arqType, "tipo1") == 0) {
        fseek(f, 182 + (RRN * 97), SEEK_SET);
        writeBinFile(f, record, header, arqType);
    } else {
        if(hasToRemoveByCity || hasToRemoveByBrand || hasToRemoveByModel) {
            removeRec(f, byteOffset);
            insertRec(f, record, header, arqType);
            // completar lixo
        } else {
            fseek(f, byteOffset, SEEK_SET);
            writeBinFile(f, record, header, arqType);
            // completar de lixo
        }
    }
}

// função para leitura do input da funcionalidade 8
void readInputForFunc8(Param **p, Param **new, int* qtdParamP, int* qtdParamNew) {
    int qtyParam;
    scanf(" %d ", &qtyParam); //lendo quantos parâmetros serão usados na busca
    *qtdParamP = qtyParam;
    printf("qtd: %d\n", qtyParam);
    (*p) = malloc(sizeof(Param) * (qtyParam + 1));
    printf("+++\n");
    char qtd[10];
    sprintf(qtd, "%d", qtyParam);
    // salvando no primeiro param a quantidade de parÂmetros que o vetor terá (menos ele mesmo)
    strcpy((*p)[0].field, qtd);
    char c;
    for(int i = 1; i <= qtyParam; i++) { //lendo os parâmetros, com field e chave
        strcpy((*p)[i].field, readWord());
        printf("field: %s\n", (*p)[i].field);
        if(strcmp((*p)[i].field, "id") == 0 || strcmp((*p)[i].field, "ano") == 0 || strcmp((*p)[i].field, "qtt") == 0) { // campos inteiros
            (*p)[i].key = readWord();
            printf("valor: %s\n", (*p)[i].key);
        } else { //campos string
            (*p)[i].key = readQuoted();
            printf("valor: %s\n", (*p)[i].key);
        }
    }

    int qtyNewParam;
    scanf(" %d ", &qtyNewParam); //lendo quantos parâmetros serão usados na busca
    *qtdParamNew = qtyNewParam;
    (*new) = malloc(sizeof(Param) * (qtyNewParam + 1));
    sprintf(qtd, "%d", qtyNewParam);
    // salvando no primeiro param a quantidade de parÂmetros que o vetor terá (menos ele mesmo)
    strcpy((*new)[0].field, qtd);
    for(int i = 1; i <= qtyNewParam; i++) { //lendo os parâmetros, com field e chave
        strcpy((*new)[i].field, readWord());
        printf("new field: %s\n", (*new)[i].field);
        if(strcmp((*new)[i].field, "id") == 0 || strcmp((*new)[i].field, "ano") == 0 || strcmp((*new)[i].field, "qtt") == 0) { // campos inteiros
            (*new)[i].key = readWord();
            printf("new valor: %s\n", (*new)[i].key);
        } else { //campos string
            (*new)[i].key = readQuoted3();
            printf("new valor: %s\n", (*new)[i].key);
        }
    }
}




