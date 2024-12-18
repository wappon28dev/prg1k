#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

/// Index ///

void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int rand_with_range(int min, int max)
{
  // NOTE:
  // - モジュロバイアスによる乱数の精度に注意.
  // - `random()` は安全だが POSIX 標準でないので注意.
  return rand() % (max - min + 1) + min;
}

void shuffle(int a[], int n)
{
  srand(time(NULL));
  for (int i = n - 1; i >= 1; i--)
  {
    int j = rand_with_range(0, i);
    swap(&a[j], &a[i]);
  }
}

/// Feature ///

typedef struct Feature
{
  double length;
  double width;
} Feature;

double calc_feature_distance(Feature feature1, Feature feature2)
{
  return sqrt(pow(feature1.length - feature2.length, 2) + pow(feature1.width - feature2.width, 2));
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

double calc_iris_distance(const Iris iris1, const Iris iris2)
{
  return calc_feature_distance(iris1.sepal, iris2.sepal) + calc_feature_distance(iris1.petal, iris2.petal);
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

void set_iris_list_shuffled(const Iris *iris_list, const int iris_list_len, Iris *iris_list_shuffled)
{
  int indexes[iris_list_len];
  for (int i = 0; i < iris_list_len; i++)
  {
    indexes[i] = i;
  }

  shuffle(indexes, iris_list_len);

  for (int i = 0; i < iris_list_len; i++)
  {
    iris_list_shuffled[i] = iris_list[indexes[i]];
  }
}

int set_iris_list_sliced(const Iris *iris_list, const int start, const int end, Iris *iris_list_sliced)
{
  for (int i = start; i < end; i++)
  {
    iris_list_sliced[i - start] = iris_list[i];
  }

  return end - start;
}

/// IrisClassPair ///

typedef struct IrisClassPair
{
  char correct[CLASS_LEN_MAX];
  char inferred[CLASS_LEN_MAX];
} IrisClassPair;

void dump_confusion_mat(const char **unique_classes, const int unique_classes_len,
                        const IrisClassPair *iris_class_pairs, const int iris_class_pairs_len)
{
  int *class_totals = malloc(sizeof(int) * unique_classes_len);
  for (int i = 0; i < unique_classes_len; i++)
  {
    class_totals[i] = 0;
    for (int k = 0; k < iris_class_pairs_len; k++)
    {
      if (strcmp(iris_class_pairs[k].correct, unique_classes[i]) == 0)
      {
        class_totals[i]++;
      }
    }
  }

  printf("\\\t\t");
  for (int i = 0; i < unique_classes_len; i++)
  {
    printf("| %s\t", unique_classes[i]);
  }
  printf("\n");

  printf("+\t\t");
  for (int i = 0; i < unique_classes_len; i++)
  {
    printf("+\t\t");
  }

  for (int i = 0; i < unique_classes_len; i++)
  {
    printf("\n%s\t", unique_classes[i]);

    for (int j = 0; j < unique_classes_len; j++)
    {
      int count = 0;
      for (int k = 0; k < iris_class_pairs_len; k++)
      {
        if (strcmp(iris_class_pairs[k].correct, unique_classes[i]) == 0 &&
            strcmp(iris_class_pairs[k].inferred, unique_classes[j]) == 0)
        {
          count++;
        }
      }

      double ratio = (class_totals[i] > 0) ? (double)count / class_totals[i] : 0.0;
      printf("| %.3f\t\t", ratio);
    }
  }

  printf("\n");

  free(class_totals);
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

  Iris iris_list_shuffled[LINES_MAX];
  set_iris_list_shuffled(iris_list, iris_list_len, iris_list_shuffled);

  int n = 5;
  int iris_list_test_len = iris_list_len / n;
  int iris_list_train_len = iris_list_len - iris_list_test_len;

  for (int k = 0; k < n; k++)
  {
    Iris iris_list_test[iris_list_test_len];
    set_iris_list_sliced(iris_list_shuffled, k * iris_list_test_len, (k + 1) * iris_list_test_len, iris_list_test);

    Iris iris_list_train[iris_list_train_len];
    set_iris_list_sliced(iris_list_shuffled, 0, k * iris_list_test_len, iris_list_train);

    printf("k = %d\n", k);
    printf("Test: #%d..#%d\n", k * iris_list_test_len, (k + 1) * iris_list_test_len);
    printf("Train: #0..#%d, #%d..#%d\n", k * iris_list_test_len, k * iris_list_test_len, iris_list_len);

    IrisClassPair iris_class_pairs[iris_list_test_len];

    for (int i = 0; i < iris_list_test_len; i++)
    {
      Iris iris = iris_list_test[i];
      char inferred_class[CLASS_LEN_MAX];
      double calculated_distance;
      set_inferred_iris_class(iris, iris_list_train, iris_list_train_len, inferred_class, &calculated_distance);

      strcpy(iris_class_pairs[i].correct, iris.class);
      strcpy(iris_class_pairs[i].inferred, inferred_class);
    }

    dump_confusion_mat((const char **)unique_classes, unique_classes_len, iris_class_pairs, iris_list_test_len);

    puts("---");
  }

  /// dispose ///
  for (int i = 0; i < unique_classes_len; i++)
  {
    free(unique_classes[i]);
  }
  free(unique_classes);

  return 0;
}
