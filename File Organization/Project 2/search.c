#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"utils.h"
#include"search.h"
#include"indexUtils.h"
#include "removeUtils.h"


// função para ler um registro de arquivo do tipo 1, dado o arquivo e
// a struct Data onde as informações serão armazenadas
void readReg1(FILE *f, Data *record) {
    //lendo os campos de tamanho fixo do record
    fread(&(record->next1), sizeof(int), 1, f);
    fread(&(record->id), sizeof(int), 1, f);
    fread(&(record->year), sizeof(int), 1, f);
    fread(&(record->qtt), sizeof(int), 1, f);
    record->state = malloc(sizeof(char) * 2);
    fread(record->state, sizeof(char), 2, f);
    //printf("leu: %c", record->state[0]);
    //printf("%c ", record->state[1]);

    // ler campos de tamanho variável
    int i;
    for(i = 0; i < 3; i++) {
        int byteQty; // vai ser o tamanho do field, caso não seja lixo

        fread(&(byteQty), sizeof(int), 1, f); //lendo 4 bytes

        if(byteQty == 606348324) { //se os bytes são lixo ($$$$)
            break;
        }

        char codChar; // código da informação
        fread(&(codChar), sizeof(char), 1, f);
        int codInt = atoi(&codChar);
        if(codInt == 0) { //cidade
            record->cityLenght = byteQty;
            record->city = malloc(record->cityLenght * sizeof(char) + 1);
            fread(record->city, sizeof(char), record->cityLenght, f);
            record->city[byteQty] = '\0';
        } else if(codInt == 1) { //marca
            record->brandLenght = byteQty;
            record->brand = malloc(record->brandLenght * sizeof(char) + 1);
            fread(record->brand, sizeof(char), record->brandLenght, f);
            record->brand[byteQty] = '\0';
        } else if(codInt == 2){ //modelo
            record->modelLenght = byteQty;
            record->model = malloc(record->modelLenght * sizeof(char) + 1);
            fread(record->model, sizeof(char), record->modelLenght, f);
            record->model[byteQty] = '\0';
        }
    }

    int offset = 19; // tamanho da parte fixa do record
    //tamanho dos campos de tamanho variável
    offset += record->cityLenght + record->brandLenght + record->modelLenght;
    //quantos bytes a mais foram lidos
    if(i == 0)
        offset += 4;
    if(i == 1)
        offset += 9;
    if(i == 2)
        offset += 14;
    if(i == 3)
        offset += 15;

    offset = 97 - offset;
    //indo para o fim do record
    fseek(f, offset, SEEK_CUR);
}

// função para ler um registro de arquivo do tipo 2, dado o
// arquivo e a struct Data onde as informações serão armazenadas
void readReg2(FILE *f, Data *record) {
    //lendo os campos de tamanho fixo
    fread(&(record->recordLenght), sizeof(int), 1, f);
    fread(&(record->next2), sizeof(long int), 1, f);
    fread(&(record->id), sizeof(int), 1, f);
    fread(&(record->year), sizeof(int), 1, f);
    fread(&(record->qtt), sizeof(int), 1, f);
    record->state = malloc(2);
    fread(record->state, sizeof(char), 2, f);

    //quantos bytes faltam para terminar o record: a quantidade informada no record - a
    // quantidade de bytes que foram lidas até aqui (exceto os campos removido e tamanho)
    int remaningBytes = record->recordLenght - 22;
    // ler campos de tamanho variável
    for(int i = 0; i < 3; i++) {
        //printf("resta: %d\n", remaningBytes);
        if(remaningBytes - 4 < 0) break; // caso não tenha próximo field de tamanho variável
        int byteQty; // vai ser o tamanho do field, caso exista
        fread(&(byteQty), sizeof(int), 1, f); //lendo 4 bytes
        //printf("bytes: %d\n", byteQty);

        char codChar; // código da informação
        fread(&(codChar), sizeof(char), 1, f);
        //printf("cod: %c\n", codChar);
        //int codInt = atoi(codChar);
        int codInt = codChar - '0';
        //printf("codint: %d\n", codInt);
        if(codInt == 0) { //cidade
            record->cityLenght = byteQty;
            record->city = malloc(record->cityLenght * sizeof(char) + 1);
            fread(record->city, sizeof(char), record->cityLenght, f);
            record->city[byteQty] = '\0';
            //printf("city: %s\n", record->city);
            remaningBytes -= (5 + byteQty);
        } else if(codInt == 1) { //marca
            record->brandLenght = byteQty;
            record->brand = malloc(record->brandLenght * sizeof(char) + 1);
            fread(record->brand, sizeof(char), record->brandLenght, f);
            record->brand[byteQty] = '\0';
            //printf("brand: %s\n", record->brand);
            remaningBytes -= (5 + byteQty);
        } else if(codInt == 2){ //modelo
            record->modelLenght = byteQty;
            record->model = malloc(record->modelLenght * sizeof(char) + 1);
            fread(record->model, sizeof(char), record->modelLenght, f);
            record->model[byteQty] = '\0';
            //printf("model: %s\n", record->model);
            remaningBytes -= (5 + byteQty);
        }
    }
}

// função para imprimir um record
void printReg(Data record) {
    char year[8];
    char qtt[20];
    //convertendo as infos inteiras para string
    sprintf(year, "%d", record.year);
    sprintf(qtt, "%d", record.qtt);
    printf("ID: %d\n", record.id);
    printf("MARCA DO VEICULO: %s\n", (record.brandLenght == 0) ? "NAO PREENCHIDO" : record.brand);
    printf("MODELO DO VEICULO: %s\n", (record.modelLenght == 0) ? "NAO PREENCHIDO" : record.model);
    printf("ANO DE FABRICACAO: %s\n", (record.year == -1) ? "NAO PREENCHIDO" : year);
    printf("NOME DA CIDADE: %s\n", (record.cityLenght == 0) ? "NAO PREENCHIDO" : record.city);
    printf("QUANTIDADE DE VEICULOS: %s\n", (record.qtt == -1) ? "NAO PREENCHIDO" : qtt);
    printf("\n");
}

//função que libera a memória de um registro
void freeMemReg(Data *record) {
    if(record->state != NULL)
        free(record->state);
    if(record->city != NULL)
        free(record->city);
    if(record->model != NULL)
        free(record->model);
    if(record->brand != NULL)
        free(record->brand);
}

// função que compara as informações de um registro com os filtros dados por Param,
// retorna 1 caso o registro passe no filtro, 0 caso o registro não passe no filtro
int regComp(Data record, Param *p) {
    
    int qtyReg = atoi(p[0].field);

    for(int i = 1; i <= qtyReg; i++) {
        char field[20];
        strcpy(field, p[i].field);

        if(strcmp(field, "id") == 0) {
            if(record.id != atoi(p[i].key)) return 0;
        } else if(strcmp(field, "ano") == 0) {
            if(record.year != atoi(p[i].key)) return 0;
        } else if(strcmp(field, "qtt") == 0) {
            if(record.qtt != atoi(p[i].key)) return 0;
        } else if(strcmp(field, "sigla") == 0) {
            if(strncmp(record.state, p[i].key, 2) != 0) return 0;
            //printf("comp: %c%c %s\n", record.state[0], record.state[1], p[i].key);
        } else if(strcmp(field, "cidade") == 0) {
            if(record.city == NULL) return 0;
            if(strncmp(record.city, p[i].key, record.cityLenght) != 0) return 0;
            //printf("comp city: %s %s\n", record.city, p[i].key);
        } else if(strcmp(field, "marca") == 0) {
            if(record.brand == NULL) return 0;
            if(strncmp(record.brand, p[i].key, record.brandLenght) != 0) return 0;
            //printf("comp marca: %s %s %d\n", record.brand, p[i].key, record.brandLenght);
        } else if(strcmp(field, "modelo") == 0)  {
            if(record.model == NULL) return 0;
            if(strncmp(record.model, p[i].key, record.modelLenght) != 0) return 0;
            //printf("comp modelo: %s %s %d\n", record.model, p[i].key, record.modelLenght);
        }
    }
    return 1;
}

/*
* função que controla a busca de um registro no arquivo;
* funcType: qual tipo de funcionalidade está sendo executada
* arqType: tipo do arquivo que será lido
* p: struct de parametros que será usada para busca no caso de funcionalidade 3.
* Caso seja outra funcionalidade, se trata de uma struct não alocada
*/
void searchRegisters(int funcType, int arqType, Param *p, FILE *f, int** RRNs, long int** byteOffsets) {
    int hasRecord = 0; // flag para ver se pelo menos um registro foi impresso
    // variáveis para funcionalidade 5
    long int qtyReg = -1;
    IDE *entries = malloc(0);
    int entryCount = 0;
    //---------------------------------
    int size = 0;

    char removed;
    while((removed = fgetc(f)) != EOF) { // vai ler sempre o primeiro byte de um registro até que chegue no fim do arquivo
        //inicializando um record
        Data record;
        record.state = NULL;
        record.city = NULL;
        record.brand = NULL;
        record.model = NULL;
        record.cityLenght = 0;
        record.brandLenght = 0;
        record.modelLenght = 0;
        record.id = -1;
        record.qtt = -1;
        record.year = -1;

        qtyReg++;

        int recBytes = 0; //quantidade de bytes do registro, é usado no arquivo de tipo 2
        long int offset = ftell(f) - 1;
        if(removed == '1') { //pulando para o próximo registro caso seja um registro removido
            if(arqType == 1) {
                fseek(f, 96, SEEK_CUR);
                continue;
            } else {
                fread(&(recBytes), sizeof(int), 1, f);
                fseek(f, recBytes, SEEK_CUR);
                continue;
            }
        }
        // chamando as leituras do registro de acordo com o tipo de arquivo
        if(arqType == 1) {
            readReg1(f, &record);
        } else {
            readReg2(f, &record);
        }

        // funções de impressão e filtro dependendo da funcionalidade
        if(funcType == 2) {
            printReg(record);
            hasRecord = 1;
        } else if(funcType == 3) { // funcionalidade 3 - imprimir com filtro
            if(regComp(record, p) == 1) {
                printReg(record);
                hasRecord = 1;
            }
        } else if(funcType == 5) { // funcionalidade 5 - escrever arquivo de índice
            // insertEntry é função do indexUtils e insere uma entrada ordenadamente na struct entries
            if(arqType == 1) {
                insertEntry(record.id, qtyReg, &entries, &entryCount);
            } else {
                insertEntry(record.id, offset, &entries, &entryCount);
            }            
        } else if(funcType == 8) {
            if(arqType == 1) {
                if (regComp(record, p) == 1) {
                    long int byteOffset = ftell(f) - 1;
                    int rrn = getRRN(byteOffset);
                    (*RRNs) = realloc((*RRNs), sizeof(*RRNs) * (size + 1));
                    (*RRNs)[size] = rrn;
                    size++;
                }
            } else {
                if (regComp(record, p) == 1) {
                    printReg(record);
                    //printf("%d %s %s %s %s\n", record.id, record.state, record.city, record.brand, record.model);
                    //printf("reclen %d\n", record.recordLenght);
                    long int byteOffset = ftell(f) - record.recordLenght - 5;
                    //printf("-> %ld\n", byteOffset);
                    //printf("entrou0\n");
                    (*byteOffsets) = realloc((*byteOffsets), sizeof(*byteOffsets) * (size + 1));
                    (*byteOffsets)[size] = byteOffset;
                    size++;
                    //printf("entrou1\n");
                    //printf("-> %ld\n", byteOffset);
                }

            }
        }

        freeMemReg(&record);
    }

    // para a funcionalidade 5, vai agora criar o arquivo de índice e escrever ele
    if(funcType == 5) {
        FILE *indexFile = fopen(p[0].key, "wb");
        writeIndexFile(&indexFile, entries, entryCount, arqType);
        
        fseek(indexFile, 0, SEEK_SET);
        fwrite("1", sizeof(char), 1, indexFile);        
        fclose(indexFile);

        binarioNaTela(p[0].key);
        hasRecord++;
    }
    if(funcType == 8) {
        if(arqType == 1) {
            (*RRNs) = realloc((*RRNs), sizeof(*RRNs) * (size + 1));
            (*RRNs)[size] = -1;

        } else {
            (*byteOffsets) = realloc((*byteOffsets), sizeof(*byteOffsets) * (size + 1));
            (*byteOffsets)[size] = -1;
        }
        hasRecord++;
    }
    
    free(entries);

    // caso nenhum registro tenha sido impresso
    if(hasRecord == 0) {
        printf("Registro inexistente.\n");
    }
}