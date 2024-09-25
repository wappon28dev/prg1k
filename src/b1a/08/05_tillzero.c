#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
  int wallet = 1000;

  while (true)
  {
    int amount;
    printf("amount? ");
    scanf("%d", &amount);
    wallet -= amount;

    printf("残高: %d\n", wallet);

    if (wallet <= 0)
    {
      break;
    }
  }

  return 0;
}
