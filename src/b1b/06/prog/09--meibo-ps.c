#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 256

void continue_or_handle_file_error(FILE *fp, const char *file_name)
{
  if (fp == NULL)
  {
    fprintf(stderr, "ファイル (`%s`) を開けませんでした: %s\n", file_name, strerror(errno));
    exit(1);
  }
}

int main(int argc, char *argv[])
{
  const char *file_name = "src/b1b/06/prog/assets/meibo.txt";
  FILE *fp = fopen(file_name, "a+");

  continue_or_handle_file_error(fp, file_name);

  int count = 0;
  char line[LINE_MAX];

  while (true)
  {
    printf("%i\t追記する名前 (Enter で終了) ? ", count + 1);
    fgets(line, LINE_MAX, stdin);

    if (line[0] == '\n')
    {
      break;
    }

    fprintf(fp, "%s", line);

    count++;
  }

  fclose(fp);
  return 0;
}
