#include <stdio.h>
#define LENGTH 5

int main(int argc, char *argv[])
{
  int a[LENGTH] = {};

  for (int i = 0; i < LENGTH; i++)
  {
    a[i] = i + 1;
  }

  int x, y;
  printf("何番目を入れ替えますか? ");
  scanf("%d %d", &x, &y);

  int temp;
  temp = a[x - 1];
  a[x - 1] = a[y - 1];
  a[y - 1] = temp;

  for (int i = 0; i < LENGTH; i++)
  {
    printf("a[%d]=%d\n", i, a[i]);
  }

  return 0;
}
