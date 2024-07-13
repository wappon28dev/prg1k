#pragma once

#include "./consts.c"

typedef struct
{
  const char *path;
  const char *content;
} FileEntry;

/// Zip ファイルの作成に必要なエントリー
typedef struct
{
  const char *zip_file_path;
  FileEntry file_entries[ARR_MAX];
  int file_entry_count;
} ZipEntry;

typedef struct
{
  const char *err_message;
  ZipEntry value;
} ResultZipEntry;

typedef struct
{
  /// ディレクトリのパス
  const char *base_path;
  const char *files[ARR_MAX];
  int file_count;
} DirStuct;

/// Result<DirStruct>
/// - 成功した場合は `value` が存在する
/// - 失敗した場合は `err_message` にエラーメッセージが格納される
typedef struct
{
  DirStuct value;
  const char *err_message;
} ResultDirStruct;

/// Result<DirStruct>
/// - 失敗した場合は `err_message` にエラーメッセージが格納される
typedef struct
{
  const char *err_message;
  const char *cause;
} ResultVoid;

typedef struct
{
  const char *error_message;
  const char *value;
} ResultChar;
