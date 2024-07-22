#pragma once

#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./types.c"

/// @brief ディレクトリー内のファイルの一覧を取得する
/// @param dir_path 探索ディレクトリーのパス
/// @return Result<DirStruct>
ResultDirStruct get_dir_files(const char *dir_path)
{
  DirStruct value = {.base_path = dir_path, .file_count = 0};
  DIR *dir = opendir(dir_path);

  if (dir == NULL)
  {
    return (ResultDirStruct){.err_message = "Failed to open directory"};
  }

  struct dirent *entry;
  int idx = 0;

  while ((entry = readdir(dir)) != NULL && idx < ARR_MAX)
  {
    value.files[idx] = (char *)malloc(strlen(entry->d_name) + 1);

    if (value.files[idx] == NULL)
    {
      closedir(dir);
      return (ResultDirStruct){.err_message = "Memory allocation failed"};
    }

    if (entry->d_type == DT_DIR)
    {
      continue;
    }

    value.files[idx] = strdup(entry->d_name);
    idx++;
  }

  value.file_count = idx;

  if (closedir(dir) == -1)
  {
    return (ResultDirStruct){.err_message = "Failed to close directory"};
  }

  return (ResultDirStruct){.value = value};
}
