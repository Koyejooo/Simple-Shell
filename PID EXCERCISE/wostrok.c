#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_words(char *str) {
    int count = 0;
    int in_word = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {
            in_word = 0;
        } else {
            if (in_word == 0) {
                count++;
                in_word = 1;
            }
        }
    }
    return count;
}

char** split_string(char *str, int *count) {
    *count = count_words(str);
    char **words = (char **) malloc((*count) * sizeof(char *));
    int in_word = 0;
    int len = strlen(str);
    int word_start = 0;
    int word_end = 0;
    int j = 0;
    for (int i = 0; i <= len; i++) {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\0') {
            if (in_word == 1) {
                word_end = i;
                int word_len = word_end - word_start;
                char *word = (char *) malloc((word_len + 1) * sizeof(char));
                memcpy(word, &str[word_start], word_len);
                word[word_len] = '\0';
                words[j] = word;
                j++;
                in_word = 0;
            }
        } else {
            if (in_word == 0) {
                word_start = i;
                in_word = 1;
            }
        }
    }
    return words;
}

int main() {
    char str[] = "Hello world! How are you?";
    int count;
    char **words = split_string(str, &count);
    for (int i = 0; i < count; i++) {
        printf("%s\n", words[i]);
    }
    for (int i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
    return 0;
}
