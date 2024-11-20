#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void continue_or_handle_malloc_error(void *ptr)
{
  if (ptr == NULL)
  {
    fprintf(stderr, "メモリの確保に失敗しました: %s\n", strerror(errno));
    exit(1);
  }
}

int calc_sum(int arr[], int arr_length)
{
  int sum = 0;
  for (int i = 0; i < arr_length; i++)
  {
    sum += arr[i];
  }
  return sum;
}

double calc_avarage(int sum, int arr_length)
{
  return (double)sum / arr_length;
}

double calc_stdev(int arr[], int arr_length, double avarage)
{
  double sum = 0;
  for (int i = 0; i < arr_length; i++)
  {
    sum += (arr[i] - avarage) * (arr[i] - avarage);
  }
  return sqrt(sum / arr_length);
}

double calc_chance_of(int score, double avarage, double stdev)
{
  return 1 / (stdev * sqrt(2 * M_PI)) * exp(-1 * (score - avarage) * (score - avarage) / (2 * stdev * stdev));
}

void dump_arr(char *name, int arr[], int arr_length)
{
  for (int i = 0; i < arr_length; i++)
  {
    printf("%s[%i] -> %d\n", name, i, arr[i]);
  }
}

int main(int argc, char *argv[])
{
  int num_of_ppl;
  printf("人数? ");
  scanf("%d", &num_of_ppl);

  int *scores = malloc(sizeof(int) * num_of_ppl);
  continue_or_handle_malloc_error(scores);

  for (int i = 0; i < num_of_ppl; i++)
  {
    printf("(%d/%d)\t点数? ", i + 1, num_of_ppl);
    scanf("%d", &scores[i]);
  }

  int sum = calc_sum(scores, num_of_ppl);
  double avarage = calc_avarage(sum, num_of_ppl);
  double stdev = calc_stdev(scores, num_of_ppl, avarage);
  double chance = calc_chance_of(50, avarage, stdev);

  printf("平均: %f\n", avarage);
  printf("標準偏差: %f\n", stdev);
  printf("50 点を取る確率: %f\n", chance);

  free(scores);

  return 0;
}
