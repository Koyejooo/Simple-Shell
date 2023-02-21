#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(void) {
    char buffer[BUFFER_SIZE];
    char *args[2];
    int status;

    while (1) {
        printf("$ ");
        fflush(stdout);

        if (!fgets(buffer, BUFFER_SIZE, stdin)) {
            break;
        }

        args[0] = buffer;
        args[1] = NULL;

        if (buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';
        }

        if (fork() == 0) {
            if (execvp(args[0], args) == -1) {
                perror("Error");
            }
            exit(EXIT_FAILURE);
        } else {
            wait(&status);
        }
    }

    return 0;
}
