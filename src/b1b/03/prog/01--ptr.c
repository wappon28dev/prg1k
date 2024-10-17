#include <stdio.h>

int main(int argc, char *argv[])
{
  char a = 'a';
  char b = 'b';

  int c = 1;
  int d = 2;

  printf("%p\n", &a);
  printf("%p\n", &b);
  printf("%p\n", &c);
  printf("%p\n", &d);

  return 0;
}
