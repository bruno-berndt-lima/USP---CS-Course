#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"
#include "utils.h"

// função que verifica a consistência do arquivo
void checkConsistency(FILE* f) {
    char cons;
    fseek(f, 0, SEEK_SET);
    fread(&(cons), sizeof(char), 1, f);
    fseek(f, 0, SEEK_SET);
    if(cons == '0') {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
}

// função para setar a consistência do arquivo para 1
void setConsistency(FILE* f) {
    fseek(f, 0, SEEK_SET);
    fwrite("1", sizeof(char), 1, f); //arquivo consistente
    fclose(f);
}

// função que permite a leitura de vários registros obtidos a partir de um
// arquivo de entrada no formato csv e a gravação desses registros
void functionality1(char* arqType, char* inputFile, char* outputFile, Data data, Header header) {
    FILE* pFileCsv; // ponteiro para o arquivo.csv que será lido os dados
    FILE* pFileBin; // ponteiro para o arquivo binário que será escrito os dados em binário
    pFileCsv = fopen(inputFile, "r");
    pFileBin = fopen(outputFile, "wb");
    if (pFileCsv == NULL || pFileBin == NULL) {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }

    memcpy(header.status, "0", 1);

    char line[100];

    char *temp = malloc(sizeof(char) * 61); // primeira linha do arquivo.csv
    fread(temp, sizeof(char), 61, pFileCsv);

    // escreve os campos do registro de cabecalho primeiro
    writeHeaderRecord(pFileBin, header, arqType);

    while (fgets(line, sizeof(line), pFileCsv) != NULL) {
        data = getData(data, line);
        header.nextRRN++;

        writeBinFile(pFileBin, data, header, header.nextRRN, arqType);

        freeMemReg(&data);
    }

    fseek(pFileBin, 0, SEEK_END);
    header.nextByteOffset = ftell(pFileBin);
    memcpy(header.status, "1", 1);
    fseek(pFileBin, 0, SEEK_SET);
    // reescreve os campos do registro de cabecalho atualizado
    writeHeaderRecord(pFileBin, header, arqType);

    free(temp);
    fclose(pFileBin);
    binarioNaTela(outputFile);
    fclose(pFileCsv);
}

// função que permite a recuperação dos dados de todos os registros armazenados
// em um arquivo de dados de entrada de um determinado tipo
void functionality2(char *arqType, char *fileName) { // SELECT * FROM
    FILE *f = fopen(fileName, "rb+");
    if(f == NULL) {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }

    checkConsistency(f);
    fwrite("0", sizeof(char), 1, f); //arquivo inconsistente

    int arqTypeInt;

    if(strcmp(arqType, "tipo1") == 0) {
        fseek(f, 182, SEEK_SET);
        arqTypeInt = 1;
    } else {
        fseek(f, 190, SEEK_SET);
        arqTypeInt = 2;
    }

    Param *p;
    searchRegisters(2, arqTypeInt, p, f);

    setConsistency(f);
}

// função que permite a recuperação dos dados de todos os registros de um
// arquivo de dados de entrada de um determinado tipo
void functionality3(char *arqType, char *fileName) {
    int qtyParam;
    scanf(" %d ", &qtyParam); //lendo quantos parâmetros serão usados na busca

    Param *p = malloc((qtyParam + 1)* sizeof(Param));
    char qtd[10];
    sprintf(qtd, "%d", qtyParam);
    // salvando no primeiro param a quantidade de parÂmetros que o vetor terá (menos ele mesmo)
    strcpy(p[0].field, qtd);

    for(int i = 1; i <= qtyParam; i++) { //lendo os parâmetros, com field e chave
        strcpy(p[i].field, readWord());

        if(strcmp(p[i].field, "id") == 0 || strcmp(p[i].field, "ano") == 0 || strcmp(p[i].field, "qtt") == 0) { // campos inteiros
            p[i].key = readWord();
        } else { //campos string
            p[i].key = readQuoted();
        }
    }
    //abrindo o arquivo
    FILE *f = fopen(fileName, "rb+");
    if(f == NULL) {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    checkConsistency(f);
    fwrite("0", sizeof(char), 1, f); //arquivo inconsistente
    //determinando o tipo de arquivo que será usado
    int arqTypeInt;
    if(strcmp(arqType, "tipo1") == 0) {
        fseek(f, 182, SEEK_SET);
        arqTypeInt = 1;
    } else {
        fseek(f, 190, SEEK_SET);
        arqTypeInt = 2;
    }

    //buscando registros no modo de funcionalidade 3
    searchRegisters(3, arqTypeInt, p, f);

    setConsistency(f);

    //desalocando memória da struct Param
    for(int i = 1; i <= qtyParam; i++) {
        free(p[i].key);
    }
    free(p);
}

// função que permite a recuperação dos dados de um registro de um arquivo de
// dados de entrada que seja do tipo1, a partir da identificação do RRN
void functionality4(char* arqType, char* inputFile, Data data, int RRN) {
    if(strcmp(arqType, "tipo1") != 0 || RRN < 0) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    FILE* pFile = fopen(inputFile, "rb+");
    if (pFile == NULL) {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }

    checkConsistency(pFile);
    fwrite("0", sizeof(char), 1, pFile); //arquivo inconsistente

    // procedimento para descobrir o tamanho do arquivo
    fseek(pFile, 0, SEEK_END);
    long fileSize = ftell(pFile);

    // se o RRN passado extrapolar o tamanho do arquivo, esse registro não existe
    if(182 + (RRN * 97) >= fileSize) {
        printf("Registro inexistente.\n");
        setConsistency(pFile);
        return;
    }
    initData(&data);

    // coloca o cursor no field "removido" do registro de dados
    fseek(pFile, 182 + (RRN * 97), SEEK_SET);
    fread(data.removed, sizeof(char), 1, pFile);
    // se o registro não estiver sido removido
    if(data.removed[0] == '1') {
        // caso contrário, o registro foi removido e portanto não existe
        printf("Registro inexistente.\n");
        setConsistency(pFile);
        return;
    }

    readReg1(pFile, &data);

    printReg(data);

    freeMemReg(&data);

    setConsistency(pFile);
}