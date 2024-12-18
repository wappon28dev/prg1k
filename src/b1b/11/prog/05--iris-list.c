#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

int set_iris_list_sliced(const Iris *iris_list, const int iris_list_len, const int start, const int end,
                         Iris *iris_list_sliced)
{
  for (int i = start; i < end; i++)
  {
    iris_list_sliced[i - start] = iris_list[i];
  }

  return end - start;
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

  Iris iris_list_shuffled[LINES_MAX];
  set_iris_list_shuffled(iris_list, iris_list_len, iris_list_shuffled);

  int iris_list_test_len = iris_list_len / 5;
  int iris_test_train_len = iris_list_len - iris_list_test_len;

  Iris iris_list_test[iris_list_test_len];
  set_iris_list_sliced(iris_list_shuffled, iris_list_len, 0, iris_list_test_len, iris_list_test);

  Iris iris_list_train[iris_test_train_len];
  set_iris_list_sliced(iris_list_shuffled, iris_list_len, iris_list_test_len, iris_list_len, iris_list_train);

  printf("Test: #0..#%d\n", iris_list_test_len);
  printf("Train: #%d..#%d\n", iris_list_test_len, iris_list_len);

  return 0;
}
