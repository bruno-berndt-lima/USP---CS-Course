#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define direct_palindrome_condition (phrase[letter_index] == phrase[phrase_size - letter_index - 1])

/*  verificacao de palindromo indireto :
 * (se em uma posicao X existe um espaco(ou uma barra) E a posicao Y (tamanho da frase/palavra menos indice de X menos 1 (pois comeca do indice zero))
 * correspondente para ser palindromo for diferente de um espaco(ou uma barra)) E (o caractere da posicao [X + 1] for igual ao
 * caractere da posicao Y) entao eh um palindromo indireto. O mesmo vale se o espaco ou a barra estiver na posicao Y correspondente.
 * Por exemplo:         10/01/1001  Tamanho da string : 10 (0 -> 9)
 *                        ^    ^    Indice 2 = '/' e Indice 9 - 2 = 0
 *                        caractere no Indice 2 + 1 = 0 que eh igual ao caractere no Indice 9.
 *                        fazendo as verificacoes seguintes conclui-se que eh palindromo indireto.
 */
#define indirect_palindrome_condition  (((phrase[letter_index] == ' ' && phrase[phrase_size - letter_index - 1] != ' ') \
                                            && (phrase[letter_index + 1] == phrase[phrase_size - letter_index - 1])) \
                                            || ((phrase[letter_index] == '/' && phrase[phrase_size - letter_index - 1] != '/') \
                                            && (phrase[letter_index + 1] == phrase[phrase_size - letter_index - 1])) \
                                            || ((phrase[phrase_size - letter_index - 1] == ' ' && phrase[letter_index] != ' ') \
                                            && (phrase[phrase_size - letter_index - 2] == phrase[letter_index])) \
                                            || ((phrase[phrase_size - letter_index - 1] == '/' && phrase[letter_index] != '/') \
                                            && (phrase[phrase_size - letter_index - 2] == phrase[letter_index])))


int recursive_palindrome_check (char *phrase, int letter_index) {
    int phrase_size = strlen(phrase);

    if (letter_index <= phrase_size) {
        if (direct_palindrome_condition) {
            return recursive_palindrome_check(phrase, letter_index + 1);
        }
        else if (indirect_palindrome_condition) {
            recursive_palindrome_check(phrase, letter_index + 1);
            return -1;
        }
        else {
            return 0;
        }
    }
    else {
        return 1;
    }
}

char *read_line (int *size_variable) {
    char *str = NULL;
    int counter = 0;
    char c;

    do {
        c = getchar();
        if (c == ' ' || c == '/' || isalnum(c)) {
            c = tolower(c);
            str = realloc(str, sizeof(char) * (counter + 1));
            str[counter++] = c;
        }
        else {
            continue;
        }

    } while (c != '\n' && c != EOF);

    str[counter] = '\0';
    *size_variable = counter;

    return str;
}

int main() {
    int size;
    char *message;

    message = read_line(&size);

    int palindrome = recursive_palindrome_check(message, 0);

    if (palindrome == 1) {
        printf("Palindromo direto\n");
    }
    else if (palindrome == -1) {
        printf("Palindromo indireto\n");
    }
    else if (palindrome == 0) {
        printf("Nao eh um palindromo\n");
    }

    free(message);

    return 0;
}
