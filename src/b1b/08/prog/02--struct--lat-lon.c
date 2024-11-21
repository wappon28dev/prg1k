#include <stdio.h>

typedef struct Point
{
  char name[20];
  char address[100];
  float lat;
  float lon;
} Point;

int main(int argc, char *argv[])
{
  Point points[2] = {
      {
          "愛工大",
          "愛知県豊田市八草町八千草１２４７",
          35.1834122,
          137.1130419,
      },
      {
          "愛工大名電",
          "愛知県名古屋市千種区若水３丁目２−１２",
          35.1783171,
          136.9490147,
      },
  };
  int points_len = sizeof(points) / sizeof(points[0]);

  puts("名前\t住所\t緯度\t経度");
  puts("----\t----\t----\t----");
  for (int i = 0; i < points_len; i++)
  {
    Point point = points[i];
    printf("%s\t%s\t%f\t%f\n", point.name, point.address, point.lat, point.lon);
  }

  return 0;
}
