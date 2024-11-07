#include <stdio.h>
#include <string.h>

#define LINE_MAX 128

int main(int argc, char *argv[])
{
  const char str[LINE_MAX] = "foo,bar,hoge,fuga";

  char buf[LINE_MAX];
  strcpy(buf, str);

  char *token = strtok(buf, ",");

  while (token != NULL)
  {
    printf("%s\n", token);
    token = strtok(NULL, ",");
  }

  return 0;
}
