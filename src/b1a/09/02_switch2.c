#include <stdio.h>

int main(int argc, char *argv[])
{
  char ch[100];

  printf("text? ");
  fgets(ch, sizeof ch, stdin);

  int i = 0;
  while (ch[i] != '\0')
  {
    switch (ch[i])
    {
    case ' ':
      printf("\n");
      break;
    case '\n':
      break;
    default:
      printf("%c", ch[i]);
      break;
    }
    i++;
  }

  printf("\n");

  return 0;
}
