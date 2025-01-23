#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/// Main ///

int main(int argc, const char *argv[])
{
  const char line[] = "10,18\n";
  Trial trial = parse_from_str(line);

  dispTrial(trial);

  return 0;
}
