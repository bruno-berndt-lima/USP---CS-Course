#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"utils.h"
#include"search.h"
#include"btree.h"
#include"functionalities.h"


int getByteOffset1(int rrn) {
    return 45 + rrn * 45;
}

int getByteOffset2(int rrn) {
    return 57 + rrn * 57;
}

int getRRN1(long int byteOffset) {
    return (byteOffset - 45) / 45;
}

int getRRN2(long int byteOffset) {
    return (byteOffset - 57) / 57;
}

long int getOffsetReg1(int rrn) {
    return 182 + 97 * rrn;
}

FILE *createBT(char *name, int arqType) {
    FILE *f = fopen(name, "wb");
    fwrite("0", sizeof(char), 1, f);
    int num = -1;
    fwrite(&(num), sizeof(int), 1, f);
    num = 0;
    fwrite(&(num), sizeof(int), 1, f);
    fwrite(&(num), sizeof(int), 1, f);
    if(arqType == 1) {
        char str[] = "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$";
        fwrite(str, sizeof(char), 32, f);
    } else {
        char str[] = "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$";
        fwrite(str, sizeof(char), 44, f);
    }
    fclose(f);
    fopen(name, "rb+");
    return f;
}


void split(int insert_key, long int insert_conteudo, int *insert_rrn_dir, no2 *no, int *promo_key, long int *promo_conteudo, int *promo_r_child, int *promo_l_child, no2 *newPage, int *prox, int arqType) {
    insert_key = *promo_key;
    insert_conteudo = *promo_conteudo;
    *insert_rrn_dir = *promo_r_child;
    
    no2 *workingPage = malloc(sizeof(no2));
    int temp_key = insert_key;
    int offsetTemp = 0;

    for(int i = 0; i < 4; i++) {
        workingPage->chaves[i] = -1;
    }

    workingPage->ponteiros[0] = no->ponteiros[0];

    for(int i = 0; i < 4; i++) {
        if(insert_key < no->chaves[i] && temp_key != -1) {
            workingPage->chaves[i] = insert_key;
            workingPage->conteudo[i] = insert_conteudo;
            workingPage->ponteiros[i + 1] = *insert_rrn_dir;

            temp_key = -1;
            offsetTemp = 1;
        } else {
            if(i == 3 && temp_key == insert_key) {
                workingPage->chaves[i] = insert_key;
                workingPage->conteudo[i] = insert_conteudo;
                workingPage->ponteiros[i + 1] = *insert_rrn_dir;
                break;
            }
            workingPage->chaves[i] = no->chaves[i - offsetTemp];
            workingPage->conteudo[i] = no->conteudo[i - offsetTemp];
            workingPage->ponteiros[i + 1] = no->ponteiros[i - offsetTemp + 1];
        }
    }

    *promo_key = workingPage->chaves[2];
    *promo_conteudo = workingPage->conteudo[2];
    *promo_r_child = *prox;


    no->numChaves = 2;
    no->chaves[0] = workingPage->chaves[0];
    no->chaves[1] = workingPage->chaves[1];
    no->chaves[2] = -1;
    no->conteudo[0] = workingPage->conteudo[0];
    no->conteudo[1] = workingPage->conteudo[1];
    no->conteudo[2] = -1;
    no->ponteiros[0] = workingPage->ponteiros[0];
    no->ponteiros[1] = workingPage->ponteiros[1];
    no->ponteiros[2] = workingPage->ponteiros[2];
    no->ponteiros[3] = -1;


    newPage->numChaves = 1;
    strcpy(&(newPage->tipo), "1");
    //newPage->tipo = "1";
    newPage->rrnNo = *prox;
    if(arqType == 1)
        newPage->offsetNo = getByteOffset1(newPage->rrnNo);
    else
        newPage->offsetNo = getByteOffset2(newPage->rrnNo);

    newPage->chaves[0] = workingPage->chaves[3];
    newPage->conteudo[0] = workingPage->conteudo[3];        
    newPage->ponteiros[1] = workingPage->ponteiros[4];

    newPage->chaves[1] = -1;
    newPage->conteudo[1] = -1;
    newPage->chaves[2] = -1;
    newPage->conteudo[2] = -1;
    newPage->chaves[3] = -1;
    newPage->conteudo[3] = -1;
    newPage->ponteiros[0] = *promo_l_child;
    newPage->ponteiros[2] = -1;
    newPage->ponteiros[3] = -1;

    free(workingPage);
}

int inserirNo(FILE *f, no2 *no, int cur_rrn, int key, long int conteudo, int *promo_key, long int *promo_conteudo, int *promo_r_child, int *promo_l_child, int *prox, int arqType) {
    no2 *newPage = malloc(sizeof(no2));

    int pos;
    int return_value;
    int p_b_rrn;

    if(cur_rrn == -1) {
        *promo_key = key;
        *promo_conteudo = conteudo;
        *promo_r_child = -1; // isso está me incomodando
        free(newPage);
        return 1;
    } else {
        if(arqType == 1)
            fseek(f, getByteOffset1(cur_rrn), SEEK_SET);
        else
            fseek(f, getByteOffset2(cur_rrn), SEEK_SET);

        no->offsetNo = ftell(f);
        fread(&no->tipo, sizeof(char), 1, f);
        fread(&no->numChaves, sizeof(int), 1, f);

        for(int i = 0; i < 3; i++) {
            fread(&no->chaves[i], sizeof(int), 1, f);
            if(arqType == 1)
                fread(&no->conteudo[i], sizeof(int), 1, f);
            else
                fread(&no->conteudo[i], sizeof(long int), 1, f);
        }             
        for(int i = 0; i < 4; i++) {
            fread(&no->ponteiros[i], sizeof(int), 1, f);
        }
        no->rrnNo = cur_rrn;

        pos = 0;
        for(int i = 0; i < 3; i++) {
            if(no->chaves[i] == key) {
                free(newPage);
                return -1;
            }                
            if(no->chaves[i] > 0 && no->chaves[i] < key)
                pos = i + 1;
        }

        p_b_rrn = no->ponteiros[pos + 1];
        return_value = inserirNo(f, no, no->ponteiros[pos], key, conteudo, promo_key, promo_conteudo, promo_r_child, promo_l_child, prox, arqType);

        if(return_value == 0) { // já inseriu
            free(newPage);
            return 0;
        } else {
            if(arqType == 1)
                fseek(f, getByteOffset1(cur_rrn), SEEK_SET);
            else
                fseek(f, getByteOffset2(cur_rrn), SEEK_SET);


            no->offsetNo = ftell(f);
            fread(&no->tipo, sizeof(char), 1, f);
            fread(&no->numChaves, sizeof(int), 1, f);

            for(int i = 0; i < 3; i++) {
                fread(&no->chaves[i], sizeof(int), 1, f);
                if(arqType == 1)
                    fread(&no->conteudo[i], sizeof(int), 1, f);
                else
                    fread(&no->conteudo[i], sizeof(long int), 1, f);
            }             
            for(int i = 0; i < 4; i++) {
                fread(&no->ponteiros[i], sizeof(int), 1, f);
            }
            no->rrnNo = cur_rrn;

            if(no->numChaves < 3) {
                if(*promo_key < no->chaves[0]) {
                    no->chaves[2] = no->chaves[1];
                    no->conteudo[2] = no->conteudo[1];
                    no->chaves[1] = no->chaves[0];
                    no->conteudo[1] = no->conteudo[0];

                    no->ponteiros[3] = no->ponteiros[2];
                    no->ponteiros[2] = no->ponteiros[1];
                    no->ponteiros[1] = *promo_r_child;

                    no->chaves[0] = *promo_key;
                    no->conteudo[0] = *promo_conteudo;
                } else if(*promo_key < no->chaves[1] || no->chaves[1] < 0) {
                    no->chaves[2] = no->chaves[1];
                    no->conteudo[2] = no->conteudo[1];

                    no->ponteiros[3] = no->ponteiros[2];
                    no->ponteiros[2] = *promo_r_child;

                    no->chaves[1] = *promo_key;
                    no->conteudo[1] = *promo_conteudo;
                } else {
                    no->chaves[2] = *promo_key;
                    no->conteudo[2] = *promo_conteudo;
                    no->ponteiros[3] = *promo_r_child;
                }
                no->numChaves = no->numChaves + 1;
                free(newPage);
                return 0;
            } else {
                split(key, conteudo, &p_b_rrn, no, promo_key, promo_conteudo, promo_r_child, promo_l_child, newPage, prox, arqType);

                //if(strcmp(novoNo->tipo, "0") != 0)
                strcpy(&(no->tipo), "2");
                //if(strcmp(newPage->tipo, "0") != 0)
                strcpy(&(newPage->tipo), "2");


                for(int i = 0; i < 4; i++) {
                    if(no->ponteiros[i] != -1) {
                        strcpy(&(no->tipo), "1");
                    }
                    if(newPage->ponteiros[i] != -1) {
                        strcpy(&(newPage->tipo), "1");
                    }
                }

                if(arqType == 1)
                    fseek(f, getByteOffset1(no->rrnNo), SEEK_SET);
                else
                    fseek(f, getByteOffset2(no->rrnNo), SEEK_SET);


                fwrite(&(no->tipo), 1, 1, f);
                fwrite(&(no->numChaves), 4, 1, f);
                for(int i = 0; i < 3; i++) {
                    fwrite(&(no->chaves[i]), 4, 1, f);
                    if(arqType == 1)
                        fwrite(&(no->conteudo[i]), 4, 1, f);
                    else
                        fwrite(&(no->conteudo[i]), sizeof(long int), 1, f);
                }
                for(int i = 0; i < 4; i++) {
                    fwrite(&(no->ponteiros[i]), 4, 1, f);                
                }
                
                //seek final
                fseek(f, 0, SEEK_END);
                fwrite(&(newPage->tipo), 1, 1, f);
                fwrite(&(newPage->numChaves), 4, 1, f);
                for(int i = 0; i < 3; i++) {
                    fwrite(&(newPage->chaves[i]), 4, 1, f);
                    if(arqType == 1)
                        fwrite(&(newPage->conteudo[i]), 4, 1, f);
                    else
                        fwrite(&(newPage->conteudo[i]), sizeof(long int), 1, f);
                }
                for(int i = 0; i < 4; i++) {
                    fwrite(&(newPage->ponteiros[i]), 4, 1, f);                
                }

                *prox = newPage->rrnNo + 1;
                *promo_r_child = newPage->rrnNo;
                *promo_l_child = no->rrnNo;    

                free(newPage);
                return 1;
            }
        }
    }
}

void driver_alg(FILE *f, int *raiz, int *prox, int *numNos, int key, long int conteudo, int arqType) {
    if(*raiz == -1) {
        fseek(f, 1, SEEK_SET);
        *raiz = 0;
        fwrite(&(*raiz), sizeof(int), 1, f);
        *prox = 1;
        fwrite(&(*prox), sizeof(int), 1, f);
        *numNos = 1;
        fwrite(&(*numNos), sizeof(int), 1, f);
        if(arqType == 1)
            fseek(f, 32, SEEK_CUR);
        else
            fseek(f, 44, SEEK_CUR);
            
        //escrevendo primeiro item do primeiro nó
        fwrite("0", 1, 1, f); //tipo no raiz
        long int num = 1;
        fwrite(&(num), sizeof(int), 1, f);
        fwrite(&(key), sizeof(int), 1, f);
        
        if(arqType == 1) {
            num = conteudo;
            fwrite(&(num), sizeof(int), 1, f);
            num = -1;
            fwrite(&(num), sizeof(int), 1, f);
            fwrite(&(num), sizeof(int), 1, f);
            fwrite(&(num), sizeof(int), 1, f);
            fwrite(&(num), sizeof(int), 1, f);
        } else {
            num = conteudo;
            fwrite(&(num), sizeof(long int), 1, f);
            num = -1;
            fwrite(&(num), sizeof(int), 1, f);
            fwrite(&(num), sizeof(long int), 1, f);
            fwrite(&(num), sizeof(int), 1, f);
            fwrite(&(num), sizeof(long int), 1, f);
        }


        //ponteiros
        fwrite(&(num), sizeof(int), 1, f);
        fwrite(&(num), sizeof(int), 1, f);
        fwrite(&(num), sizeof(int), 1, f);
        fwrite(&(num), sizeof(int), 1, f);
        
        return;
    }

    no2 *no = malloc(sizeof(no2));
    for(int i = 0; i < 3; i++) {
        no->chaves[i] = -1;
        no->conteudo[i] = -1;
    }
    for(int i = 0; i < 4; i++) {
        no->ponteiros[i] = -1;
    }

    int promo_key = -1;
    long int promo_conteudo = -1;
    int promo_r_child = -1;
    int promo_l_child = -1;

    if(inserirNo(f, no, *raiz, key, conteudo, &promo_key, &promo_conteudo, &promo_r_child, &promo_l_child, prox, arqType) == 1) {
        fseek(f, 0, SEEK_END);
            if(arqType == 1) {
                int novaRaiz = ftell(f);

                fwrite("0", 1, 1, f);
                int num = 1;
                fwrite(&(num), sizeof(int), 1, f);
                fwrite(&(promo_key), sizeof(int), 1, f);
                fwrite(&(promo_conteudo), sizeof(int), 1, f);
                num = -1;
                fwrite(&(num), sizeof(int), 1, f);
                fwrite(&(num), sizeof(int), 1, f);
                fwrite(&(num), sizeof(int), 1, f);
                fwrite(&(num), sizeof(int), 1, f);
                fwrite(&(*raiz), sizeof(int), 1, f);
                fwrite(&(promo_r_child), sizeof(int), 1, f);
                fwrite(&(num), sizeof(int), 1, f);
                fwrite(&(num), sizeof(int), 1, f);


                *raiz = getRRN1(novaRaiz);
                *prox = *prox + 1;
                fseek(f, 0, SEEK_END);

                *numNos = getRRN1(ftell(f));
            } else {
                int novaRaiz = ftell(f);

                fwrite("0", 1, 1, f);
                long int num = 1;
                fwrite(&(num), sizeof(int), 1, f);
                fwrite(&(promo_key), sizeof(int), 1, f);
                fwrite(&(promo_conteudo), sizeof(long int), 1, f);
                num = -1;
                fwrite(&(num), sizeof(int), 1, f);
                fwrite(&(num), sizeof(long int), 1, f);
                fwrite(&(num), sizeof(int), 1, f);
                fwrite(&(num), sizeof(long int), 1, f);
                fwrite(&(*raiz), sizeof(int), 1, f);
                fwrite(&(promo_r_child), sizeof(int), 1, f);
                fwrite(&(num), sizeof(int), 1, f);
                fwrite(&(num), sizeof(int), 1, f);


                *raiz = getRRN2(novaRaiz);
                *prox = *prox + 1;
                fseek(f, 0, SEEK_END);

                *numNos = getRRN2(ftell(f));
            }
            

            fseek(f, 1, SEEK_SET);
            fwrite(&(*raiz), sizeof(int), 1, f);
            fwrite(&(*prox), sizeof(int), 1, f);
            fwrite(&(*numNos), sizeof(int), 1, f);
    } else {
        if(arqType == 1) {
            fseek(f, getByteOffset1(no->rrnNo) + 1, SEEK_SET);

            int num = 1;
            fwrite(&(no->numChaves), sizeof(int), 1, f);
            for(int i = 0; i < 3; i++) {
                fwrite(&(no->chaves[i]), sizeof(int), 1, f);
                fwrite(&(no->conteudo[i]), sizeof(int), 1, f);
            }
            for(int i = 0; i < 4; i++) {
                fwrite(&(no->ponteiros[i]), sizeof(int), 1, f);
            }
        } else {
            fseek(f, getByteOffset2(no->rrnNo) + 1, SEEK_SET);

            int num = 1;
            fwrite(&(no->numChaves), sizeof(int), 1, f);
            for(int i = 0; i < 3; i++) {
                fwrite(&(no->chaves[i]), sizeof(int), 1, f);
                fwrite(&(no->conteudo[i]), sizeof(long int), 1, f);
            }
            for(int i = 0; i < 4; i++) {
                fwrite(&(no->ponteiros[i]), sizeof(int), 1, f);
            }
        }

        fseek(f, 1, SEEK_SET);
        fwrite(&(*raiz), sizeof(int), 1, f);
        fwrite(&(*prox), sizeof(int), 1, f);
        fwrite(&(*prox), sizeof(int), 1, f);

    }
}

void lerPagina(no2 *pagina, FILE *idFile, int arqType) {
    fread(&(pagina->tipo), 1, 1, idFile);
    fread(&(pagina->numChaves), 4, 1, idFile);
    for(int i = 0; i < 3; i++) {
        fread(&(pagina->chaves[i]), 4, 1, idFile);
        if(arqType == 1)
            fread(&(pagina->conteudo[i]), 4, 1, idFile);
        else
            fread(&(pagina->conteudo[i]), 8, 1, idFile);
    }
    for(int i = 0; i < 4; i++) {
        fread(&(pagina->ponteiros[i]), 4, 1, idFile);
    }
    //printPage(pagina);
}

void searchById(FILE *f, int arqTypeInt, char *outputFile, int id) {
    FILE *idFile = fopen(outputFile, "rb+");
    if(!idFile) {
        printf("Falha no processamento do arquivo.");
        exit(0);
    }

    checkConsistency(idFile);
    fwrite("0", 1, 1, idFile);

    no2 *pagina = malloc(sizeof(no2));

    int raiz;
    fread(&(raiz), 4, 1, idFile);

    Data *registro = NULL;
    while(registro == NULL && raiz != -1) {
        if(arqTypeInt == 1)
            fseek(idFile, getByteOffset1(raiz), SEEK_SET);
        else
            fseek(idFile, getByteOffset2(raiz), SEEK_SET);

        lerPagina(pagina, idFile, arqTypeInt);

        int pos = 0;

        if(id < pagina->chaves[0]) {
            raiz = pagina->ponteiros[0];
            continue;
        }

        for(int i = 0; i < pagina->numChaves; i++) {
            if(id > pagina->chaves[i]) {
                pos++;
            } else { break; }
        }

        if(id == pagina->chaves[pos]) {
            if(arqTypeInt == 1)
                fseek(f, getOffsetReg1(pagina->conteudo[pos]), SEEK_SET);
            else
                fseek(f, pagina->conteudo[pos], SEEK_SET);  

            char rem;
            fread(&(rem), 1, 1, f);
            if(strcmp(&(rem), "1") == 0) {
                raiz = -1;
                break;
            }

            registro = malloc(sizeof(Data));
            if(arqTypeInt == 1)
                readReg1(f, registro);
            else {
                readReg2(f, registro);
            }

            printReg(*registro);
            free(registro);
            break;
        }
        else {
            raiz = pagina->ponteiros[pos];
        }
    }

    if(raiz == -1) {
        printf("Registro inexistente.\n");
    }


    free(pagina);
    fseek(idFile, 0, SEEK_SET);
    setConsistency(idFile);
}


void searchRegBTree(int funcType, int arqType, char *indexFileName, FILE *f, FILE *fp) {
    FILE *indexFile;
    int raiz, proxRRN, numNos;

    if(funcType == 9) {
        indexFile = createBT(indexFileName, arqType);
        raiz = -1;
        proxRRN = 0;
        numNos = 0;
    } else if(funcType == 11) {
        fseek(fp, 1, SEEK_SET);
        fread(&raiz, sizeof(int), 1, fp);
        printf("raiz: %d\n", raiz);
        fread(&proxRRN, sizeof(int), 1, fp);
        printf("prox: %d\n", proxRRN);
        fread(&numNos, sizeof(int), 1, fp);
        printf("numNos: %d\n", numNos);
    }

    int hasRecord = 0; // flag para ver se pelo menos um registro foi impresso

    long int qtyReg = -1;
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

        // incluindo registro na btree
        if(funcType == 9) {
            //void driver_alg(FILE *f, int *raiz, int *prox, int *numNos, int key, long int conteudo, int arqType);
            if(arqType == 1)
                driver_alg(indexFile, &raiz, &proxRRN, &numNos, record.id, qtyReg, arqType);
            else
                driver_alg(indexFile, &raiz, &proxRRN, &numNos, record.id, offset, arqType);
        } else if(funcType == 11) {
            if(arqType == 1) {
                driver_alg(fp, &raiz, &proxRRN, &numNos, record.id, qtyReg, arqType);
            }
            else
                driver_alg(fp, &raiz, &proxRRN, &numNos, record.id, offset, arqType);
        }

        freeMemReg(&record);
}

    if(funcType == 9) {
        fseek(indexFile, 0, SEEK_SET);
        fwrite("1", 1, 1, indexFile);
        fclose(indexFile);
    }
}


void lerArquivoIndice(FILE *f, int arqType) {
    fseek(f, 1, SEEK_SET);
    int raiz, proxRRN, numNos;
    fread(&(raiz), sizeof(int), 1, f);
    fread(&(proxRRN), sizeof(int), 1, f);
    fread(&(numNos), sizeof(int), 1, f);
    printf("raiz %d\nprox rrn: %d\nNumnos: %d\n", raiz, proxRRN, numNos);

    if(arqType == 1) {
        fseek(f, 45, SEEK_SET);
        for(int i = 0; i < numNos; i++) {
            char tipo;
            int numChaves;
            fread(&(tipo), 1, 1, f);
            fread(&(numChaves), sizeof(int), 1, f);
            printf("Nó %d\nTipo: %c\nNumChaves: %d\n", i, tipo, numChaves);

            int chave, conteudo, ponteiro;
            for(int j = 0; j < 3; j++) {
                fread(&(chave), sizeof(int), 1, f);
                fread(&(conteudo), sizeof(int), 1, f);
                printf("Chave %d: %d; conteudo: %d\n", j, chave, conteudo);
            }
            for(int j = 0; j < 4; j++) {
                fread(&(ponteiro), sizeof(int), 1, f);
                printf("Ponteiro %d: %d\n", j, ponteiro);
            }
            printf("\n");
        }
    } else {
        fseek(f, 57, SEEK_SET);

        for(int i = 0; i < numNos; i++) {
            char tipo;
            int numChaves;
            fread(&(tipo), 1, 1, f);
            fread(&(numChaves), sizeof(int), 1, f);
            printf("Nó %d\nTipo: %c\nNumChaves: %d\n", i, tipo, numChaves);

            int chave, conteudo, ponteiro;
            for(int j = 0; j < 3; j++) {
                fread(&(chave), sizeof(int), 1, f);
                fread(&(conteudo), sizeof(long int), 1, f);
                printf("Chave %d: %d; conteudo: %d\n", j, chave, conteudo);
            }
            for(int j = 0; j < 4; j++) {
                fread(&(ponteiro), sizeof(int), 1, f);
                printf("Ponteiro %d: %d\n", j, ponteiro);
            }
            printf("\n");
        }
    }
}