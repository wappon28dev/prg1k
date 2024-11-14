#include <errno.h>
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
  const char *file_name = "out/number.txt";
  FILE *fp = fopen(file_name, "a+");

  continue_or_handle_file_error(fp, file_name);

  for (int i = 100; i < 200; i++)
  {
    fprintf(fp, "%d\n", i);
  }

  fclose(fp);
  return 0;
}
