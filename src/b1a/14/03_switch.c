#include <stdio.h>

int main(int argc, char *argv[])
{
  int n;

  printf("n? ");
  scanf("%d", &n);

  switch (n)
  {
  case 1:
    puts("AAA");
    break;
  case 2:
    puts("BBB");
    break;
  default:
    puts("Defaultです.");
    break;
  }

  return 0;
}
