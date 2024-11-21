#include <stdio.h>

typedef struct Feature
{
  float length;
  float width;
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
  printf("  Sepal: (%f, %f)\n", iris.sepal.length, iris.sepal.width);
  printf("  Petal: (%f, %f)\n", iris.petal.length, iris.petal.width);
  printf("  Class: %s\n", iris.class);
}

int main(int argc, char *argv[])
{
  Iris iris1 = (Iris){
      .sepal = {6.7, 3.0},
      .petal = {5.2, 2.3},
      .class = "Iris-virginica",
  };
  Iris iris2 = (Iris){
      .sepal = {7.0, 3.2},
      .petal = {4.7, 1.4},
      .class = "Iris-versicolor",
  };

  dump_iris(iris1, "Iris1");
  dump_iris(iris2, "Iris1");

  return 0;
}
