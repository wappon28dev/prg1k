#include <stdio.h>
#define DIGITS 3

int main(int argc, char *argv[])
{
  int x;

  printf("x? ");
  scanf("%d", &x);

  // 3-digit zero padding
  char *pad;
  sprintf(pad, "%0*d", DIGITS, x);

  for (int i = DIGITS; i > 0; i--)
  {
    printf("%c", pad[i - 1]);
  }
  printf("\n");

  return 0;
}
