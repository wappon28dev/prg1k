#include <stdio.h>

int main(int argc, char *argv[])
{
  int human[3][2] = {
      {170, 80},
      {160, 50},
      {180, 70},
  };

  for (int i = 0; i < 3; i++)
  {
    printf("%d人目の身長と体重は %d %d\n", i + 1, human[i][0], human[i][1]);
  }

  return 0;
}
