#include <stdio.h>
#include <stdlib.h>

/*Conteúdo: 
	- Alocação dinâmica e Memória Heap...
	- malloc()
	- free()
*/

void preencherMatrizStack(int linhas, int colunas, int matriz[][colunas]){
	int i, j;
	for(i=0;i<linhas;i++)
		for(j=0;j<colunas;j++)
			matriz[i][j] = i*j;
}

void imprimirMatrizStack(int linhas, int colunas, int matriz[][colunas]){
	int i, j;
	for(i=0;i<linhas;i++){
		for(j=0;j<colunas;j++)
			printf("%i ", matriz[i][j]);
		printf("\n");
	}
}

int somaMatrizStack(int linhas, int colunas, int matriz[][colunas]){
	int i, j, soma=0;
	for(i=0;i<linhas;i++)
		for(j=0;j<colunas;j++)
			soma = soma + matriz[i][j];
	return soma;
}

void preencherMatrizHeap(int linhas, int colunas, int **matriz);
void imprimirMatrizHeap(int linhas, int colunas, int **matriz);
int somaMatrizHeap(int linhas, int colunas, int **matriz);

int main(){
	int i, j;
	
	int linhas = 4;
	int colunas = 7;
	int matrizStack[linhas][colunas];
	
	printf("Alocacao na Memoria Stack\n");
	preencherMatrizStack(linhas, colunas, matrizStack);
	imprimirMatrizStack(linhas, colunas, matrizStack);
	printf("Soma dos valores da matriz: %i\n", somaMatrizStack(linhas, colunas, matrizStack));
	printf("***********************************\n");
	
	//criando uma variavel inteira na memoria heap
	printf("\nAlocacao na Memoria Heap com dados comuns\n");
	int *numero = malloc(sizeof(int));
	printf("Endereco na Memoria Heap: %p\n", numero);
	
	printf("Valor antes da atribuicao: %i\n", *numero);
	*numero = 111;
	printf("Valor apos atribuicao: %i\n", *numero);
	
	if (numero == NULL)//podemos verificar se teremos memoria suficiente para alocar
		printf("Memoria insuficiente");
		
	printf("Desalocar o dado comum na Memoria Heap\n");
	free(numero);
	printf("***********************************\n");
	
	//construindo um vetor de 4 posições de inteiros na memoria heap
	printf("\nAlocacao na Memoria Heap com vetor\n");
	int *vetorHeap = (int *)malloc(4 * sizeof(int));
	printf("Endereco na Memoria Heap: %p\n", vetorHeap);
	
	printf("Vetor sem atribuicao: ");
	for(i=0;i<4;i++)
		printf("%i ", *(vetorHeap+i));
	
	printf("\nVetor apos atribuicao: ");
	*vetorHeap = 10;
	*(vetorHeap+3) = 20;
	vetorHeap[2] = -9;
	for(i=0;i<4;i++)
		printf("%i ", *(vetorHeap+i)); //ou printf("%i ", vetorHeap[i]);
	printf("\n");
	
	printf("Desalocar o vetor na Memoria Heap\n");
	free(vetorHeap);
	printf("***********************************\n");
	
	//construindo uma matriz[2][3] de inteiros
	printf("\nAlocacao na Memoria Heap com matriz\n");
	int **matrizHeap = malloc(2 * sizeof(void *)); //quantidade de vetores
	for (j=0; j<3; j++)
		matrizHeap[j] = malloc(3 * sizeof(int)); //definindo o tamanho do vetor
	printf("Endereco na Memoria Heap: %p\n", matrizHeap);
	
	printf("Matriz sem atribuicao:\n");
	for(i=0;i<2;i++){
		for(j=0;j<3;j++)
			printf("%i ", matrizHeap[i][j]);
		printf("\n");
	}
	
	printf("Matriz apos atribuicao:\n");
	matrizHeap[1][0] = -89; //coordenada (1,0)
	*(matrizHeap[1]+1) = 7; //coordenada (1,1)
	*(matrizHeap[0]+2) = -30; //coordenada (0,2)
	
	for(i=0;i<2;i++){
		for(j=0;j<3;j++)
			printf("%i ", matrizHeap[i][j]);//ou printf("%i ", *(matrizHeap[i]+j));
		printf("\n");
	}
	
	printf("Desalocar a matriz na Memoria Heap\n");
	for (j=0; j<3; j++)
		free(matrizHeap[j]);//desaloca as linhas
	free(matrizHeap);//desaloca o todo
	printf("***********************************\n");
	
	printf("\nUtilizando as funcoes heap para a matriz heap\n");
	int **matrizHeapHeap = malloc(4 * sizeof(int *));
	for (j=0; j<3; j++)
		matrizHeapHeap[j] = malloc(3 * sizeof(int));
		
	preencherMatrizHeap(4, 3, matrizHeapHeap);
	imprimirMatrizHeap(4, 3, matrizHeapHeap);
	printf("Soma dos valores da matriz: %i\n", somaMatrizHeap(4, 3, matrizHeapHeap));
	
	printf("Desalocar a matriz na Memoria Heap\n");
	free(matrizHeapHeap);//desaloca o todo
	printf("***********************************\n");
	
	return 0;
}

void preencherMatrizHeap(int linhas, int colunas, int **matriz){
	int i, j;
	for(i=0;i<linhas;i++)
		for(j=0;j<colunas;j++)
			*((*matriz)+linhas*i+j) = i*j;
}

void imprimirMatrizHeap(int linhas, int colunas, int **matriz){
	int i, j;
	for(i=0;i<linhas;i++){
		for(j=0;j<colunas;j++)
			printf("%i ", *((*matriz)+linhas*i+j));
		printf("\n");
	}
}

int somaMatrizHeap(int linhas, int colunas, int **matriz){
	int i, j, soma=0;
	for(i=0;i<linhas;i++)
		for(j=0;j<colunas;j++)
			soma = soma + *((*matriz)+linhas*i+j);
	return soma;
}
