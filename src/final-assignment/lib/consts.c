#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ARR_MAX 100

void handle_unhanded_error(const char *message)
{
  fprintf(stderr, "\n\n--- UNHANDED ERROR OCCURRED ---\n");
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}
