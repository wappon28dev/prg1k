#include <stdio.h>

int main(int argc, char *argv[])
{
  for (int i = 0; i < 10; i++)
  {
    printf("hoge");

    if ((i + 1) % 3 == 0)
    {
      putchar('\n');
    }
  }

  putchar('\n');

  return 0;
}
