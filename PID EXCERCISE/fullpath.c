#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LENGTH 1024

int main() {
    char cmd[MAX_CMD_LENGTH];
    pid_t pid;

    while (1) {
        printf("$ ");
        fgets(cmd, MAX_CMD_LENGTH, stdin);
        cmd[strcspn(cmd, "\n")] = '\0';

        pid = fork();

        if (pid == -1) {
            printf("fork failed\n");
            exit(1);
        } else if (pid == 0) {
            if (execl(cmd, cmd, (char *)0) == -1) {
                printf("error: command not found\n");
                exit(1);
            }
        } else {
            waitpid(pid, NULL, 0);
        }
    }

    return 0;
}
