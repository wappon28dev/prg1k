#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define LENGTH 20

int main(int argc, char *argv[])
{
  char input[LENGTH + 1] = {'\0'};

  printf("input(20文字以下): ");
  scanf("%s", input);

  char palindrome[LENGTH + 1] = {'\0'};
  int len = strlen(input);

  for (int i = 0; i < len; i++)
  {
    palindrome[i] = input[len - i - 1];
  }

  bool isPalindrome = strcmp(input, palindrome) == 0;
  printf("回文%s\n", isPalindrome ? "OK" : "NG");

  return 0;
}
