#pragma once

#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./consts.c"
#include "./types.c"

/// @brief
/// @param dir_path
/// @return
ResultDirStruct get_dir_files(char *dir_path)
{
  DirStuct value = {.base_path = dir_path, .file_count = 0};
  DIR *dir = opendir(dir_path);

  if (dir == NULL)
  {
    return (ResultDirStruct){.err_message = "Failed to open directory"};
  }

  struct dirent *entry;
  int idx = 0;

  while ((entry = readdir(dir)) != NULL && idx < ARR_MAX)
  {
    value.files[idx] = malloc(strlen(entry->d_name) + 1);

    if (value.files[idx] == NULL)
    {
      closedir(dir);
      return (ResultDirStruct){.err_message = "Memory allocation failed"};
    }

    strcpy(value.files[idx], entry->d_name);
    printf("%d -> %s\n", idx, value.files[idx]);

    idx++;
  }

  value.file_count = idx;

  if (closedir(dir) == -1)
  {
    return (ResultDirStruct){.err_message = "Failed to close directory"};
  }

  return (ResultDirStruct){.value = value};
}

// int main()
// {
//   ResultDirStruct result = get_dir_files(".");
//   if (result.err_message == NULL)
//   {
//     printf("Success\n");
//     for (int i = 0; i < result.value.file_count; i++)
//     {
//       printf("%s\n", result.value.files[i]);
//     }
//   }
//   else
//   {
//     printf("Error: %s\n", result.err_message);
//   }
//   return 0;
// }
