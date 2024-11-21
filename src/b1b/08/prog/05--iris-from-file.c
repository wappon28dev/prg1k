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

/// Iris ///

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
  printf("  Sepal: (%f, %f)\n", iris.sepal.length, iris.sepal.width);
  printf("  Petal: (%f, %f)\n", iris.petal.length, iris.petal.width);
  printf("  Class: %s\n", iris.class);
}

Feature __calc_average(Feature *features, const int features_len)
{
  float sum_length = 0;
  float sum_width = 0;

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
      .sepal = __calc_average(sepal_features, iris_list_len),
      .petal = __calc_average(petal_features, iris_list_len),
  };

  free(sepal_features);
  free(petal_features);

  return reduced_iris;
}

void set_iris_filtered_by_class(const Iris *iris_list, const int iris_list_len, const char *class,
                                Iris *filtered_iris_list, int *filtered_iris_list_len)
{
  int idx = 0;
  for (int i = 0; i < iris_list_len; i++)
  {
    printf("iris_list[%d].class: %s\n", i, iris_list[i].class);
    if (strcmp(iris_list[i].class, class) == 0)
    {
      filtered_iris_list[idx] = iris_list[i];
      idx++;
    }
  }

  *filtered_iris_list_len = idx;
}

/// File ///

void set_lines(FILE *fp, char **lines, int *lines_len)
{

  char line[LINE_MAX];
  int idx = 0;

  while (fgets(line, LINE_MAX, fp) != NULL)
  {
    lines[idx] = malloc(sizeof(char) * LINE_MAX);
    continue_or_handle_malloc_error(lines[idx]);

    strcpy(lines[idx], line);
    idx++;
  }

  *lines_len = idx;
}

int main(int argc, const char *argv[])
{
  const char *file_name = "assets/iris.data";
  FILE *fp = fopen(file_name, "r");
  continue_or_handle_file_error(fp, file_name);

  char *lines[LINES_MAX];
  int lines_len = 0;
  set_lines(fp, lines, &lines_len);

  Iris iris_list[lines_len];
  for (int i = 0; i < lines_len; i++)
  {
    iris_list[i] = parse_str(lines[i]);
  }

  for (int i = 0; i < lines_len; i++)
  {
    char *name;
    asprintf(&name, "Iris %d", i + 1);
    dump_iris(iris_list[i], name);
  }

  fclose(fp);
  return 0;
}
