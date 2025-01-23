#include <errno.h>
#include <limits.h>
#include <math.h>
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

double calc_mse(const int *list_expected, const int *list_predicted, int list_len)
{
  double sqrt_mean;

  for (int i = 0; i < list_len; i++)
  {
    sqrt_mean += pow(list_expected[i] - list_predicted[i], 2);
  }

  return (1 / (double)list_len) * sqrt_mean;
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

  int distances_expected[trials_len];
  int distances_predicted[trials_len];

  for (int i = 0; i < trials_len; i++)
  {
    Trial trial = trials[i];

    distances_expected[i] = trial.distance;
    distances_predicted[i] = 2 * trial.speed;
  }

  printf("MSE: %lf\n", calc_mse(distances_expected, distances_predicted, trials_len));

  return 0;
}
