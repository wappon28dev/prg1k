#include <stdio.h>
#define LENGTH 100

int main(int argc, char *argv[])
{
  int array[] = {};
  for (int i = 0; i < LENGTH; i++)
  {
    array[i] = i;
  }

  for (int i = 0; i < LENGTH; i++)
  {
    printf("array[%d]: %d\n", i, array[i]);
  }

  return 0;
}
