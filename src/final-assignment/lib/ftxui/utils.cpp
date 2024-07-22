#pragma once

#include <algorithm>
#include <iostream>
#include <numeric>
#include <regex>
#include <vector>

#include "../types.c"

typedef struct
{
  std::string name;
  std::string ext;
} FileName;

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

FileName analyze_file_name(std::string file_name)
{
  std::regex re(R"((.*)\.([^.]+))");
  std::smatch match;
  std::regex_search(file_name, match, re);

  return FileName{.name = match[1], .ext = match[2]};
}
