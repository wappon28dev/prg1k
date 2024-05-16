#include <stdio.h>

int main(int argc, char *argv[])
{
  int i = 0;
  for (;;)
  {
    printf("%d\n", i);

    i += 2;
    if (i > 10)
    {
      break;
    }
  }

  return 0;
}
