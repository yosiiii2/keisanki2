#include<stdio.h>
#include <stdlib.h>

void swap(int *i, int *j) {
  int temp = *i;
  *i = *j;
  *j = temp;
}

void f() {
  int a = 123;
  int *b = (int *) malloc(sizeof(int));
  int *c = NULL;

  *b = 456;

  swap(&a, b);
  printf("a = %d, b = %d\n", a, *b);

  swap(&a, c);
  printf("a = %d, c = %d\n", a, *c);
}

int main() {
  f();
  return 0;
}
