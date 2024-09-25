#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
  int wallet = 1000;
  int bank = 1000;

  while (true)
  {
    int amount;
    printf("amount? ");
    scanf("%d", &amount);
    wallet += amount;
    bank -= amount;

    if (amount == 0)
    {
      printf("取引終了\n");
      return 0;
    }

    printf("銀行: %d 財布: %d\n", bank, wallet);

    if (wallet <= 0 || bank <= 0)
    {
      break;
    }
  }

  return 0;
}
