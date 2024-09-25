#pragma once

#include <algorithm>
#include <iostream>
#include <numeric>
#include <regex>
#include <vector>

#include "../types.c"

typedef struct
{
  /// ファイル名
  std::string name;
  /// 拡張子
  std::string ext;
} FileName;

/// @brief `const char *files[ARR_MAX]` から std のベクターへ変換します.
/// @return std::vector<std::string>
std::vector<std::string> dir_files_to_vector(DirStruct dir_struct)
{
  std::vector<std::string> files;
  for (int i = 0; i < dir_struct.file_count; i++)
  {
    if (dir_struct.files[i] == NULL)
    {
      break;
    }

    files.push_back(dir_struct.files[i]);
  }

  return files;
}

/// @brief ファイル名と拡張子とを分離します.
/// @return FileName
FileName split_file_name_ext(std::string file_name)
{
  std::regex re(R"((.*)\.([^.]+))");
  std::smatch match;
  std::regex_search(file_name, match, re);

  return FileName{.name = match[1], .ext = match[2]};
}
