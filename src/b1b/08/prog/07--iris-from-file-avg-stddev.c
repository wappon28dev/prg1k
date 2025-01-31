#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 256
#define LINES_MAX 150
#define CLASS_LEN_MAX 50

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

Feature calc_feature_stddev(Feature *features, const int features_len)
{
  Feature average = calc_feature_average(features, features_len);

  double sum_length = 0;
  double sum_width = 0;

  for (int i = 0; i < features_len; i++)
  {
    sum_length += (features[i].length - average.length) * (features[i].length - average.length);
    sum_width += (features[i].width - average.width) * (features[i].width - average.width);
  }

  return (Feature){
      .length = sqrt(sum_length / features_len),
      .width = sqrt(sum_width / features_len),
  };
}

/// Iris ///

typedef struct Iris
{
  Feature sepal;
  Feature petal;
  char class[CLASS_LEN_MAX];
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
  if (strlen(iris.class) > 0)
  {
    printf("  Class: %s\n", iris.class);
  }
}

Iris calc_iris_average(const Iris *iris_list, int iris_list_len, const char *class)
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

  strcpy(reduced_iris.class, class);

  free(sepal_features);
  free(petal_features);

  return reduced_iris;
}

Iris calc_iris_stddev(const Iris *iris_list, int iris_list_len, const char *class)
{
  Feature *sepal_features = malloc(sizeof(Feature) * iris_list_len);
  Feature *petal_features = malloc(sizeof(Feature) * iris_list_len);

  for (int i = 0; i < iris_list_len; i++)
  {
    sepal_features[i] = iris_list[i].sepal;
    petal_features[i] = iris_list[i].petal;
  }

  Iris reduced_iris = {
      .sepal = calc_feature_stddev(sepal_features, iris_list_len),
      .petal = calc_feature_stddev(petal_features, iris_list_len),
  };

  strcpy(reduced_iris.class, class);

  free(sepal_features);
  free(petal_features);

  return reduced_iris;
}

/// @param unique_classes `unique_classes[idx]` は free してね！！！
int set_iris_classes_unique(const Iris *iris_list, const int iris_list_len, char **unique_classes)
{
  int idx = 0;
  for (int i = 0; i < iris_list_len; i++)
  {
    bool is_unique = true;
    for (int j = 0; j < idx; j++)
    {
      if (strcmp(unique_classes[j], iris_list[i].class) == 0)
      {
        is_unique = false;
        break;
      }
    }

    if (is_unique)
    {
      unique_classes[idx] = allocate_and_copy_string(iris_list[i].class);
      idx++;
    }
  }

  return idx;
}

int set_iris_filtered_by_class(const Iris *iris_list, const int iris_list_len, const char *class,
                               Iris *iris_list_filtered)
{
  int idx = 0;
  for (int i = 0; i < iris_list_len; i++)
  {
    if (strcmp(iris_list[i].class, class) == 0)
    {
      iris_list_filtered[idx] = iris_list[i];
      idx++;
    }
  }

  return idx;
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

  char **unique_classes = malloc(sizeof(char *) * LINES_MAX);
  continue_or_handle_malloc_error(unique_classes);
  int unique_classes_len = set_iris_classes_unique(iris_list, iris_list_len, unique_classes);

  for (int i = 0; i < unique_classes_len; i++)
  {
    Iris iris_list_filtered[LINES_MAX];
    int iris_list_filtered_len =
        set_iris_filtered_by_class(iris_list, iris_list_len, unique_classes[i], iris_list_filtered);

    Iris iris_avg = calc_iris_average(iris_list_filtered, iris_list_filtered_len, unique_classes[i]);
    Iris iris_stddev = calc_iris_stddev(iris_list_filtered, iris_list_filtered_len, unique_classes[i]);

    char *name;
    asprintf(&name, "%s (avg, sd)", unique_classes[i]);

    printf("%s:\n", name);
    printf("  Sepal: (%lf, %lf), (%lf, %lf)\n",
           //
           iris_avg.sepal.length, iris_avg.sepal.width, iris_stddev.sepal.length, iris_stddev.sepal.width);
    printf("  Petal: (%lf, %lf), (%lf, %lf)\n",
           //
           iris_avg.petal.length, iris_avg.petal.width, iris_stddev.petal.length, iris_stddev.petal.width);

    free(name);
  }

  /// dispose ///
  for (int i = 0; i < unique_classes_len; i++)
  {
    free(unique_classes[i]);
  }
  free(unique_classes);

  return 0;
}
