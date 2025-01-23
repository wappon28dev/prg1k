#include <stdio.h>

int main(int argc, const char *argv[])
{
  const char *file_name = "./cars.csv";
  FILE *fp = fopen(file_name, "r");

  char buf[256];
  while (fgets(buf, sizeof(buf), fp) != NULL)
  {
    printf("%s", buf);
  }

  fclose(fp);

  return 0;
}
