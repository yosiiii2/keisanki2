#include <stdio.h>
#include <string.h>

int main() {
  char in[40];
  char *a, *b, *c;

  fgets(in, 40, stdin);
  a = strtok(in, " ,\n");
  b = strtok(NULL, " ,\n");
  c = strtok(NULL, " ,\n");

  printf("1st = %s; 2nd = %s; 3rd = %s\n", a, b, c);

  return 0;
}
