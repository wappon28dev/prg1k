#include <stdio.h>

int main(int argc, char *argv[])
{
  for (int n = 1; n <= 100; n++)
  {
    printf("hoge");

    if (n % 2 == 0)
    {
      printf("foo");
    }

    if (n % 3 == 0)
    {
      printf("bar");
    }

    putchar('\n');
  }

  return 0;
}
