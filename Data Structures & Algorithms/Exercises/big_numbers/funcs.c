#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

typedef struct node node_t;

struct node {
    elem info;
    node_t *prev, *next;
};

struct list {
    node_t *beginning, *end;
};

// funcao que fara as leitura dos numeros
int *read_number (int *size) {
    // cria um vetor de int
    int *vet = NULL;

    char c;
    int tmp = 0;
    int counter = 0;
    int is_negative = 0;

    do {
        c = getchar();

        // se ler o caractere "menos" o numero eh negativo
        if (c == '-') {
            is_negative = 1;
            continue;
        }
        // se ler o '\r' ignora
        if (c == '\r') {
            continue;
        }
        // se ler zeros a esquerda e tmp for igual a 0
        // ele ignora os zeros a esquerda
        if (c == '0' && tmp != 1) {
            continue;
        } else {
            tmp = 1;
        }
        vet = realloc(vet, sizeof (int) * (counter + 1));
        vet[counter++] = c - '0';
        // se leu um caractere "menos" la em cima,
        // entao seta o valor apos ele como negativo
        if (is_negative) {
            vet[counter - 1] = -vet[counter - 1];
            is_negative = 0;
        }
    } while (c != ' ' && c != EOF && c != '\n');

    // se leu somente um espaco ou quebra de linha
    // poe o valor 0 no lugar
    if (counter == 1) { // \n ou ' '
        vet[0] = 0;
        counter++;
    }
    // variavel de controle do tamanho do numero
    *size = counter - 1;

    return vet;
}

void free_all(list_t *l_result, list_t *l1, list_t *l2) {
    free_list(l1);
    free_list(l2);
    free_list(l_result);
}

list_t *sum (list_t *l1, list_t *l2) {
    list_t *l_result = create();
    node_t *p1 = l1->beginning;
    node_t *p2 = l2->beginning;

    // variavel que guardara o "vai um" quando a soma extrapola 10
    int aux = 0;
    // enquanto um dos dois ponteiros forem diferentes de nulo
    while (p1 != NULL || p2 != NULL) {
        // se p1 e p2 sao diferentes de nulos
        if (p1 != NULL && p2 != NULL) {
            // e se o o valor de p1 e p2 mais o "sobe um" for maior ou igual a 10
            if ((p1->info + p2->info + aux) >= 10) {
                // insiro o resto do valor dividido por 10
                insert_elem(l_result, ((p1->info + p2->info + aux) % 10));
                // e calculo o valor para somar ao proximo algarismo
                aux = (int) (p1->info + p2->info + aux) / 10;

            } else { // se o valor for menor que 10, eh soh inseri-lo direto na lista
                insert_elem(l_result, p1->info + p2->info + aux);
                aux = 0;
            }
            p1 = p1->next;
            p2 = p2->next;
        } else if (p1 != NULL) { // se p1 nao for nulo e p2 for
            // faz o mesmo procedimento do if acima
            if ((p1->info + aux) >= 10) {
                insert_elem(l_result, ((p1->info + aux) % 10));
                aux = (int) (p1->info + aux) / 10;
            } else {
                insert_elem(l_result, p1->info + aux);
                aux = 0;
            }
            p1 = p1->next;
        } else { // mesma coisa para caso p1 seja nulo e p2 nao
            if ((p2->info + aux) >= 10) {
                insert_elem(l_result, ((p2->info + aux) % 10));
                aux = (int) (p2->info + aux) / 10;
            } else {
                insert_elem(l_result, p2->info + aux);
                aux = 0;
            }
            p2 = p2->next;
        }
    }
    // se apos todas a operacoes ainda restar alguma valor no aux
    // insere esse valor na lista
    if (aux > 0) {
        insert_elem(l_result, aux);
    }

    return l_result;
}

int is_bigger(list_t *l1, list_t *l2, int n1_size, int n2_size) {
    node_t *p1 = l1->beginning;
    node_t *p2 = l2->beginning;

    // avanca p1 ate chegar a ultima posicao
    while (p1->next != NULL) {
        p1 = p1->next;
    }
    // avanca p2 ate chegar a ultima posicao
    while (p2->next != NULL) {
        p2 = p2->next;
    }
    // se o dois valores na ultima posicao forem positivos
    if (p1->info >= 0 && p2->info >= 0) {
        // se o tamanho do numero 1 for maior que o numero 2
        // entao p1.info eh maior que p2.info
        if (n1_size > n2_size) {
            return 1;
            // caso contrario eh menor
        } else if (n1_size < n2_size){
            return 0;
            // se o tamanho dos numeros forem iguais
        } else if (n1_size == n2_size) {
            // enquanto p1.info e p2.info forem iguais
            while (p1->info == p2->info && p1->prev != NULL && p2->prev != NULL) {
                // vai retrocendo os valores ate encontrar um em que sejam diferentes
                // ou nulo
                p1 = p1->prev;
                p2 = p2->prev;
            }
            if (p1->info > p2->info) {
                return 1;
            } else {
                return 0;
            }
        }
        // no caso que em p1.info e p2.info sao negativos
        // faz a mesmas verificacoes acima apenas com
        // algumas mudancas
    } else if (p1->info < 0 && p2->info < 0) {
        if (n1_size > n2_size) {
            return 0;
        } else if (n1_size < n2_size){
            return 1;
        } else if (n1_size == n2_size) {
            while (p1->info == p2->info && p1->prev != NULL && p2->prev != NULL) {
                p1 = p1->prev;
                p2 = p2->prev;
            }
            if (p1->info < p2->info) {
                return 1;
            } else {
                return 0;
            }
        }
    } else if (p1->info >= 0 && p2->info < 0) {
        return 1;
    } else if (p1->info < 0 && p2->info >= 0) {
        return 0;
    }
    return -1;
}

int is_smaller(list_t *l1, list_t *l2, int n1_size, int n2_size) {
    node_t *p1 = l1->beginning;
    node_t *p2 = l2->beginning;

    // funcao identica a is_bigger somente com poucas mudancas
    if (p1 != NULL) {
        while (p1->next != NULL) {
            p1 = p1->next;
        }
    }
    if (p2 != NULL) {
        while (p2->next != NULL) {
            p2 = p2->next;
        }
    }

    if (p1->info >= 0 && p2->info >= 0) {
        if (n1_size > n2_size) {
            return 0;
        } else if (n1_size < n2_size){
            return 1;
        } else if (n1_size == n2_size) {
            while (p1->info == p2->info && p1->prev != NULL && p2->prev != NULL) {
                p1 = p1->prev;
                p2 = p2->prev;
            }
            if (p1->info < p2->info) {
                return 1;
            } else {
                return 0;
            }
        }
    } else if (p1->info < 0 && p2->info < 0) {
        if (n1_size > n2_size) {
            return 1;
        } else if (n1_size < n2_size){
            return 0;
        } else if (n1_size == n2_size) {
            while (p1->info == p2->info && p1->prev != NULL && p2->prev != NULL) {
                p1 = p1->prev;
                p2 = p2->prev;
            }
            if (p1->info > p2->info) {
                return 1;
            } else {
                return 0;
            }
        }
    } else if (p1->info >= 0 && p2->info < 0) {
        return 0;
    } else if (p1->info < 0 && p2->info >= 0) {
        return 1;
    }
    return -1;
}

int is_equal (list_t *l1, list_t *l2, int n1_size, int n2_size) {
    node_t *p1 = l1->beginning;
    node_t *p2 = l2->beginning;

    // se o tamanho dos numeros forem diferentes
    // entao os numeros sao diferentes
    if (n1_size != n2_size) {
        return 0;
    }

    // se nao, enquanto forem diferentes de nulo
    // vai avancando e comparando os valores de
    // p1.info e p2.info
    while (p1 != NULL || p2 != NULL) {
        if (p1->info == p2->info) {
            p1 = p1->next;
            p2 = p2->next;
        } else {
            return 0;
        }
    }
    return 1;
}
