#include <stdio.h>
#define NUM_OF_LOOP 100
#define SPAN_OF_FOO 2
#define SPAN_OF_BAR 3

int main(int argc, char *argv[])
{
  for (int n = 1; n <= NUM_OF_LOOP; n++)
  {
    printf("hoge");

    if (n % SPAN_OF_FOO == 0)
    {
      printf("foo");
    }

    if (n % SPAN_OF_BAR == 0)
    {
      printf("bar");
    }

    putchar('\n');
  }

  return 0;
}
