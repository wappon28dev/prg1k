#include <stdio.h>
#include <stdbool.h>

// 制約: `if` 文のみ

int main(int argc, char *argv[])
{
  /// 0 <= dayOfWeek < 7
  /// 0: 日, 1: 月, 2: 火, 3: 水, 4: 木, 5: 金, 6: 土
  int dayOfWeek;

  /// 0 or 1
  /// 0: 09:00 ~ 12:00, 1: 13:00 ~ 16:00
  int timeSlot;

  bool isOpened = false;

  printf("曜日? ");
  scanf("%d", &dayOfWeek);

  printf("時間帯? ");
  scanf("%d", &timeSlot);

  if (timeSlot == 0)
  {
    if (dayOfWeek == 1 || dayOfWeek == 2 || dayOfWeek == 3 || dayOfWeek == 4 || dayOfWeek == 5)
    {
      isOpened = true;
    }
  }

  if (timeSlot == 1)
  {
    if (dayOfWeek == 1 || dayOfWeek == 2 || dayOfWeek == 4 || dayOfWeek == 5 || dayOfWeek == 6)
    {
      isOpened = true;
    }
  }

  printf(isOpened ? "診察を行っています" : "診察は行っていません");
  printf("\n");

  return 0;
}
