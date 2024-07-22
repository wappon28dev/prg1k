#pragma once

#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "./types.c"

const char *get_dir_name(UserData user_data)
{
  if (user_data.mode == PRACTICE)
  {
    return strdup(user_data.student_id);
  }
  else
  {
    char *dir_name;
    asprintf(&dir_name, "%s_issues", user_data.student_id);
    return strdup(dir_name);
  }
}

ResultChar make_dir_in_tmp()
{
  time_t now = time(NULL);
  if (now == -1)
  {
    return (ResultChar){.err_message = "make_dir_in_tmp: Failed to get current time"};
  }

  char folderName[256];
  snprintf(folderName, sizeof(folderName), "/tmp/cook-zip-c-%ld", now);

  if (mkdir(folderName, 0777) == -1)
  {
    return (ResultChar){.err_message = "make_dir_in_tmp: Failed to create directory"};
  }

  return (ResultChar){.value = strdup(folderName)};
}

/// @brief ディレクトリー内のファイルの一覧を取得する
/// @param dir_path 探索ディレクトリーのパス
/// @return Result<DirStruct>
ResultDirStruct get_dir_files(const char *dir_path)
{
  DirStruct value = {.base_path = dir_path, .file_count = 0};
  DIR *dir = opendir(dir_path);

  if (dir == NULL)
  {
    return (ResultDirStruct){.err_message = "get_dir_files: Failed to open directory"};
  }

  struct dirent *entry;
  int idx = 0;

  while ((entry = readdir(dir)) != NULL && idx < ARR_MAX)
  {
    value.files[idx] = (char *)malloc(strlen(entry->d_name) + 1);

    if (value.files[idx] == NULL)
    {
      closedir(dir);
      return (ResultDirStruct){.err_message = "get_dir_files: Memory allocation failed"};
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
    return (ResultDirStruct){.err_message = "get_dir_files: Failed to close directory"};
  }

  return (ResultDirStruct){.value = value};
}
