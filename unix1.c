#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 10 // maximum number of arguments
#define MAX_ARG_LEN 20 // maximum length of an argument
#define MAX_INPUT_LEN (MAX_ARGS * MAX_ARG_LEN + 1) // maximum length of the input

int main(void) {
    char input[MAX_INPUT_LEN];
    char* args[MAX_ARGS + 1]; // array of arguments, plus a NULL pointer
    int status;

    while (1) {
        printf("$ ");
        if (fgets(input, MAX_INPUT_LEN, stdin) == NULL) {
            printf("\n");
            break; // end of file
        }
        input[strlen(input) - 1] = '\0'; // remove the newline character

        int i = 0;
        char* token = strtok(input, " ");
        while (token != NULL && i < MAX_ARGS) {
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL; // terminate the array of arguments with a NULL pointer

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            // child process
            if (execvp(args[0], args) == -1) {
                perror("execvp");
                exit(1);
            }
        } else {
            // parent process
            if (wait(&status) == -1) {
                perror("wait");
                exit(1);
            }
        }
    }

    return 0;
}
