#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/**
 * main - Simple shell program entry point
 *
 * Return: Always 0
 */
int main(void)
{
    char *line = NULL;
    char *token;
    size_t len = 0;
    ssize_t nread;
    int status;
    pid_t pid;
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    char *dir;
    char *command;
    int found = 0;

    while (1)
    {
        printf("$ ");
        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            if (errno == EINVAL)
            {
                perror("Error: ");
            }
            break;
        }
        if (nread == 1)
            continue;
        line[nread - 1] = '\0';
        token = strtok(line, " ");
        command = token;
        while (token)
        {
            token = strtok(NULL, " ");
            if (token)
            {
                char *arg = token;
            }
        }

        while ((dir = strsep(&path_copy, ":")))
        {
            char *fullpath = malloc(strlen(dir) + strlen(command) + 2);
            sprintf(fullpath, "%s/%s", dir, command);
            if (access(fullpath, F_OK) == 0)
            {
                found = 1;
                pid = fork();
                if (pid == -1)
                {
                    perror("Error:");
                }
                if (pid == 0)
                {
                    execve(fullpath, (char *[]){command, NULL}, NULL);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    wait(&status);
                }
                free(fullpath);
                break;
            }
            free(fullpath);
        }

        if (found == 0)
        {
            printf("%s: command not found\n", command);
        }
        found = 0;
    }
    free(path_copy);
    free(line);
    exit(EXIT_SUCCESS);
}
