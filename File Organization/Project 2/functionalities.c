#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"
#include "utils.h"
#include"removeUtils.h"
#include"indexUtils.h"

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

        writeBinFile(pFileBin, &data, header, arqType);

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
    searchRegisters(2, arqTypeInt, p, f, NULL, NULL);

    setConsistency(f);
}

// função que lê parâmetros de busca e chama uma busca com esses parâmetros,
// linear, direto no arquivo de dados de um determinado tipo
void functionality3(char *arqType, char *fileName) {
    int qtyParam;
    scanf(" %d ", &qtyParam); //lendo quantos parâmetros serão usados na busca
    Param *p = malloc((qtyParam + 1)* sizeof(Param));
    char qtd[10];
    sprintf(qtd, "%d", qtyParam);
    // salvando no primeiro param a quantidade de parÂmetros que o vetor terá (menos ele mesmo)
    strcpy(p[0].field, qtd);
    char c;
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
    searchRegisters(3, arqTypeInt, p, f, NULL, NULL);

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

// função parar criar um arquivo de índice para um arquivo de dados,
// dados os nomes de cada arquivo e o tipo do arquivo de dados
void functionality5(char *arqType, char *inputFile, char *outputFile) {
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
    Param *p = malloc(sizeof(Param));
    p[0].key = malloc(sizeof(char) * strlen(outputFile));
    strcpy(p[0].key, outputFile);
    free(outputFile);
    searchRegisters(5, arqTypeInt, p, f, NULL, NULL);
    free(p[0].key);
    free(p);
    

    setConsistency(f);
}

// função de remoção lógica de registro de um arquivo de dados. Lê parâmetros para
// saber quais registros serão removidos, e chama a função que realiza a remoção
void functionality6(char *arqType, char *frota, char *indices) {
    // abrindo arquivos para verificar se existem e checando a consistência deles.
    // Fecha em seguida
    FILE *f = fopen(frota, "rb");
    if(f == NULL) {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    checkConsistency(f);
    fclose(f);
    f = fopen(indices, "rb");
    if(f == NULL) {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
    checkConsistency(f);
    fclose(f);

    // leitura dos parâmetros de remoção
    int qtdReg;
    scanf(" %d ", &qtdReg);

    Param **p = malloc((qtdReg) * sizeof(Param *));

    // a função de ler parâmetros da funcionalidade 3 e da funcionalidade 6 são diferentes;
    // a outra usa readQuoted() e essa usa readParams(), isso porque, como o formato de entrada
    // dos dois é levemente diferente, não foi possível reutilizar a função
    for(int i = 0; i < qtdReg; i++) {
        int qtdParam;
        scanf(" %d ", &qtdParam);
        p[i] = malloc(qtdParam * sizeof(Param));

        for(int j = 0; j < qtdParam; j++) {
            p[i][j].qtdParam = qtdParam;
            strcpy(p[i][j].field, readWord());

            if(strcmp(p[i][j].field, "id") == 0 || strcmp(p[i][j].field, "ano") == 0 || strcmp(p[i][j].field, "qtt") == 0) { // campos inteiros
                p[i][j].key = readWord();
            } else { //campos string
                p[i][j].key = readParams();
            }
        }
    }

    // verificando tipo de arquivo
    int arqTypeInt;
    if(strcmp(arqType, "tipo1") == 0) {
        arqTypeInt = 1;
    } else {
        arqTypeInt = 2;
    }

    searchAndRemove(arqTypeInt, frota, indices, p, qtdReg);

    //liberando memória da struct de parâmetros
    for(int i = 0; i < qtdReg; i++) {
        int qtdP = p[i][0].qtdParam;
        for(int j = 0; j < qtdP; j++) {
            free(p[i][j].key);
        }
        free(p[i]);
    }
    free(p);

    binarioNaTela(frota);
    binarioNaTela(indices);
    
    free(indices);
}

// função que permite a inserção de novos registros em um arquivo de dados de entrada de um
// determinado tipo, baseado na abordagem dinâmica de reaproveitamento de espaços de
// registros logicamente removidos.
void functionality7(char* arqType, char* dataFile, char* indexFile, int n) {
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
    initData(&data_rec);

    Header header;
    allocHeaderRecord(&header);
    fillHeaderRecord(&header);

    IDE *entry;
    int qttEntries = 0;
    int qtdEnt = 0;

    int top; // armazena o RRN
    int nextRRN; // indica o proximo RRN disponivel para inserir um registro
    int nRemovedRecs; // numero de registros removidos

    int recSize; // tamanho do registro de dados
    long int top2; // armazena o byteOffset
    long int nextByteOffset; // armazena o proximo byteOffset para insercao

    if(strcmp(arqType, "tipo1") == 0)
        entry = readIndexFile1(&fp, (&qttEntries));
    else
        entry = readIndexFile2(&fp, &qttEntries);
    qtdEnt = qttEntries - 2;

    int arqTypeInt;
    while(n > 0) {
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

        if(strcmp(arqType, "tipo1") == 0) {
            arqTypeInt = 1;

            fseek(f, 1, SEEK_SET);
            fread(&top, sizeof(int), 1, f);

            if (top == -1) { // nao ha registro removido, insere no final
                fseek(f, 174, SEEK_SET); // vai pro campo que indica o prox RRN disponivel
                fread(&nextRRN, sizeof(int), 1, f);

                fseek(f, 0, SEEK_END);
                writeBinFile(f, &data_rec, header, arqType);

                fseek(f, 174, SEEK_SET);
                int newNextRRN = nextRRN + 1;
                fwrite(&newNextRRN, sizeof(int), 1, f);

                insertEntry(data_rec.id, nextRRN, &entry, &nextRRN);
                writeIndexFile(&fp, entry, newNextRRN, arqTypeInt);

            } else { // tem registro removido
                fseek(f, 178, SEEK_SET); // campo do número de registros removidos
                fread(&nRemovedRecs, sizeof(int), 1, f);

                insertEntry(data_rec.id, top, &entry, &qtdEnt);
                writeIndexFile(&fp, entry, qtdEnt, arqTypeInt);

                fseek(f, 182 + (top * 97) + 1, SEEK_SET);
                fread(&top, sizeof(int), 1, f); // le o campo next que sera o novo top

                fseek(f, -5, SEEK_CUR); // volta para o comeco do registro de dados
                writeBinFile(f, &data_rec, header, arqType);
                nRemovedRecs -= 1;

                fseek(f, 1, SEEK_SET);
                fwrite(&top, sizeof(int), 1, f);

                fseek(f, 178, SEEK_SET);
                fwrite(&nRemovedRecs, sizeof(int), 1, f);
            }

        } else if(strcmp(arqType, "tipo2") == 0) {
            arqTypeInt = 2;

            fseek(f, 1, SEEK_SET);
            fread(&top2, sizeof(long int), 1, f);

            if(top2 == -1) { // nao ha registro removido, insere no final
                fseek(f, 178, SEEK_SET);
                fread(&nextByteOffset, sizeof(int), 1, f);

                insertEntry(data_rec.id, nextByteOffset, &entry, &qtdEnt);
                writeIndexFile(&fp, entry, qtdEnt, arqTypeInt);

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

                    insertEntry(data_rec.id, top2, &entry, &qtdEnt);
                    writeIndexFile(&fp, entry, qtdEnt, arqTypeInt);
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

                } else { // registro nao cabe no espaco, entao insere no final
                    fseek(f, 178, SEEK_SET);
                    fread(&nextByteOffset, sizeof(long int), 1, f);

                    insertEntry(data_rec.id, nextByteOffset, &entry, &qtdEnt);
                    writeIndexFile(&fp, entry, qtdEnt, arqTypeInt);

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

// função que permite a atualização de registros de um arquivo de dados de entrada de um
// determinado tipo, baseado na abordagem dinâmica de reaproveitamento de espaços de
// registros logicamente removidos.
void functionality8(char* arqType, char* dataFile, char* indexFile, int n) {
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

    IDE *entry;
    int qttEntries = 0;
    int qtdEnt = 0;

    Param *p; // guardará os campos e os valores que devem ser realizada a atualização
    Param *new; // guardará os novos valores e os campos a serem atualizados
    int intArqType;

    Data record;
    Header header;
    allocHeaderRecord(&header);
    fillHeaderRecord(&header);

    if(strcmp(arqType, "tipo1") == 0) {
        entry = readIndexFile1(&fp, &qttEntries);
        qtdEnt = qttEntries - 2;
        fseek(f, 182, SEEK_SET);
        intArqType = 1;
    } else {
        entry = readIndexFile2(&fp, &qttEntries);
        qtdEnt = qttEntries - 2;
        fseek(f, 190, SEEK_SET);
        intArqType = 2;
    }

    int qtdParamP, qtdParamNew;
    int idIdx; // guardará a posição na struct p, caso um dos parâmetros seja o id
    int fieldIdFlag = 0; // flag para caso a busca use o id
    while (n > 0) {
        printf("heyhey\n");
        readInputForFunc8(&p, &new, &qtdParamP, &qtdParamNew);

        printf("heyhey2\n");

        int qtyReg = atoi(p[0].field);
        for (int j = 1; j <= qtyReg; j++) {
            // se a busca do campo a ser atualizado for por id
            if(strcmp(p[j].field, "id") == 0) {
                fieldIdFlag = 1;
                idIdx = j;
            }
        }
        printf("heyhey3\n");

        if (strcmp(arqType, "tipo1") == 0) {

            if(fieldIdFlag) { // se a atualização envolver o campo id
                int rrn = binSearch(entry, atoi(p[idIdx].key), qtdEnt);
                printf("heyhey4\n");

                fseek(f, 182 + (97 * rrn), SEEK_SET);
                initData(&record);
                fread(record.removed, sizeof(char), 1, f);
                readReg1(f, &record); // le os valores atuais do registro desejado
                // se o registro possui os valores que devem ser atualizados
                if(regComp(record, p) == 1) {
                    editFields(f, &record, header, new, arqType, rrn, -1);
                    freeMemReg(&record);
                }
                // atualiza o arquivo de índice
                fseek(f, 0, SEEK_END);
                long int end = ftell(f);
                int endRRN = getRRN(end);
                removeFromEntries(entry, &qtdEnt, atoi(p[idIdx].key), endRRN);
                int newIndex;
                fseek(f, 187 + (97 * rrn), SEEK_SET);
                fread(&newIndex, sizeof(int), 1, f);
                insertEntry(newIndex, rrn, &entry, &qtdEnt);
                writeIndexFile(&fp, entry, qtdEnt, intArqType);

            } else { // se a atualização não envolver o campo id
                // vetor de int para guardar os RRNs dos campos a serem atualizados
                int* RRNs = malloc(sizeof(int));
                RRNs[0] = -1;
                fseek(f, 182, SEEK_SET);
                searchRegisters(8, intArqType, p, f, &RRNs, NULL);
                printf("heyhey5\n");
                for (int j = 0; RRNs[j] != -1; ++j) {
                    fseek(f, 182 + (97 * RRNs[j]), SEEK_SET);
                    initData(&record);
                    fread(record.removed, sizeof(char), 1, f);
                    readReg1(f, &record);
                    editFields(f, &record, header, new, arqType, RRNs[j], -1);
                    freeMemReg(&record);
                }

                free(RRNs);
            }

        } else { // arquivo do tipo2
            if(fieldIdFlag) { // se a atualização envolver o campo id
                //printf("entrou\n");
                long int byteOffset = getLocation(entry, atoi(p[idIdx].key), qtdEnt);
                //printf("%ld\n", byteOffset);
                fseek(f, byteOffset, SEEK_SET);
                initData(&record);
                fread(record.removed, sizeof(char), 1, f);
                //printf("%c\n", record.removed[0]);
                readReg2(f, &record); // le os valores atuais do registro desejado

                // se o registro possui os valores que devem ser atualizados
                //printf("entrou2\n");
                if(regComp(record, p) == 1) {
                    editFields(f, &record, header, new, arqType, -1, byteOffset);
                    //printf("entrou3\n");
                    freeMemReg(&record);
                }
                // remover do arquivo de indice

            } else {
                //printf("entrou2\n");
                long int* byteOffsets = malloc(sizeof(long int));
                fseek(f, 190, SEEK_SET);
                /*printf("old: %s\n", p[1].key);
                printf("new: %s\n", new[1].key);*/
                searchRegisters(8, intArqType, p, f, NULL, &byteOffsets);
                for (int j = 0; byteOffsets[j] != -1; ++j) {
                    //printf("%ld\n", byteOffsets[j]);
                    fseek(f, byteOffsets[j], SEEK_SET);
                    //printf("entrou1\n");
                    initData(&record);
                    fread(record.removed, sizeof(char), 1, f);
                    //printf("rem: %c\n", record.removed[0]);

                    readReg2(f, &record);
                    //printf("entrou2\n");
                    editFields(f, &record, header, new, arqType, -1, byteOffsets[j]);
                    //printf("entrou3\n");
                    freeMemReg(&record);
                }
                free(byteOffsets);
                //freeMemReg(&record);
            }
        }
        for (int i = 1; i <= qtdParamP; i++) {
            //printf("--> %s %s\n", p[i].field, p[i].key);
            free(p[i].key);
        }

        for (int i = 1; i <= qtdParamNew; i++) {
            //printf("-> %s %s\n", new[i].field, new[i].key);
            free(new[i].key);
        }
        free(p);
        free(new);

        fieldIdFlag = 0;
        n--;
    }
    printf("hello\n");
    freeHeaderRecord(&header);

    setConsistency(f);
    binarioNaTela(dataFile);
    setConsistency(fp);
    binarioNaTela(indexFile);
}


