#include <stdio.h>

void dump_arr(char *name, int arr[], int length)
{
  for (int i = 0; i < length; i++)
  {
    printf("%s[%i] -> %d\n", name, i, arr[i]);
  }
}

void set_map_10x(int arr[], int length)
{
  for (int i = 0; i < length; i++)
  {
    arr[i] = arr[i] * 10;
  }
}

int main(int argc, char *argv[])
{
  int a[] = {10, 20, 30, 40, 50};
  int b[] = {3, 4, 5, 6};

  int a_len = sizeof(a) / sizeof(a[0]);
  int b_len = sizeof(b) / sizeof(b[0]);

  dump_arr("a", a, a_len);
  dump_arr("b", b, b_len);

  set_map_10x(a, a_len);
  set_map_10x(b, b_len);

  puts("--- Mapped 10x ---");
  dump_arr("a", a, a_len);
  dump_arr("b", b, b_len);

  return 0;
}
