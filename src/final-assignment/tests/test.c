#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

int add(int a, int b)
{
  return a - b;
}

int main()
{
  assert(add(1, 2) == 3);
}
