// Bruno Berndt Lima - 12542550

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "palavras.h"

typedef struct words {
    char word[20];
    int word_occurrence;
} words_t;

int main() {
    words_t *words = NULL;

    char c;
    int words_to_print, words_count = 0, count_different_words = 1;
    int size = 1;
    bool end = false;
    bool first_time = true;
    while (!end) {
        if(words == NULL){
            words = (words_t*) malloc(size * sizeof(words_t));
        }

        c = getchar();
        printf("%c\n", c);

        if (c == EOF) {
            free(words);
            end = true;
        }
        else if (is_alphabetic(c)){
            ungetc(c, stdin);

            scanf(" %s", words[size-1].word);

            words = realloc(words, sizeof(words_t) * (size + 1));

            size++;
            words_count++;

        } else if (c != ' ' && c != '\r' && c != '\n' && c != 32) {

            ungetc(c, stdin);
            scanf(" %d", &words_to_print);

            for (int k = 0; k < words_count; k++) {
                words[k].word_occurrence = 1;
            }
            if(!first_time){
                printf("\n");
            }

            for (int k = 0; k < words_count; k++) {
                for (int l = k + 1; l < words_count; l++) {
                    if (strcmp(words[k].word, words[l].word) == 0 && (strcmp(words[l].word, "0") != 0) &&
                        (strcmp(words[k].word, "0") != 0)) {
                        words[k].word_occurrence++;
                        strcpy(words[l].word, "0");
                        words[l].word_occurrence = 0;
                        //printf("%d - %d - %s - %d\n", k, l, words.word[k], words.word_occurrence[k]);
                    }
                }
            }

            for (int k = 0; k < words_count; k++) {
                if (strcmp(words[k].word, "0") != 0) {
                    count_different_words++;
                }
            }

            int aux;
            char temp[20];
            for (int k = 1; k < words_count; k++) {
                for (int j = 0; j < words_count - k; j++) {
                    if (words[j].word_occurrence < words[j + 1].word_occurrence) {
                        aux = words[j].word_occurrence;
                        words[j].word_occurrence = words[j + 1].word_occurrence;
                        words[j + 1].word_occurrence = aux;

                        strcpy(temp, words[j].word);
                        strcpy(words[j].word, words[j + 1].word);
                        strcpy(words[j + 1].word, temp);
                    }
                }
            }

            for (int k = 0; k < words_count; k++) {
                for (int j = k + 1; j < words_count; j++) {
                    if (words[k].word_occurrence == words[j].word_occurrence) {
                        if (strcmp(words[k].word, words[j].word) > 0) {
                            strcpy(temp, words[k].word);
                            strcpy(words[k].word, words[j].word);
                            strcpy(words[j].word, temp);
                        }
                    }
                }
            }
            int words_printed = 0;
            printf("..%d\n", count_different_words);
            if (words_to_print < count_different_words) {
                for (int k = 0; k < words_to_print; k++) {
                    if ((strcmp(words[k].word, "0") != 0 && words_printed <= count_different_words) && words[k].word_occurrence > 0 ) {
                        printf("%s %d\n", words[k].word, words[k].word_occurrence);

                        words_printed++;
                    } else {
                        words_to_print++;
                    }

                }
            } else {

                words_to_print = count_different_words;

                for (int k = 0; k < words_to_print; k++) {
                    if ((strcmp(words[k].word, "0") != 0 && words_printed <= count_different_words) && words[k].word_occurrence > 0 ) {
                        printf("%s %d\n", words[k].word, words[k].word_occurrence);

                        words_printed++;
                    } else {
                        words_to_print++;
                    }
                }
            }

            first_time = false;
            free(words);
            words = NULL;
            size = 1;
            words_count = 0;
            words_to_print = 0;
            count_different_words = 0;
        }
    }

    return 0;
}
