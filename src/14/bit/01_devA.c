#include <stdbool.h>
#include <stdio.h>

void devA(bool a, bool b, bool c)
{
  if (a || (!a && b && c) || (!b && c))
  {
    printf("GO\n");
    return;
  }

  printf("NO\n");
}

int main(int argc, char *argv[])
{

  devA(0, 0, 0);
  devA(0, 0, 1);
  devA(0, 1, 0);
  devA(0, 1, 1);
  devA(1, 0, 0);
  devA(1, 0, 1);
  devA(1, 1, 0);
  devA(1, 1, 1);

  return 0;
}
