#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  const char *file_name = "src/b1b/06/prog/out/number.txt";
  FILE *fp = fopen(file_name, "w");

  continue_or_handle_file_error(fp, file_name);

  for (int i = 0; i < 100; i++)
  {
    fprintf(fp, "%d\n", i);
  }

  fclose(fp);
  return 0;
}
