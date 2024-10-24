#include <stdio.h>
#define LENGTH 3

int main(int argc, char *argv[])
{
  int arr[LENGTH] = {1, 2, 3};

  for (int i = 0; i < LENGTH; i++)
  {
    printf("arr[%i] -> %p\n", i, &arr[i]);
  }

  return 0;
}
