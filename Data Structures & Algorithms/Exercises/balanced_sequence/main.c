// Bruno Berndt Lima - 12542550

#include <stdio.h>
#include "stack.h"

//funcao criada para verificar e retornar a partir
// de um char ),],} o seu complemento adequado
char complement_statement(char c) {
    if(c == ')') {
        return '(';
    }
    if(c == ']') {
        return '[';
    }
    if(c == '}') {
        return '{';
    } else {
        return 0;
    }
}

int is_balanced(stack_t *p, char s[]) {
    int count_inverted_commas = 0;
    char temp;

    for (int i = 0; s[i] != '\0'; i++) {
        // se s[i] for um char de "abertura", empilha ele
        if(s[i] == '{' || s[i] == '[' || s[i] == '(') {
            push(p, &s[i]);
        }
        // se o char for um aspas, somente incrementa o contador de aspas
        else if (s[i] == '"') {
            count_inverted_commas++;
        }
        // se s[i] for um char de "fechamento", desempilha um char
        else if (s[i] == '}' || s[i] == ']' || s[i] == ')') {
            temp = s[i];
            pop(p, &temp);
            // se o char desempilhado for diferente do complemento de s[i]
            // entao retorna 0, pois nao esta em ordem correta de abertura e fechamento
            if(temp != complement_statement(s[i])) {
                return 0;
            }
        }
    }
    // se ao final do processo, ainda sobrar algum elemento na pilha
    // retorna 0, pois nao estao em complementaridade
    if(!is_empty(p)) {
        return 0;
    }
    // como as aspas nao se diferenciam em "abertura" ou "fechamento"
    // se o numero de vezes em que aparecem for par, elas estao em complementaridade
    if ((count_inverted_commas % 2) != 0) {
        return 0;
    }

    return 1;
}


int main() {
    stack_t *p;
    char c, sequence[1000];

    while ((c = getchar()) != EOF) {
        ungetc(c, stdin);

        p = create(sizeof(char));

        fgets(sequence, 1000, stdin);    // considerando os espacos entre os caracteres

        if ((is_balanced(p, sequence)) == 0) {
            printf("NÃO BALANCEADO\n");
        } else {
            printf("BALANCEADO\n");
        }

        destroy(p);
    }

    return 0;
}
