#ifndef TRABALHO_1_UTILS_H
#define TRABALHO_1_UTILS_H

typedef struct header_rec{
    char* status; // (1 byte)
    char* description; // (40 bytes)
    char* desC1; // (22 bytes)
    char* desC2; // (19 bytes)
    char* desC3; // (24 bytes)
    char* desC4; // (8 bytes)
    char* codC5; // (1 byte)
    char* desC5; // (16 bytes)
    char* codC6; // (1 byte)
    char* desC6; // (18 bytes)
    char* codC7; // (1 byte)
    char* desC7; // (19 bytes)
    int top1; // para arquivos tipo1
    int nextRRN; // para arquivos tipo1
    long long int top2; // para arquivos tipo2
    long long int nextByteOffset; // para arquivos tipo2
    int numRemRec;
} Header;

typedef struct data_rec {
    int id;
    int year;
    int qtt;
    char* state;
    char* city;
    char* brand;
    char* model;
    char removed[1];
    int next1; // para arquivos tipo1
    long long int next2; // para arquivos tipo2
    int cityLenght;
    int brandLenght;
    int modelLenght;
    int recordLenght; // para arquivos tipo2

} Data;


char* readWord();

long int getByteOffset(int rrn);

long int getRRN(long int byteOffset);

void binarioNaTela(char* nomeArquivoBinario);

char *readQuoted2();

Header allocHeaderRecord(Header* header);

void freeHeaderRecord(Header* header);

void fillHeaderRecord(Header* header);

void initData(Data* data);

void writeBinFile(FILE* pFileBin, Data* data, Header header, char* fileType);


#endif //TRABALHO_1_UTILS_H
