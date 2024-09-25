#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define LENGTH 1000

/*
  equation? 100 + 200 - 300
   | [ 0]: 1    preNum: 0    result: 0    needAddOnNext: 1
   | [ 1]: 0    preNum: 1    result: 0    needAddOnNext: 1
   | [ 2]: 0    preNum: 10   result: 0    needAddOnNext: 1
   | [ 3]:      preNum: 100  result: 0    needAddOnNext: 1 ← 確定: 100 を加算！
   | [ 4]: +    preNum: 0    result: 100  needAddOnNext: 1 ← 次の確定時に加算
   | [ 5]:      preNum: 0    result: 100  needAddOnNext: 1 ← 確定: 0 を加算！
   | [ 6]: 2    preNum: 0    result: 100  needAddOnNext: 1
   | [ 7]: 0    preNum: 2    result: 100  needAddOnNext: 1
   | [ 8]: 0    preNum: 20   result: 100  needAddOnNext: 1
   | [ 9]:      preNum: 200  result: 100  needAddOnNext: 1 ← 確定！: 200 を加算！
   | [10]: -    preNum: 0    result: 300  needAddOnNext: 1 ← 次の確定時に減算
   | [11]:      preNum: 0    result: 300  needAddOnNext: 0 ← 確定！: 0 を減算！
   | [12]: 3    preNum: 0    result: 300  needAddOnNext: 0
   | [13]: 0    preNum: 3    result: 300  needAddOnNext: 0
   | [14]: 0    preNum: 30   result: 300  needAddOnNext: 0
   | [15]: \n   preNum: 300  result: 300  needAddOnNext: 0 ← 確定！: 300 を減算！
  answer: 0
*/
int calculate(const char *expression)
{
  int result = 0;
  int preNum = 0;
  bool needAddOnNext = true;

  for (int i = 0; expression[i] != '\0'; i++)
  {
    char ch = expression[i];

    bool isNumeric = ch >= '0' && ch <= '9';
    bool isOperator = ch == '+' || ch == '-';
    bool needFinalize = isOperator || ch == ' ' || ch == '=' || ch == '\n';

    // printf(" | [%2d]: %c\t preNum: %d\t result: %d\t needAddOnNext: %d\n", i, ch, preNum, result, needAddOnNext);

    if (isNumeric)
    {
      // Carry the digit
      preNum *= 10;
      // e.g. ch: '3'
      // -> '3' - '0' = 0x33 - 0x30 = 0x03 = 3
      preNum += ch - '0';
      continue;
    }

    if (isOperator)
    {
      needAddOnNext = ch == '+';
      continue;
    }

    if (needFinalize)
    {
      result += needAddOnNext ? preNum : -1 * preNum;
      preNum = 0;
      continue;
    }

    printf("Invalid character: %c\n", ch);
    exit(1);
  }

  return result;
}

int main(int argc, char *argv[])
{
  char equationStr[LENGTH];

  while (0)
  {
    switch (0)
    {
    default:
      break;
    }
  }

  printf("equation? ");
  fgets(equationStr, sizeof equationStr, stdin);
  printf("answer: %d\n", calculate(equationStr));

  return 0;
}
