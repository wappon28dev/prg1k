#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_LINE_MAX 128
#define FILE_LINES_MAX 150

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

/// Trial ///

typedef struct trial
{
  int speed;
  int distance;
} Trial;

Trial parse_from_str(const char *data)
{
  Trial trial = {0, 0};
  sscanf(data, "%d,%d", &trial.speed, &trial.distance);
  return trial;
}

void dispTrial(Trial trial)
{
  printf("speed: %d [mph]\tdistance: %d [feet]\n", trial.speed, trial.distance);
}

/// Array ///

int calc_min(const int *arr, int arr_len)
{
  int min = INT_MAX;

  for (int i = 0; i < arr_len; i++)
  {
    if (arr[i] < min)
    {
      min = arr[i];
    }
  }

  return min;
}

int calc_max(const int *arr, int arr_len)
{
  int max = INT_MIN;

  for (int i = 0; i < arr_len; i++)
  {
    if (arr[i] > max)
    {
      max = arr[i];
    }
  }

  return max;
}

/// File ///

int load_trials_from_file(const char *file_name, Trial *trials)
{
  FILE *fp = fopen(file_name, "r");
  continue_or_handle_file_error(fp, file_name);

  char line[FILE_LINE_MAX];
  int lines_len = 0;

  while (fgets(line, FILE_LINE_MAX, fp) != NULL)
  {
    trials[lines_len] = parse_from_str(line);
    lines_len++;
  }

  fclose(fp);
  return lines_len;
}

/// Main ///

int main(int argc, const char *argv[])
{
  const char *file_name = "./cars.csv";

  Trial trials[FILE_LINE_MAX];
  int trials_len = load_trials_from_file(file_name, trials);

  // int arr[] = {2, 5, -1, 5, 6};
  // int arr_len = sizeof(arr) / sizeof(arr[0]);

  // printf("min: %d (== -1)\n", calc_min(arr, arr_len));
  // printf("max: %d (== 6)\n", calc_max(arr, arr_len));

  int speeds[trials_len];
  for (int i = 0; i < trials_len; i++)
  {
    speeds[i] = trials[i].speed;
  }

  int distances[trials_len];
  for (int i = 0; i < trials_len; i++)
  {
    distances[i] = trials[i].distance;
  }

  printf("speedの最小値: %d [mph]\n", calc_min(speeds, trials_len));
  printf("speedの最大値: %d [mph]\n", calc_max(speeds, trials_len));
  printf("distanceの最小値: %d [feet]\n", calc_min(distances, trials_len));
  printf("distanceの最大値: %d [feet]\n", calc_max(distances, trials_len));

  return 0;
}
