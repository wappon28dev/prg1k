#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 256
#define LINES_MAX 150

/// Error Handlers ///

void continue_or_handle_malloc_error(const void *ptr)
{
  if (ptr == NULL)
  {
    fprintf(stderr, "メモリの確保に失敗しました: %s\n", strerror(errno));
    exit(1);
  }
}

void continue_or_handle_file_error(const FILE *fp, const char *file_name)
{
  if (fp == NULL)
  {
    fprintf(stderr, "ファイル (`%s`) を開けませんでした: %s\n", file_name, strerror(errno));
    exit(1);
  }
}

/// Helpers ///

char *allocate_and_copy_string(const char *src)
{
  char *dest = malloc(strlen(src) + 1);
  continue_or_handle_malloc_error(dest);
  strcpy(dest, src);
  return dest;
}

/// Feature ///

typedef struct Feature
{
  double length;
  double width;
} Feature;

Feature calc_feature_average(Feature *features, const int features_len)
{
  double sum_length = 0;
  double sum_width = 0;

  for (int i = 0; i < features_len; i++)
  {
    sum_length += features[i].length;
    sum_width += features[i].width;
  }

  return (Feature){
      .length = sum_length / features_len,
      .width = sum_width / features_len,
  };
}

/// Iris ///

typedef struct Iris
{
  Feature sepal;
  Feature petal;
  char class[50];
} Iris;

Iris parse_str(const char *str)
{
  char buf[LINE_MAX];
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

void dump_iris(Iris iris, const char *name)
{
  printf("%s:\n", name);
  printf("  Sepal: (%lf, %lf)\n", iris.sepal.length, iris.sepal.width);
  printf("  Petal: (%lf, %lf)\n", iris.petal.length, iris.petal.width);
  printf("  Class: %s\n", iris.class);
}

Iris calc_iris_average(const Iris *iris_list, int iris_list_len)
{
  Feature *sepal_features = malloc(sizeof(Feature) * iris_list_len);
  Feature *petal_features = malloc(sizeof(Feature) * iris_list_len);

  for (int i = 0; i < iris_list_len; i++)
  {
    sepal_features[i] = iris_list[i].sepal;
    petal_features[i] = iris_list[i].petal;
  }

  Iris reduced_iris = {
      .sepal = calc_feature_average(sepal_features, iris_list_len),
      .petal = calc_feature_average(petal_features, iris_list_len),
  };

  free(sepal_features);
  free(petal_features);

  return reduced_iris;
}

/// File ///

int load_iris_from_file(const char *file_name, Iris *iris_list)
{
  FILE *fp = fopen(file_name, "r");
  continue_or_handle_file_error(fp, file_name);

  char line[LINE_MAX];
  int lines_len = 0;

  while (fgets(line, LINE_MAX, fp) != NULL)
  {
    iris_list[lines_len] = parse_str(line);
    lines_len++;
  }

  fclose(fp);
  return lines_len;
}

/// Main ///

int main(int argc, const char *argv[])
{
  const char *file_name = "assets/iris.data";
  Iris iris_list[LINES_MAX];
  int iris_list_len = load_iris_from_file(file_name, iris_list);

  for (int i = 0; i < iris_list_len; i++)
  {
    char *name;
    asprintf(&name, "Iris %d", i + 1);
    dump_iris(iris_list[i], name);
  }

  return 0;
}
