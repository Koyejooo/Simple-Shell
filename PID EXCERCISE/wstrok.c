#include <stdio.h>
#include <string.h>

int count_words(char *str) {
    int count = 0;
    char *token = strtok(str, " ");
    while (token != NULL) {
        count++;
        token = strtok(NULL, " ");
    }
    return count;
}

char** split_string(char *str, int *count) {
    *count = count_words(str);
    char **words = (char **) malloc((*count) * sizeof(char *));
    char *token = strtok(str, " ");
    for (int i = 0; i < *count; i++) {
        words[i] = token;
        token = strtok(NULL, " ");
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
    free(words);
    return 0;
}
