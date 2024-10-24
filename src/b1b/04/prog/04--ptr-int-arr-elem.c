#include <stdio.h>
#define LENGTH 5

int main(int argc, char *argv[])
{
  int arr[LENGTH] = {1, 2, 3, 4, 5};
  int *p_arr = arr; // NOTE: `&arr[0]` と同じ

  for (int i = 0; i < LENGTH; i++)
  {
    printf("p_arr + %i -> %p\n", i, p_arr + i);
  }

  for (int i = 0; i < LENGTH; i++)
  {
    printf("arr[%i] -> %p\n", i, &arr[i]);
  }

  return 0;
}
