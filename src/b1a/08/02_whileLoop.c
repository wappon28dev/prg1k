#include <stdio.h>

int main(int argc, char *argv[])
{
  int n;

  printf("n? ");
  scanf("%d", &n);

  while (n >= 0)
  {
    printf("%d\n", n);
    n--;
  }

  return 0;
}
