#include <stdio.h>

void printFunc()
{
  for (int i = 1; i <= 5; i++)
  {
    printf("%d\n", i);
  }
}

int main(int argc, char *argv[])
{
  printFunc();
  return 0;
}
