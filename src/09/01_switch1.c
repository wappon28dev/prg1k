#include <stdio.h>

int main(int argc, char *argv[])
{
  int n;

  printf("n? ");
  scanf("%d", &n);

  switch (n)
  {
  case 1:
    printf("AAA");
    break;
  case 2:
    printf("BBB");
    break;
  default:
    printf("Defaultです.");
    break;
  }

  printf("\n");

  return 0;
}
