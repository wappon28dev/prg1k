#include <stdio.h>
#define LENGTH 3

int main(int argc, char *argv[])
{
  int a[LENGTH] = {};
  int b[LENGTH] = {};

  for (int i = 0; i < LENGTH; i++)
  {
    printf("a[%d]? ", i);
    scanf("%d", &a[i]);
  }

  for (int i = 0; i < LENGTH; i++)
  {
    printf("b[%d]? ", i);
    scanf("%d", &b[i]);
  }

  for (int i = 0; i < LENGTH; i++)
  {
    printf("a[%d] - b[%d] = %d\n", i, i, a[i] - b[i]);
  }

  return 0;
}
