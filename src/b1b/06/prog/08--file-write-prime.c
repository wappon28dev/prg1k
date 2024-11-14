#include <errno.h>
#include <stdbool.h>
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

bool is_prime(int n)
{
  if (n < 2)
  {
    return false;
  }

  for (int i = 2; i < n; i++)
  {
    if (n % i == 0)
    {
      return false;
    }
  }

  return true;
}

int main(int argc, char *argv[])
{
  const char *file_name = "out/prime.txt";

  FILE *fp = fopen(file_name, "w");

  continue_or_handle_file_error(fp, file_name);

  for (int i = 0; i <= 100; i++)
  {
    if (is_prime(i))
    {
      fprintf(fp, "%d\n", i);
    }
  }

  return 0;
}
