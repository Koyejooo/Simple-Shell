#include <stdio.h>

extern char **environ;

int main(void) {
    char **env = environ;
    while (*env != NULL) {
        printf("%s\n", *env);
        env++;
    }
    return 0;
}
