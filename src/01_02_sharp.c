#include <stdio.h>

int main(int argc, char *argv[])
{
  int SIZE = 5;
  for (int i = 0; i < SIZE * SIZE; i++)
  {
    printf("#");
    if ((i + 1) % SIZE == 0)
    {
      printf("\n");
    }
  }

  return 0;
}
