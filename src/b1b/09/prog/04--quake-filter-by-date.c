#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LINES_MAX 16384 // 2^14

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

/// Date ///

typedef struct Date
{
  int year;
  int month;
  int day;
} Date;

Date tm_to_date(const struct tm *time)
{
  Date date = {
      .year = time->tm_year + 1900,
      .month = time->tm_mon + 1,
      .day = time->tm_mday,
  };
  return date;
}

struct tm date_to_tm(const Date date)
{
  struct tm time = {
      .tm_year = date.year - 1900,
      .tm_mon = date.month - 1,
      .tm_mday = date.day,
  };
  return time;
}

char *date_to_str(const Date date)
{
  char *str;
  asprintf(&str, "%d-%02d-%02d", date.year, date.month, date.day);
  return str;
}

/// Point ///

typedef struct Point
{
  double lat;
  double lon;
} Point;

/// Intensity ///

/// 震度
/// ref:
///  https://www.data.jma.go.jp/svd/eqev/data/bulletin/data/format/hypfmt_j.html#:~:text=A1-,%E6%9C%80%E5%A4%A7%E9%9C%87%E5%BA%A6,-1%3A%20%E9%9C%87%E5%BA%A61
typedef enum IntensityKey
{
  i_1,
  i_2,
  i_3,
  i_4,
  i_A,
  i_B,
  i_C,
  i_D,
  i_7,
  UNKNOWN
} IntensityKey;

typedef struct Intensity
{
  IntensityKey key;
  char char_key;
  const char *name;
} Intensity;

const Intensity __intensity_map[] = {
    {i_1, '1', "震度 1"},    {i_2, '2', "震度 2"},    {i_3, '3', "震度 3"},    {i_4, '4', "震度 4"},
    {i_A, 'A', "震度 5 弱"}, {i_B, 'B', "震度 5 強"}, {i_C, 'C', "震度 6 弱"}, {i_D, 'D', "震度 6 強"},
    {i_7, '7', "震度 7"},    {UNKNOWN, '\0', "不明"},
};

Intensity get_intensity_from_char(const char input)
{
  int idx = 0;
  while (__intensity_map[idx].key != UNKNOWN)
  {
    if (__intensity_map[idx].char_key == input)
    {
      return __intensity_map[idx];
    }
    idx++;
  }

  return __intensity_map[idx]; // To be UNKNOWN
}

/// Quake ///

typedef struct Quake
{
  Date date;
  Point point;
  Intensity intensity;
} Quake;

typedef struct QuakeRaw
{
  int year;
  int month;
  int day;
  double lat;
  double lon;
  char intensity;
} QuakeRaw;

void dump_quake(const Quake quake, const char *name)
{
  char *date_str = date_to_str(quake.date);
  printf("%s:\n", name);
  printf("  Date: %s\n", date_str);
  printf("  Point: (%lf, %lf)\n", quake.point.lat, quake.point.lon);
  printf("  Intensity: %s\n", quake.intensity.name);
  free(date_str);
}

QuakeRaw parse_quake_raw(const char *str)
{
  char buf[256];
  strcpy(buf, str);

  QuakeRaw quake_raw;
  quake_raw.year = atoi(strtok(buf, ","));
  quake_raw.month = atoi(strtok(NULL, ","));
  quake_raw.day = atoi(strtok(NULL, ","));
  quake_raw.lat = atof(strtok(NULL, ","));
  quake_raw.lon = atof(strtok(NULL, ","));
  quake_raw.intensity = strtok(NULL, ",")[0];
  return quake_raw;
}

Quake convert_quake_raw_to_quake(const QuakeRaw quake_raw)
{
  return (Quake){
      .date =
          (Date){
              .year = quake_raw.year,
              .month = quake_raw.month,
              .day = quake_raw.day,
          },
      .point =
          (Point){
              .lat = quake_raw.lat,
              .lon = quake_raw.lon,
          },
      .intensity = get_intensity_from_char(quake_raw.intensity),
  };
}

int set_filtered_quakes_by_date(const Quake *quakes, const int quakes_len, const Date date, Quake *quakes_filtered)
{
  struct tm date_tm = date_to_tm(date);
  time_t target_time = mktime(&date_tm);

  int idx = 0;
  for (int i = 0; i < quakes_len; i++)
  {
    struct tm quake_tm = date_to_tm(quakes[i].date);
    time_t quake_time = mktime(&quake_tm);

    if (difftime(target_time, quake_time) == 0)
    {
      quakes_filtered[idx] = quakes[i];
      idx++;
    }
  }
  return idx;
}

/// File ///

int set_loaded_quake_raw_list(const char *file_name, QuakeRaw *quake_raw_list)
{
  FILE *fp = fopen(file_name, "r");
  continue_or_handle_file_error(fp, file_name);

  int idx = 0;
  while (true)
  {
    char line[LINES_MAX];
    if (fgets(line, sizeof(line), fp) == NULL)
    {
      break;
    }
    quake_raw_list[idx] = parse_quake_raw(line);
    idx++;
  }

  fclose(fp);
  return idx;
}

/// Main ///

int main(int argc, char *argv[])
{
  const char *file_name = "assets/h2011_eq.csv";
  QuakeRaw quake_raw_list[LINES_MAX];
  int quake_raw_list_len = set_loaded_quake_raw_list(file_name, quake_raw_list);

  Quake quakes[quake_raw_list_len];
  int quakes_len = quake_raw_list_len;
  for (int i = 0; i < quakes_len; i++)
  {
    quakes[i] = convert_quake_raw_to_quake(quake_raw_list[i]);
  }

  Quake quakes_filtered[quakes_len];
  Date target_date = {2011, 3, 11};
  int quakes_filtered_len = set_filtered_quakes_by_date(quakes, quakes_len, target_date, quakes_filtered);

  for (int i = 0; i < quakes_filtered_len; i++)
  {
    char *name;
    asprintf(&name, "Quake on %s #%d", date_to_str(quakes_filtered[i].date), i + 1);
    dump_quake(quakes_filtered[i], name);
    free(name);
  }

  return 0;
}
