#include <stdio.h>

void printbin(unsigned int x)
{
  if (x < 1)
    return;
  printbin(x >> 1);
  printf("%d", x & 1);
}

int main(int argc, const char *argv[])
{
  unsigned int n;

  printf("n? ");
  scanf("%d", &n);

  printbin(n);
  printf("\n");

  return 0;
}
