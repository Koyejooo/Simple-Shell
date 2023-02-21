#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_MAX_LENGTH 4096
#define PATH_SEPARATOR ":"

int main(int argc, char *argv[]) {
    char *path_env = getenv("PATH");
    char *path = strtok(path_env, PATH_SEPARATOR);
    char file_path[PATH_MAX_LENGTH];

    while (path != NULL) {
        snprintf(file_path, PATH_MAX_LENGTH, "%s/%s", path, argv[1]);
        if (access(file_path, F_OK) != -1) {
            printf("%s\n", file_path);
            break;
        }

        path = strtok(NULL, PATH_SEPARATOR);
    }

    return 0;
}
