#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern char **environ;

char *_getenv(const char *name) {
    char *env_val = NULL;
    size_t name_len = strlen(name);
    for (char **env = environ; *env != NULL; env++) {
        if (strncmp(name, *env, name_len) == 0 && (*env)[name_len] == '=') {
            env_val = *env + name_len + 1;
            break;
        }
    }
    return env_val;
}

int main() {
    char *home_dir = _getenv("HOME");
    if (home_dir == NULL) {
        printf("Environment variable HOME not found.\n");
    } else {
        printf("HOME=%s\n", home_dir);
    }
    return 0;
}
