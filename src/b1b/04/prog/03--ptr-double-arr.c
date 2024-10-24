#include <stdio.h>
#define LENGTH 3

int main(int argc, char *argv[])
{
  double arr[LENGTH] = {1.0, 2.0, 3.0};

  for (int i = 0; i < LENGTH; i++)
  {
    printf("arr[%i] -> %p\n", i, &arr[i]);
  }

  return 0;
}
