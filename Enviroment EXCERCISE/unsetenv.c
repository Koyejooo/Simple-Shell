#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

int _unsetenv(const char *name) {
    int i, j, found = 0;
    size_t namelen = strlen(name);

    // Look for the variable in the environment
    for (i = 0; environ[i] != NULL; i++) {
        if (strncmp(name, environ[i], namelen) == 0 && environ[i][namelen] == '=') {
            found = 1;
            break;
        }
    }

    // If the variable was found, remove it from the environment
    if (found) {
        // Shift all the environment variables down one position
        for (j = i; environ[j] != NULL; j++) {
            environ[j] = environ[j + 1];
        }
    } else {
        return -1;
    }

    return 0;
}
