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

/// Iris 分類するやつら ///

typedef struct IrisDistTuple
{
  // NOTE: Iris 構造体を連れ回すと重くなりそうなので, インデックスだけ持つ
  int iris_idx;
  double distance;
} IrisDistTuple;

void set_iris_dist_tuples_from_iris(const Iris iris, const Iris *iris_list, const int iris_list_len,
                                    IrisDistTuple *iris_dist_tuples)
{
  for (int i = 0; i < iris_list_len; i++)
  {
    iris_dist_tuples[i].iris_idx = i;
    iris_dist_tuples[i].distance = calc_iris_distance(iris, iris_list[i]);
  }
}

/// @brief `distance` で昇順ソート
void set_sorted_iris_dist_tuples(const IrisDistTuple *iris_dist_tuples, const int iris_dist_tuples_len,
                                 IrisDistTuple *iris_dist_tuples_sorted)
{
  // IrisDistTuple 構造体のコピー
  for (int i = 0; i < iris_dist_tuples_len; i++)
  {
    iris_dist_tuples_sorted[i] = iris_dist_tuples[i];
  }

  for (int i = 0; i < iris_dist_tuples_len; i++)
  {
    for (int j = iris_dist_tuples_len - 1; j > i; j--)
    {
      if (iris_dist_tuples_sorted[j - 1].distance > iris_dist_tuples_sorted[j].distance)
      {
        IrisDistTuple temp = iris_dist_tuples_sorted[j - 1];
        iris_dist_tuples_sorted[j - 1] = iris_dist_tuples_sorted[j];
        iris_dist_tuples_sorted[j] = temp;
      }
    }
  }
}

/// @param k 類似度の上位何個を見るか
/// @param class_candidates `class_candidates[idx]` は free してね！！！
void set_inferred_iris_class_knn(const Iris iris, const Iris *iris_list, const int k, const int iris_list_len,
                                 char *inferred_class, const char **unique_classes, int unique_classes_len,
                                 int *counted_unique_classes)
{
  IrisDistTuple iris_dist_tuples[iris_list_len];
  set_iris_dist_tuples_from_iris(iris, iris_list, iris_list_len, iris_dist_tuples);

  IrisDistTuple iris_dist_tuples_sorted[iris_list_len];
  set_sorted_iris_dist_tuples(iris_dist_tuples, iris_list_len, iris_dist_tuples_sorted);

  // クラスのカウントを初期化
  for (int i = 0; i < unique_classes_len; i++)
  {
    counted_unique_classes[i] = 0;
  }

  // 上位 k 個のクラス
  for (int i = 0; i < k; i++)
  {
    int iris_idx = iris_dist_tuples_sorted[i].iris_idx;
    for (int j = 0; j < unique_classes_len; j++)
    {
      if (strcmp(iris_list[iris_idx].class, unique_classes[j]) == 0)
      {
        counted_unique_classes[j]++;
        break;
      }
    }
  }

  // 最頻クラスを決定
  int max_count = 0;
  int max_count_idx = 0;
  for (int i = 0; i < unique_classes_len; i++)
  {
    if (counted_unique_classes[i] > max_count)
    {
      max_count = counted_unique_classes[i];
      max_count_idx = i;
    }
  }

  strcpy(inferred_class, unique_classes[max_count_idx]);
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

void print_header(const char **unique_classes, int unique_classes_len)
{
  printf("  | k\t| ");
  for (int uc = 0; uc < unique_classes_len; uc++)
  {
    printf("%s\t| ", unique_classes[uc]);
  }
  printf("\n  +\t+");
  for (int uc = 0; uc < unique_classes_len; uc++)
  {
    printf("\t\t+ ");
  }
  printf("\n");
}

void process_and_print_knn(const Iris sample, const Iris *iris_list, int iris_list_len, int k_step,
                           const char **unique_classes, int unique_classes_len)
{
  for (int k = 1; k <= iris_list_len; k += k_step)
  {
    char inferred_class[CLASS_LEN_MAX];
    int *counted_unique_classes = malloc(sizeof(int) * unique_classes_len);
    continue_or_handle_malloc_error(counted_unique_classes);

    set_inferred_iris_class_knn(sample, iris_list, k, iris_list_len, inferred_class, unique_classes, unique_classes_len,
                                counted_unique_classes);

    int cnt_max_idx = 0;
    for (int i = 0; i < unique_classes_len; i++)
    {
      if (counted_unique_classes[i] > counted_unique_classes[cnt_max_idx])
      {
        cnt_max_idx = i;
      }
    }

    printf("  | %d\t| ", k);
    for (int uc = 0; uc < unique_classes_len; uc++)
    {
      // printf("%d\t\t| ", counted_unique_classes[uc]);
      printf(cnt_max_idx == uc ? "\033[33m%d\033[0m\t\t| " : "%d\t\t| ", counted_unique_classes[uc]);
    }
    printf("\n");

    free(counted_unique_classes);
  }
}

int main(int argc, const char *argv[])
{
  const char *file_name = "assets/iris.data";
  Iris iris_list[LINES_MAX];
  int iris_list_len = load_iris_from_file(file_name, iris_list);

  char **unique_classes = malloc(sizeof(char *) * LINES_MAX);
  continue_or_handle_malloc_error(unique_classes);
  int unique_classes_len = set_iris_classes_unique(iris_list, iris_list_len, unique_classes);

  Iris samples[] = {
      {.sepal = {5.7, 4.0}, .petal = {1.2, 0.2}},
      {.sepal = {5.9, 2.9}, .petal = {4.2, 1.5}},
      {.sepal = {5.6, 2.8}, .petal = {4.8, 2.0}},
  };
  int samples_len = sizeof(samples) / sizeof(Iris);

  for (int s_idx = 0; s_idx < samples_len; s_idx++)
  {
    char *name;
    asprintf(&name, "Sample #%d (k = 1..%d)", s_idx + 1, iris_list_len);
    dump_iris(samples[s_idx], name);

    print_header((const char **)unique_classes, unique_classes_len);
    process_and_print_knn(samples[s_idx], iris_list, iris_list_len, 10, (const char **)unique_classes,
                          unique_classes_len);

    printf("\n");
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
