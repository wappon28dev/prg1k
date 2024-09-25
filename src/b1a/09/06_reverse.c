#include <stdio.h>
#define LENGTH 5

int main(int argc, char *argv[])
{
  int input[LENGTH] = {};

  for (int i = 0; i < LENGTH; i++)
  {
    printf("input[%d]? ", i);
    scanf("%d", &input[i]);
  }

  printf("---reverse---\n");

  for (int i = LENGTH - 1; i >= 0; i--)
  {
    printf("input[%d]: %d\n", i, input[i]);
  }

  return 0;
}
