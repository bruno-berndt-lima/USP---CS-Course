#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"removeUtils.h"
#include"functionalities.h"
#include"indexUtils.h"
#include"search.h"

// retorna byte offset a partir de RRN
long int getByteOffset(int rrn) {
    return(182 + (rrn * 97));
}
// retorna RRN a partir de byte offset
long int getRRN(long int byteOffset) {
    return (byteOffset - 182)/97;
}

// cria uma nova struct para ler registro
Data initializeData() {
    Data record;
    record.state = NULL;
    record.city = NULL;
    record.brand = NULL;
    record.model = NULL;
    record.cityLenght = 0;
    record.brandLenght = 0;
    record.modelLenght = 0;
    record.id = -1;

    return record;
}

// faz as comparações necessárias para saber se um registro deve ser removido
// retorna 1 caso deva ser removido, 0 caso não
// é levemente diferente da função regComp, do search.c, pois aqui a quantidade
// de parâmetros é passada na chamada e o primeiro parâmetro já se encontra
// no índice 0 do array de parâmetros
int removeComp(Data record, Param *p, int qtdParam) {
    for(int i = 0; i < qtdParam; i++) {
        char field[20];
        strcpy(field, p[i].field);
        
        if(strcmp(field, "id") == 0) {
            if(record.id != atoi(p[i].key)) return 0;
        } else if(strcmp(field, "ano") == 0) {
            if(record.year != atoi(p[i].key)) return 0;
        } else if(strcmp(field, "qtt") == 0) {
            if(record.qtt != atoi(p[i].key)) return 0;
        } else if(strcmp(field, "sigla") == 0) {
            if(strcmp(record.state, p[i].key) != 0) return 0;
        } else if(strcmp(field, "cidade") == 0) {
            if(record.city == NULL) return 0;
            if(strcmp(record.city, p[i].key) != 0) return 0;
        } else if(strcmp(field, "marca") == 0) {
            if(record.brand == NULL) return 0;
            if(strcmp(record.brand, p[i].key) != 0) return 0;
        } else if(strcmp(field, "modelo") == 0)  {
            if(record.model == NULL) return 0;
            if(strcmp(record.model, p[i].key) != 0) return 0;
        }
    }
    return 1;
}

// função que busca registros e remove eles, de acordo com o tipo de arquivo. é grande
void searchAndRemove(int arqType, char *dataFileName, char *indexFileName, Param **p, int qtdReg) {
    // abrindo arquivo; existência e consistência foram checadas em functionalities
    FILE *f = fopen(dataFileName, "rb+");
    fwrite("0", sizeof(char), 1, f);

    // para arquivo de dados tipo1
    if(arqType == 1) {
        // campos do cabeçalho
        int topo, proxRRN, numRegRem;
        fread(&(topo), sizeof(int), 1, f);
        fseek(f, 174, SEEK_SET);
        fread(&(proxRRN), sizeof(int), 1, f);
        fread(&(numRegRem), sizeof(int), 1, f);

        // carregando arquivo de índice na memória
        FILE *id = fopen(indexFileName, "rb+");
        fwrite("0", sizeof(char), 1, id);

        int qtyEnt = 0;
        IDE *entries = readIndexFile1(&id, &qtyEnt);
        qtyEnt = qtyEnt - 2;
        

        // pilha que armazena indices removidos, exclusividade de arquivos tipo 1
        rmStack *stack = createStack(qtyEnt + 1);

        // iterando pelos comandos de remoção, os parâmetros passados
        // qtdReg é a quantidade de comandos de remoção recebidos
        for(int i = 0; i < qtdReg; i++) {
            fseek(f, 182, SEEK_SET); // indo para o primeiro registro
            
            int idRem = -1; // id do registro que será removido
            
            //verificando se algum dos parâmetros passados foi o ID
            //caso tenha sido, vai salvar no idRem o valor, e fará a remoção sem
            //percorrer o arquivo sequencialmente
            int qtdPar = p[i]->qtdParam;
            for(int j = 0; j < qtdPar; j++) {
                if(strcmp(p[i][j].field, "id") == 0) {
                    int rrnLer = getLocation(entries, atoi(p[i][j].key), qtyEnt);
                    if(rrnLer == -1) {
                        idRem = -2; // isso quer dizer que o id não foi encontrado no arquivo de índices, logo não deve existir
                        break;      // no arquivo de dados também
                    }
                    fseek(f, getByteOffset(rrnLer), SEEK_SET); // colocando o cursor no início do registro buscado
                    Data record = initializeData();
                    char c = fgetc(f);
                    if(c == '1') { // verificando se ele já foi removido
                        idRem = -2;
                        break;
                    }
                    readReg1(f, &record); // lendo o registro
                    if(removeComp(record, p[i], qtdPar) == 1) { // verificando se ele se encaixa em todos os parâmetros de remoção             
                        idRem = atoi(p[i][j].key);
                    } else { idRem = -2; }
                    freeMemReg(&record);
                    break;
                }
            }

            if(idRem == -2) { //registro teve id encontrado mas não corresponde a critérios de busca
                continue;
            }

            if(idRem == -1) { // id não foi passado como parâmetro
                Data record;
                char c;
                while(1) { // percorrendo arquivo de dados sequencialmente
                    int offsetReg = ftell(f); // offset do início do registro
                    int rrnAtual = getRRN(offsetReg);
                    c = fgetc(f);
                    if(c == EOF) break;

                    if(c == '1') { // caso registro seja removido, pula ele
                        fseek(f, 96, SEEK_CUR);
                        continue;
                    }
                    //iniciando e lendo registro
                    record = initializeData();
                    readReg1(f, &record);

                    int offsetFinal = ftell(f); // offset do fim do registro
                    
                    if(removeComp(record, p[i], qtdPar) == 1) { // caso o registro tenha que ser removido, faz a remoção logica
                        fseek(f, offsetReg, SEEK_SET);
                        fwrite("1", sizeof(char), 1, f);
                        fwrite(&(topo), sizeof(int), 1, f);
                        topo = rrnAtual;
                        fread(&(idRem), sizeof(int), 1, f);
                        fseek(f, offsetFinal, SEEK_SET);
                        // empilhando id do removido, que será usado para atualizar o arquivo de índice
                        stackPush(stack, idRem);
                    }
                }
                idRem = -1;
                freeMemReg(&record);
                continue; // indo para o próximo registro
            }
            
            // caso o id tenha sido informado, vai realizar a remoção lógica aqui
            int removeRRN = getLocation(entries, idRem, qtyEnt);
            int removeOffset = getByteOffset(removeRRN);
            
            fseek(f, removeOffset, SEEK_SET);
            fwrite("1", sizeof(char), 1, f);
            fwrite(&(topo), sizeof(int), 1, f);
            topo = removeRRN;
            // empilhando id do removido para atualizar arquivo de índice
            stackPush(stack, idRem);
        }

        // atualizando o arquivo de indices
        int popped = 0;
        while(1) {
            popped = stackPop(stack);
            if(popped == -1) {
                break;
            }
            proxRRN = removeFromEntries(entries, &(qtyEnt), popped, proxRRN);
            numRegRem++;
        }
        // destruindo a pilha e criando um novo arquivo de índice
        stackDestroy(stack);
        fseek(id, 0, SEEK_SET);
        fwrite("1", sizeof(char), 1, id);
        fclose(id);

        remove(indexFileName);

        FILE *newId = fopen(indexFileName, "wb");
        writeIndexFile(&newId, entries, qtyEnt, arqType);
        fseek(id, 0, SEEK_SET);
        fwrite("1", sizeof(char), 1, newId);
        fclose(newId);
        free(entries);

        // atualizando o cabeçalho do arquivo de dados com aquilo que foi modificado
        fseek(f, 1, SEEK_SET);
        fwrite(&(topo), sizeof(int), 1, f);
        fseek(f, 178, SEEK_SET);
        fwrite(&(numRegRem), sizeof(int), 1, f);
    }

    // para arquivo de dados tipo2
    if(arqType == 2) {
        //campos de cabeçalho
        long int topo, proxOffset;
        int numRegRem;
        fread(&(topo), sizeof(long int), 1, f);
        fseek(f, 178, SEEK_SET);
        fread(&(proxOffset), sizeof(long int), 1, f);
        fread(&(numRegRem), sizeof(int), 1, f);

        // carregando arquivo de índice na memória
        FILE *id = fopen(indexFileName, "rb+");
        fwrite("0", sizeof(char), 1, id);

        int qtyEnt = 0;
        IDE *entries = readIndexFile2(&id, &qtyEnt);
        qtyEnt = qtyEnt - 2;

        //lista ligada que vai armazenar informações dos registros removidos, exclusividade de arquivos tipo 2
        RList *list = createList();

        // iterando pelos comandos de remoção, os parâmetros passados
        // qtdReg é a quantidade de comandos de remoção recebidos
        for(int i = 0; i < qtdReg; i++) {
            fseek(f, 190, SEEK_SET); // indo para o primeiro registro

            int idRem = -1; // id do registro que será removido

            //verificando se algum dos parâmetros passados foi o ID
            //caso tenha sido, vai salvar no idRem o valor, e fará a remoção sem
            //percorrer o arquivo sequencialmente
            int qtdPar = p[i]->qtdParam;
            for(int j = 0; j < qtdPar; j++) {
                if(strcmp(p[i][j].field, "id") == 0) {
                    long int offsetLer = getLocation(entries, atoi(p[i][j].key), qtyEnt); // pegando offset do registro de tal id
                    if(offsetLer == -1) {
                        idRem = -2; // isso quer dizer que o id não foi encontrado no arquivo de índices, logo não deve existir
                        break;      // no arquivo de dados também
                    }
                    fseek(f, offsetLer, SEEK_SET); // colocando o cursor no início do registro buscado
                    Data record = initializeData();
                    char c = fgetc(f);
                    if(c == '1') { // verificando se ele já foi removido
                        idRem = -2;
                        break;
                    }
                    readReg2(f, &record); // lendo o registro
                    if(removeComp(record, p[i], qtdPar) == 1) { // verificando se ele se encaixa em todos os parâmetros de remoção
                        idRem = atoi(p[i][j].key);
                        fseek(f, offsetLer, SEEK_SET); //voltando no começo do registro
                    } else { idRem = -2; }
                    freeMemReg(&record);
                    break;
                }
            }

            if(idRem == -2) { //registro teve id encontrado mas não corresponde a critérios de busca
                continue;
            }

            if(idRem == -1) { // id não foi passado como parâmetro
                Data record;
                char c;
                while(1) { // percorrendo arquivo de dados sequencialmente
                    long int offsetReg = ftell(f); // offset do início do registro
                    int recBytes = 0;
                    c = fgetc(f);
                    if(c == EOF) break;

                    if(c == '1') { // caso registro seja removido, pula ele
                        fread(&(recBytes), sizeof(int), 1, f);
                        fseek(f, recBytes, SEEK_CUR);
                        continue;
                    }
                    //iniciando e lendo registro
                    record = initializeData();
                    readReg2(f, &record);

                    long int offsetFinal = ftell(f); // offset do fim do registro

                    if(removeComp(record, p[i], qtdPar) == 1) { // caso o registro tenha que ser removido, faz a remoção logica
                        int size = 0;
                        fseek(f, offsetReg, SEEK_SET);
                        fwrite("1", sizeof(char), 1, f);
                        fread(&(size), sizeof(int), 1, f);
                        fwrite(&(topo), sizeof(long int), 1, f);
                        topo = offsetReg;
                        fread(&(idRem), sizeof(int), 1, f);
                        fseek(f, offsetFinal, SEEK_SET);
                        // inserindo na lista ligada as informações do registro removido (id, tamanho e offset)
                        insertNodeList(list, idRem, size, offsetReg);
                    }
                }
                idRem = -1;
                freeMemReg(&record);
                continue; // indo para o próximo registro
            }

            // caso o id tenha sido informado, vai realizar a remoção lógica aqui
            long int removeOffset = ftell(f);
            int size = 0;
            fwrite("1", sizeof(char), 1, f);
            fread(&(size), sizeof(int), 1, f);
            fwrite(&(topo), sizeof(long int), 1, f);
            topo = removeOffset;
            // inserindo na lista ligada o registro que será removido do arquivo de índices
            insertNodeList(list, idRem, size, removeOffset);
        }

        //atualizar arquivo de indices
        long int offset;
        do {
            int idLista = 0;
            offset = removeFirstNode(list, &idLista);
            if(offset != -1) {
                proxOffset = removeFromEntries(entries, &(qtyEnt), idLista, proxOffset);
                numRegRem++;
            }
        } while(offset != -1);
        // destruindo a lista e criando um novo arquivo de índice
        destroyList(list);
        fseek(id, 0, SEEK_SET);
        fwrite("1", sizeof(char), 1, id);
        fclose(id);

        remove(indexFileName);

        FILE *newId = fopen(indexFileName, "wb");
        writeIndexFile(&newId, entries, qtyEnt, arqType);
        fseek(id, 0, SEEK_SET);
        fwrite("1", sizeof(char), 1, newId);
        fclose(newId);
        free(entries);

        // atualizando o cabeçalho do arquivo de dados
        fseek(f, 1, SEEK_SET);
        fwrite(&(topo), sizeof(long int), 1, f);
        fseek(f, 186, SEEK_SET);
        fwrite(&(numRegRem), sizeof(int), 1, f);
    }

    // deixando o arquivo de dados consistente e fechando ele
    fseek(f, 0, SEEK_SET);
    fwrite("1", sizeof(char), 1, f);
    fclose(f);
}