#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_path_dirs() {
    char* path_env = getenv("PATH");
    if (path_env == NULL) {
        printf("PATH environment variable not set.\n");
        return;
    }

    char* path_copy = strdup(path_env); // create a copy of path_env
    char* path_dir = strtok(path_copy, ":"); // get the first directory

    while (path_dir != NULL) {
        printf("%s\n", path_dir);
        path_dir = strtok(NULL, ":"); // get the next directory
    }

    free(path_copy); // free the memory used by the copy
}

int main() {
    print_path_dirs();
    return 0;
}
