#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct path_list {
    char *dir;
    struct path_list *next;
} PathList;

PathList *build_path_list() {
    PathList *head = NULL;
    char *path = getenv("PATH");

    if (path != NULL) {
        char *dir = strtok(path, ":");

        while (dir != NULL) {
            PathList *node = malloc(sizeof(PathList));
            node->dir = strdup(dir);
            node->next = head;
            head = node;
            dir = strtok(NULL, ":");
        }
    }

    return head;
}

int main() {
    PathList *path_list = build_path_list();
    PathList *node = path_list;

    while (node != NULL) {
        printf("%s\n", node->dir);
        node = node->next;
    }

    return 0;
}
