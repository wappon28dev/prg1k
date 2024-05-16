#include <stdio.h>

int main(int argc, char *argv[])
{
  int n;

  printf("人数? ");
  scanf("%d", &n);

  double sum = 0;
  for (int i = 0; i < n; i++)
  {
    int height;
    printf("%d人目の身長は? ", i + 1);
    scanf("%d", &height);

    sum += height;
  }

  printf("平均身長: %lf\n", sum / n);

  return 0;
}
