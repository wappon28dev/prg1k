#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define LENGTH 1000

int calculate(const char *expression)
{
  int result = 0;
  int num = 0;
  char op = '+';

  for (int i = 0; i < strlen(expression); i++)
  {

    if (expression[i] == ' ')
    {
      continue;
    }

    // whatever it is a number
    if (expression[i] >= '0' && expression[i] <= '9')
    {
      num = num * 10 + expression[i] - '0';
    }
    // if it is a operator
    else
    {
      switch (op)
      {
      case '+':
        result += num;
        break;
      case '-':
        result -= num;
        break;
      }

      num = 0;
      op = expression[i];
    }
  }

  return result;
}

int main(int argc, char *argv[])
{
  char equationStr[LENGTH];

  printf("equation? ");
  fgets(equationStr, sizeof equationStr, stdin);
  printf("%d\n", calculate(equationStr));

  return 0;
}
