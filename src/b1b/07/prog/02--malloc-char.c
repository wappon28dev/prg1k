#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int arr_length = 5;
  char *arr = malloc(sizeof(char) * arr_length);

  strcpy(arr, "hoge");

  for (int i = 0; i < arr_length; i++)
  {
    printf("arr[%i] -> %c\n", i, arr[i]);
  }

  free(arr);

  return 0;
}
