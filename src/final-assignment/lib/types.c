#pragma once

#include "./consts.c"

typedef struct
{
  char *path;
  char *content;
} FileEntry;

typedef struct
{
  char *zip_file_name;
  FileEntry fileEntries[ARR_MAX];
  int file_entry_count;
} ZipEntry;

typedef struct
{
  char *err_message;
  ZipEntry value;
} ResultZipEntry;

typedef struct
{
  /// ディレクトリのパス
  char *base_path;
  char *files[ARR_MAX];
  int file_count;
} DirStuct;

/// Result<DirStruct>
/// - 成功した場合は `value` が存在する
/// - 失敗した場合は `err_message` にエラーメッセージが格納される
typedef struct
{
  DirStuct value;
  char *err_message;
} ResultDirStruct;

/// Result<DirStruct>
/// - 失敗した場合は `err_message` にエラーメッセージが格納される
typedef struct
{
  char *err_message;
} ResultVoid;

typedef struct
{
  char *error_message;
  char *value;
} ResultChar;
