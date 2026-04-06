#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include"btree.h"

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

// função que cria um arquivo de índice árvore-B para um arquivo de dados de entrada já
// existente
void functionality9(char *arqType, char *inputFile, char *outputFile) {
    FILE *f = fopen(inputFile, "rb+");
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
    // passando o nome do arquivo de dados na struct Param
    // para não ter que alterar os parâmetros da função search registers
    searchRegBTree(9, arqTypeInt, outputFile, f, NULL);
    binarioNaTela(outputFile);
    free(outputFile);    

    setConsistency(f);    
}

// função que permite a recuperação dos dados de todos os registros que satisfaçam um critério
//de busca determinado pelo usuário sobre o campo id, usando o índice árvore-B criado
//na funcionalidade [9]
void functionality10(char *arqType, char *inputFile, char *outputFile, int n) {
    FILE *f = fopen(inputFile, "rb+");

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

    searchById(f, arqTypeInt, outputFile, n);
    free(outputFile);    

    setConsistency(f);
}

void functionalityPrintIndex(char *arqType, char *inputFile) {
    FILE *f = fopen(inputFile, "rb+");

    if(f == NULL) {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    checkConsistency(f);
    fwrite("0", sizeof(char), 1, f); //arquivo inconsistente

    int arqTypeInt;
    if(strcmp(arqType, "tipo1") == 0) {
        arqTypeInt = 1;
    } else {
        arqTypeInt = 2;
    }

    lerArquivoIndice(f, arqTypeInt);

    setConsistency(f);   
}

// função que permite a inserção de novos registros em um arquivo de dados de entrada de um
// determinado tipo, baseado na abordagem dinâmica de reaproveitamento de espaços de
// registros logicamente removidos, uitlizando btree como organização de arquivo de índice.
void functionality11(char* arqType, char* dataFile, char* indexFile, int n) {
    FILE *f = fopen(dataFile, "rb+");
    FILE *fp = fopen(indexFile, "rb+");
    if(f == NULL || fp == NULL) {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    checkConsistency(f);
    checkConsistency(fp);
    fwrite("0", sizeof(char), 1, f); //arquivo inconsistente
    fwrite("0", sizeof(char), 1, fp); //arquivo inconsistente

    Data data_rec;
    Header header;
    allocHeaderRecord(&header);
    fillHeaderRecord(&header);

    int intArqType;
    int top; // armazena o RRN
    int nextRRN; // indica o proximo RRN disponivel para inserir um registro
    int nRemovedRecs; // numero de registros removidos

    int recSize; // tamanho do registro de dados
    long int top2; // armazena o byteOffset
    long int nextByteOffset; // armazena o proximo byteOffset para insercao

    int raiz, proxRRN, numNos; // armazena valores que serão usados na btree

    if(strcmp(arqType, "tipo1") == 0) {
        fseek(f, 182, SEEK_SET);
        intArqType = 1;
    } else {
        fseek(f, 190, SEEK_SET);
        intArqType = 2;
    }

    while (n > 0) {
        initData(&data_rec);
        char *idBuffer, *yearBuffer, *qttBuffer;

        idBuffer = readWord();
        if(strcmp(idBuffer, "NULO") != 0) {
            data_rec.id = atoi(idBuffer);
        } else {
            data_rec.id = -1;
        }
        yearBuffer = readWord();
        if(strcmp(yearBuffer, "NULO") != 0) {
            data_rec.year = atoi(yearBuffer);
        } else {
            data_rec.year = -1;
        }
        qttBuffer = readWord();
        if(strcmp(qttBuffer, "NULO") != 0) {
            data_rec.qtt = atoi(qttBuffer);
        } else {
            data_rec.qtt = -1;
        }
        data_rec.state = readQuoted2();
        data_rec.city = readQuoted2();
        data_rec.city != NULL ? data_rec.cityLenght = strlen(data_rec.city) : 0;
        data_rec.brand = readQuoted2();
        data_rec.brand != NULL ? data_rec.brandLenght = strlen(data_rec.brand) : 0;
        data_rec.model = readQuoted2();
        data_rec.model != NULL ? data_rec.modelLenght = strlen(data_rec.model) : 0;

        fseek(fp, 1, SEEK_SET);
        fread(&raiz, sizeof(int), 1, fp);
        fread(&proxRRN, sizeof(int), 1, fp);
        fread(&numNos, sizeof(int), 1, fp);

        if(strcmp(arqType, "tipo1") == 0) {
            intArqType = 1;

            fseek(f, 1, SEEK_SET);
            fread(&top, sizeof(int), 1, f);

            if (top == -1) { // nao há registro removido, insere no final
                fseek(f, 174, SEEK_SET); // vai pro campo que indica o prox RRN disponível
                fread(&nextRRN, sizeof(int), 1, f);

                fseek(f, 0, SEEK_END);
                writeBinFile(f, &data_rec, header, arqType);

                fseek(f, 174, SEEK_SET);
                int newNextRRN = nextRRN + 1;
                fwrite(&newNextRRN, sizeof(int), 1, f);

                // insere o id e RRN do novo registro na btree
                driver_alg(fp, &raiz, &proxRRN, &numNos, data_rec.id, nextRRN, intArqType);

            } else { // tem registro removido
                fseek(f, 178, SEEK_SET); // campo do número de registros removidos
                fread(&nRemovedRecs, sizeof(int), 1, f);

                fseek(f, 182 + (top * 97) + 1, SEEK_SET);

                // encontra o RRN aonde será inserido o novo registro
                long int offset = ftell(f);
                long int RRN = getRRN(offset);
                driver_alg(fp, &raiz, &proxRRN, &numNos, data_rec.id, RRN, intArqType);

                fread(&top, sizeof(int), 1, f); // lê o campo next que será o novo top
                fseek(f, -5, SEEK_CUR); // volta para o começo do registro de dados
                writeBinFile(f, &data_rec, header, arqType);
                nRemovedRecs -= 1;

                fseek(f, 1, SEEK_SET);
                fwrite(&top, sizeof(int), 1, f);

                fseek(f, 178, SEEK_SET);
                fwrite(&nRemovedRecs, sizeof(int), 1, f);
            }

        } else if(strcmp(arqType, "tipo2") == 0) {
            intArqType = 2;

            fseek(f, 1, SEEK_SET);
            fread(&top2, sizeof(long int), 1, f);

            if(top2 == -1) { // não há registro removido, insere no final
                fseek(f, 178, SEEK_SET);
                fread(&nextByteOffset, sizeof(int), 1, f);

                driver_alg(fp, &raiz, &proxRRN, &numNos, data_rec.id, nextByteOffset, intArqType);

                fseek(f, 0, SEEK_END);
                writeBinFile(f, &data_rec, header, arqType);
                nextByteOffset = ftell(f); // novo valor de nextByteOffset

                fseek(f, 178, SEEK_SET);
                fwrite(&nextByteOffset, sizeof(long int), 1, f);

            } else { // tem registro removido
                fseek(f, 186, SEEK_SET); // campo do número de registros removidos
                fread(&nRemovedRecs, sizeof(int), 1, f);

                // tamanho total dos campos envolvendo cidade, marca e modelo
                int cityRecSize = 0, brandRecSize = 0, modelRecSize = 0;
                data_rec.cityLenght > 0 ? cityRecSize = 5 + data_rec.cityLenght : 0;
                data_rec.brandLenght > 0 ? brandRecSize = 5 + data_rec.brandLenght : 0;
                data_rec.modelLenght > 0 ? modelRecSize = 5 + data_rec.modelLenght : 0;

                // tamanho total do registro a partir do campo next
                int recLenght = 22 + cityRecSize + brandRecSize + modelRecSize;

                fseek(f, top2 + 1, SEEK_SET);
                fread(&recSize, sizeof(int), 1, f);
                int newTop2; // valor que sera o novo top2
                fread(&newTop2, sizeof(long int), 1, f);

                if(recLenght < recSize) { // se o registro cabe no espaco, insere nesse espaco
                    fseek(f, -13, SEEK_CUR);
                    data_rec.recordLenght = recSize;

                    writeBinFile(f, &data_rec, header, arqType);

                    driver_alg(fp, &raiz, &proxRRN, &numNos, data_rec.id, top2, intArqType);

                    nextByteOffset = ftell(f); // marca o byteOffset do final da escrita

                    // se necessario completa de lixo
                    if(nextByteOffset < top2 + recSize + 5) {
                        while(nextByteOffset < top2 + recSize + 5) {
                            fwrite("$", sizeof(char), 1, f);
                            nextByteOffset++;
                        }
                    }

                    fseek(f, 1, SEEK_SET);
                    fwrite(&newTop2, sizeof(long int), 1, f);

                    nRemovedRecs -= 1;
                    fseek(f, 186, SEEK_SET);
                    fwrite(&nRemovedRecs, sizeof(int), 1, f);

                } else { // registro não cabe no espaco, então insere no final
                    fseek(f, 178, SEEK_SET);
                    fread(&nextByteOffset, sizeof(long int), 1, f);

                    driver_alg(fp, &raiz, &proxRRN, &numNos, data_rec.id, nextByteOffset, intArqType);

                    fseek(f, 0, SEEK_END);

                    data_rec.recordLenght = recLenght;
                    writeBinFile(f, &data_rec, header, arqType);
                    nextByteOffset = ftell(f);

                    fseek(f, 178, SEEK_SET);
                    fwrite(&nextByteOffset, sizeof(long int), 1, f);
                }
            }
        }
        free(idBuffer);free(yearBuffer);free(qttBuffer);
        free(data_rec.state);free(data_rec.city);free(data_rec.brand);free(data_rec.model);

        n--;
    }

    freeHeaderRecord(&header);

    setConsistency(f);
    binarioNaTela(dataFile);
    setConsistency(fp);
    binarioNaTela(indexFile);
}