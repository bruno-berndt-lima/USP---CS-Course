#ifndef TRABALHO_3_BTREE_H
#define TRABALHO_3_BTREE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"utils.h"
#include"search.h"
#include"btree.h"

typedef struct node2 {
    long int offsetNo;
    int rrnNo;
    char tipo;
    int numChaves;
    int chaves[4];
    long int conteudo[4];
    int ponteiros[5];
} no2;

void ler_e_imprimir();
int getByteOffset1(int rrn);
int getRRN1(long int byteOffset);
FILE *createBT(char *name, int arqType);
void searchRegBTree(int funcType, int arqType, char *indexFileName, FILE *f, FILE *fp);
void split(int insert_key, long int insert_conteudo, int *insert_rrn_dir, no2 *no, int *promo_key, long int *promo_conteudo, int *promo_r_child, int *promo_l_child, no2 *newPage, int *prox, int arqType);
int inserirNo(FILE *f, no2 *no, int cur_rrn, int key, long int conteudo, int *promo_key, long int *promo_conteudo, int *promo_r_child, int *promo_l_child, int *prox, int arqType);
void driver_alg(FILE *f, int *raiz, int *prox, int *numNos, int key, long int conteudo, int arqType);
void searchById(FILE *f, int arqTypeInt, char *outputFile, int id);
void lerArquivoIndice(FILE *f, int arqType);

#endif