#include <stdio.h>
#define NUM_OF_LOOP 10
#define SPAN_OF_NEWLINE 3

int main(int argc, char *argv[])
{
  for (int i = 0; i < NUM_OF_LOOP; i++)
  {
    printf("hoge");

    if ((i + 1) % SPAN_OF_NEWLINE == 0)
    {
      putchar('\n');
    }
  }

  putchar('\n');

  return 0;
}
