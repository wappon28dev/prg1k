#include <stdio.h>

int main(int argc, char *argv[])
{
  int n;

  printf("n? ");
  scanf("%d", &n);

  for (int i = 0; i < n; i++)
  {
    printf("Hello, World!\n");
  }

  return 0;
}
