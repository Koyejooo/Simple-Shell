#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

// Function to parse the input string and split it into tokens
int parse_input(char *input, char **args) {
    int i = 0;
    args[i] = strtok(input, " \n\t");
    while (args[i] != NULL && i < MAX_ARGS - 1) {
        args[++i] = strtok(NULL, " \n\t");
    }
    return i;
}

int main() {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARGS];
    int status;
    pid_t pid;

    while (1) {
        // Display the prompt
        printf("$ ");

        // Read the input from the user
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            printf("\n");
            break;
        }

        // Parse the input and split it into tokens
        int num_args = parse_input(input, args);

        // Check if the command is exit and exit the shell
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        // Create a child process to execute the command
        pid = fork();
        if (pid == 0) {
            // Child process
            // Look for the command in each directory of the PATH environment variable
            char *path = getenv("PATH");
            char *dir = strtok(path, ":");
            while (dir != NULL) {
                char command[MAX_INPUT_SIZE];
                snprintf(command, MAX_INPUT_SIZE, "%s/%s", dir, args[0]);
                if (access(command, X_OK) == 0) {
                    // Execute the command with the arguments
                    execv(command, args);
                }
                dir = strtok(NULL, ":");
            }

            // If the command is not found, exit the child process with an error
            printf("%s: command not found\n", args[0]);
            exit(1);
        } else {
            // Parent process
            // Wait for the child process to finish
            wait(&status);
        }
    }

    return 0;
}
