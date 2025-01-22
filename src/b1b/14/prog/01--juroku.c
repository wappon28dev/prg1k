#include <stdio.h>

void print16(unsigned int x)
{
  switch (x)
  {
  case 10:
    printf("A");
    break;
  case 11:
    printf("B");
    break;
  case 12:
    printf("C");
    break;
  case 13:
    printf("D");
    break;
  case 14:
    printf("E");
    break;
  case 15:
    printf("F");
    break;
  default:
    printf("%d", x);
  }
}

int main(int argc, const char *argv[])
{
  unsigned int n;

  printf("n? ");
  scanf("%d", &n);

  print16(n / 16);
  print16(n % 16);

  printf("\n");

  return 0;
}
