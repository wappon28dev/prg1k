#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./consts.c"
#include "./types.c"

#define MAX_LINE_LENGTH 1024

ResultChar get_file_content(char *file_path)
{
  FILE *file = fopen(file_path, "r");
  char line[MAX_LINE_LENGTH];
  char *content = NULL;
  size_t content_size = 0;

  if (!file)
  {
    return (ResultChar){.error_message = "Failed to open file"};
  }

  while (fgets(line, MAX_LINE_LENGTH, file))
  {
    size_t line_length = strlen(line);
    content = realloc(content, content_size + line_length + 1);
    if (!content)
    {
      fclose(file);
      return (ResultChar){.error_message = "Failed to allocate memory"};
    }

    strcpy(content + content_size, line);
    content_size += line_length;
  }

  fclose(file);

  if (content_size == 0)
  {
    fprintf(stderr, "INFO: File %s is empty\n", file_path);
    return (ResultChar){.value = "<empty>"};
  }

  return (ResultChar){.value = content};
}

// int main(void)
// {
//   char *input_filename = "./LICENSE";
//   char *content = get_file_content(input_filename);

//   puts(content);

//   return EXIT_SUCCESS;
// }
