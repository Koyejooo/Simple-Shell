#include <stdlib.h>
#include <string.h>

int _setenv(const char *name, const char *value, int overwrite) {
    int len, i;
    char **envp = environ;

    if (name == NULL || value == NULL) {
        return -1;
    }

    len = strlen(name);

    for (i = 0; envp[i] != NULL; i++) {
        if (strncmp(envp[i], name, len) == 0 && envp[i][len] == '=') {
            if (!overwrite) {
                return 0;
            }
            else {
                break;
            }
        }
    }

    char *env_var = (char *) malloc(len + strlen(value) + 2);
    sprintf(env_var, "%s=%s", name, value);

    if (envp[i] == NULL) {
        envp[i + 1] = NULL;
    }

    envp[i] = env_var;

    return 0;
}
