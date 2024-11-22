#include <errno.h>
#include <float.h>
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

double calc_feature_distance(Feature feature1, Feature feature2)
{
  return sqrt(pow(feature1.length - feature2.length, 2) + pow(feature1.width - feature2.width, 2));
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

double calc_iris_distance(const Iris iris1, const Iris iris2)
{
  return calc_feature_distance(iris1.sepal, iris2.sepal) + calc_feature_distance(iris1.petal, iris2.petal);
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

void set_inferred_iris_class(const Iris iris, const Iris *iris_list, const int iris_list_len, char *inferred_class,
                             double *calculated_distance)
{
  double min_distance = DBL_MAX;
  for (int i = 0; i < iris_list_len; i++)
  {
    double distance = calc_iris_distance(iris, iris_list[i]);
    if (distance < min_distance)
    {
      min_distance = distance;
      strcpy(inferred_class, iris_list[i].class);
    }
  }

  *calculated_distance = min_distance;
  return;
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

  Iris iris_list_unique_avg[unique_classes_len];
  for (int i = 0; i < unique_classes_len; i++)
  {
    Iris iris_list_filtered[iris_list_len];
    int iris_list_filtered_len =
        set_iris_filtered_by_class(iris_list, iris_list_len, unique_classes[i], iris_list_filtered);

    iris_list_unique_avg[i] = calc_iris_average(iris_list_filtered, iris_list_filtered_len, unique_classes[i]);
  }

  Iris samples[] = {
      {.sepal = {5.7, 4.0}, .petal = {1.2, 0.2}},
      {.sepal = {5.9, 2.9}, .petal = {4.2, 1.5}},
      {.sepal = {5.6, 2.8}, .petal = {4.8, 2.0}},
  };
  int samples_len = sizeof(samples) / sizeof(Iris);

  for (int i = 0; i < samples_len; i++)
  {
    char inferred_class[CLASS_LEN_MAX];
    double calculated_distance;
    set_inferred_iris_class(samples[i], iris_list_unique_avg, unique_classes_len, inferred_class, &calculated_distance);

    char *name;
    asprintf(&name, "Sample #%d", i + 1);
    dump_iris(samples[i], name);
    printf("  Inferred Class: %s\n", inferred_class);
    printf("     -> Distance: %lf\n", calculated_distance);
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
