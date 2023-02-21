#include <stdio.h>

int main() {
  char command[100];

  printf("$ ");
  fgets(command, sizeof(command), stdin);
  printf("%s", command);

  return 0;
}