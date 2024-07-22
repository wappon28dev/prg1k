#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void handle_unhanded_error(const char *message)
{
  fprintf(stderr, "\n\n--- UNHANDED ERROR OCCURRED ---\n");
  fprintf(stderr, "%s\n", message);
  fprintf(stderr, "--------------------------------\n\n");
  exit(EXIT_FAILURE);
}

const char *LOGO = "  _____          __     ____  _              _____  _            __\n"
                   " / ___/__  ___  / /__  /_  / (_)__    ____  / ___/ (_)_ _  ___  / /\n"
                   "/ /__/ _ \\/ _ \\/  '_/   / /_/ / _ \\  /___/ / /__  / /  ' \\/ _ \\/ / \n"
                   "\\___/\\___/\\___/_/\\_\\   /___/_/ .__/        \\___/ /_/_/_/_/ .__/_(_)\n"
                   "                            /_/                         /_/        \n";
