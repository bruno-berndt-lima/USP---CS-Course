#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"utils.h"
#include"search.h"

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
        if(remaningBytes - 4 < 0) break; // caso não tenha próximo field de tamanho variável
        int byteQty; // vai ser o tamanho do field, caso exista

        fread(&(byteQty), sizeof(int), 1, f); //lendo 4 bytes

        char codChar; // código da informação
        fread(&(codChar), sizeof(char), 1, f);
        int codInt = atoi(&codChar);
        if(codInt == 0) { //cidade
            record->cityLenght = byteQty;
            record->city = malloc(record->cityLenght * sizeof(char) + 1);
            fread(record->city, sizeof(char), record->cityLenght, f);
            record->city[byteQty] = '\0';
            remaningBytes -= (5 + byteQty);
        } else if(codInt == 1) { //marca
            record->brandLenght = byteQty;
            record->brand = malloc(record->brandLenght * sizeof(char) + 1);
            fread(record->brand, sizeof(char), record->brandLenght, f);
            record->brand[byteQty] = '\0';
            remaningBytes -= (5 + byteQty);
        } else if(codInt == 2){ //modelo
            record->modelLenght = byteQty;
            record->model = malloc(record->modelLenght * sizeof(char) + 1);
            fread(record->model, sizeof(char), record->modelLenght, f);
            record->model[byteQty] = '\0';
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
    //printf("ID: %d\n", record.id);
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

