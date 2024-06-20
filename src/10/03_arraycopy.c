#include <stdio.h>
#define LENGTH 5

int main(int argc, char *argv[])
{
  int heightsCm[LENGTH] = {};

  for (int i = 0; i < LENGTH; i++)
  {
    printf("%d人目の身長(cm)? ", i + 1);
    scanf("%d", &heightsCm[i]);
  }

  puts("--- Convert Meter ---");

  double heightsMeter[LENGTH] = {};
  for (int i = 0; i < LENGTH; i++)
  {
    heightsMeter[i] = heightsCm[i] / 100.0;
  }

  for (int i = 0; i < LENGTH; i++)
  {
    printf("%d人目の身長: %lf m\n", i + 1, heightsMeter[i]);
  }

  return 0;
}
