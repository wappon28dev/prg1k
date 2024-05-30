#include <stdio.h>

int main(int argc, char *argv[])
{
  int n;

  printf("n? ");
  scanf("%d", &n);

  for (int i = n; i >= 1; i--)
  {
    printf("%d\n", i);
  }
  return 0;
}
