#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Feature
{
  double length;
  double width;
} Feature;

typedef struct Iris
{
  Feature sepal;
  Feature petal;
  char class[50];
} Iris;

void dump_iris(Iris iris, const char *name)
{
  printf("%s:\n", name);
  printf("  Sepal: (%lf, %lf)\n", iris.sepal.length, iris.sepal.width);
  printf("  Petal: (%lf, %lf)\n", iris.petal.length, iris.petal.width);
  printf("  Class: %s\n", iris.class);
}

Iris parse_str(const char *str)
{
  char buf[256];
  strcpy(buf, str);

  // NOTE: 各行の終端の `\n` で, `iris.class` に `\n` が含まれてしまうので削除
  buf[strlen(buf) - 1] = '\0';

  Iris iris;
  iris.sepal.length = atof(strtok(buf, ","));
  iris.sepal.width = atof(strtok(NULL, ","));
  iris.petal.length = atof(strtok(NULL, ","));
  iris.petal.width = atof(strtok(NULL, ","));
  strcpy(iris.class, strtok(NULL, ","));

  return iris;
}

int main(int argc, char *argv[])
{
  char line[50] = "5.7,2.9,4.2,1.3,Iris-versicolor";
  Iris iris = parse_str(line);

  dump_iris(iris, "Iris");

  return 0;
}
