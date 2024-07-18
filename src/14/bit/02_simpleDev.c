#include <math.h>
#include <stdbool.h>
#include <stdio.h>

void devB(bool a, bool b, bool c)
{
  printf("%s", a || c ? "GO\n" : "NO\n");
}

int main(int argc, char *argv[])
{
  for (int i = 0; i < pow(2, 3); i++)
  {
    devB(i & 0b100, i & 0b010, i & 0b001);
  }
  return 0;
}
