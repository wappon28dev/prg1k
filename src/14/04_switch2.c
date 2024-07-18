#include <stdio.h>

int main(int argc, char *argv[])
{
  char c;

  printf("c? ");
  scanf("%c", &c);

  switch (c)
  {
  case 'L':
    puts("Left");
    break;
  case 'R':
    puts("Right");
    break;
  default:
    puts("nop");
    break;
  }

  return 0;
}
