#include <stdio.h>

int main(int argc, char *argv[])
{
  int a, b;

  printf("a? ");
  scanf("%d", &a);
  printf("b? ");
  scanf("%d", &b);

  if (a == 0)
  {
    printf("aは0です\n");
    return 0;
  }

  printf(a >= b ? "a は b 以上です" : "a は b 未満です");
  printf("\n");

  return 0;
}
