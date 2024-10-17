#include <stdio.h>

int main(int argc, char *argv[])
{
  int a = 10;
  int *px = &a;

  printf("a: %p\n", &a);
  printf("px: %p\n", &px);

  return 0;
}
