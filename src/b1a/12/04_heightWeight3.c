#include <stdio.h>

int main(int argc, char *argv[])
{
  int human[3][2] = {};

  for (int i = 0; i < 3; i++)
  {
    printf("%d人目の身長と体重? ", i + 1);
    scanf("%d %d", &human[i][0], &human[i][1]);
  }

  for (int i = 0; i < 3; i++)
  {
    printf("%d人目の身長と体重は ", i + 1);
    for (int j = 0; j < 2; j++)
    {
      printf("%d ", human[i][j]);
    }
    puts("");
  }

  return 0;
}
