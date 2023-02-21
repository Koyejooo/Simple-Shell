#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_ARGS 10
#define MAX_ARG_LEN 20
#define MAX_PATH_LEN 1024

int parse_command(char *line, char **args);
int execute_command(char **args, char **envp);
void print_environment(char **envp);

int main(int argc, char **argv, char **envp) {
    char line[1024];
    char *args[MAX_ARGS];
    int status;
    int n_args;

    while (1) {
        printf("$ ");
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\n");
            break;
        }

        n_args = parse_command(line, args);
        if (n_args < 1) {
            continue;
        }

        if (strcmp(args[0], "exit") == 0) {
            exit(0);
        } else if (strcmp(args[0], "env") == 0) {
            print_environment(envp);
        } else {
            status = execute_command(args, envp);
            if (status == -1) {
                printf("%s: command not found\n", args[0]);
            }
        }
    }

    return 0;
}

int parse_command(char *line, char **args) {
    int i = 0;
    char *token;

    token = strtok(line, " \n");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " \n");
    }
    args[i] = NULL;

    return i;
}

int execute_command(char **args, char **envp) {
    char path[MAX_PATH_LEN];
    pid_t pid;
    int status;

    if (access(args[0], X_OK) == 0) {
        pid = fork();
        if (pid == 0) {
            execve(args[0], args, envp);
            perror(args[0]);
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("fork");
            return -1;
        } else {
            wait(&status);
            return status;
        }
    } else {
        char *path_var = getenv("PATH");
        char *dir;
        while ((dir = strtok(path_var, ":")) != NULL) {
            path_var = NULL; // for the next call to strtok
            snprintf(path, MAX_PATH_LEN, "%s/%s", dir, args[0]);
            if (access(path, X_OK) == 0) {
                pid = fork();
                if (pid == 0) {
                    execve(path, args, envp);
                    perror(path);
                    exit(EXIT_FAILURE);
                } else if (pid < 0) {
                    perror("fork");
                    return -1;
                } else {
                    wait(&status);
                    return status;
                }
            }
        }
    }

    return -1;
}

void print_environment(char **envp) {
    while (*envp != NULL) {
        printf("%s\n", *envp++);
    }
}
