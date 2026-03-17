#include <stdio.h>

float soma(float numero1, float numero2);
float subtrai(float numero1, float numero2);
float multiplica(float n1, float n2);
void divide(float n1, float n2);

//função principal
int main(){
	float numero1, numero2, resultado;
	char op=' ';
	
	while(op != '$'){
		printf("Digite a operacao: ");
		scanf(" %c", &op);
		if (op == '$')
			break;
	
		printf("Digite o primeiro numero: ");
		scanf("%f", &numero1);
		printf("Digite o segundo numero: ");
		scanf("%f", &numero2);
		
		switch(op){
			case '+': resultado = soma(numero1, numero2);
					  printf("Resultado:  %f\n\n", resultado);
					  break;
			case '-': resultado = subtrai(numero1, numero2);
					  printf("Resultado:  %f\n\n", resultado);
					  break;
			case '*': resultado = multiplica(numero1, numero2);
					  printf("Resultado:  %f\n\n", resultado);
					  break;
			case '/': divide(numero1, numero2);
					  break;
			default: printf("Operacao invalida\n\n");
					  break;
		}
	}
	
	return 0;
}

//funções desenvolvidas
float soma(float numero1, float numero2){
	float resultado = numero1 + numero2;
	return resultado;
}

float subtrai(float numero1, float numero2){
	return numero1 - numero2;
}

float multiplica(float n1, float n2){
	return n1 * n2;
}

void divide(float n1, float n2){
	if (n2 != 0)
		printf("Resultado: %f\n\n", n1/n2);
	else
		printf("Erro: divisao por zero\n\n");
}
