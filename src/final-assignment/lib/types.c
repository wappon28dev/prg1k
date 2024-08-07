#pragma once

#define ARR_MAX 100

typedef struct
{
  const char *path;
  const char *renamed;
  const char *content;
} FileEntry;

/// Zip ファイルの作成に必要なエントリー
typedef struct
{
  /// 作成する Zip ファイルのパス
  const char *zip_file_path;
  FileEntry file_entries[ARR_MAX];
  int file_entries_length;
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
} DirStruct;

/// Result<DirStruct>
/// - 成功した場合は `value` が存在する
/// - 失敗した場合は `err_message` にエラーメッセージが格納される
typedef struct
{
  DirStruct value;
  const char *err_message;
} ResultDirStruct;

/// Result<DirStruct>
/// - 失敗した場合は `err_message` にエラーメッセージが格納される
typedef struct
{
  const char *err_message;
  const char *cause;
} ResultVoid;

/// Result<DirStruct>
typedef struct
{
  const char *err_message;
  const char *value;
} ResultChar;

/// Result<DirStruct>
typedef struct
{
  const bool value;
  const char *err_message;
} ResultBool;

/// 提出物の種類
enum MODE
{
  PRACTICE = 0,
  ISSUES = 1,
};
typedef enum MODE Mode;

/// ユーザーに求める情報
typedef struct
{
  const char *student_id;
  Mode mode;
  const char *path;
} UserData;
