#pragma once

#include <iostream>
#include <vector>

#include "../types.c"

std::vector<std::string> dir_files_to_vector(DirStruct dir_struct)
{
  std::vector<std::string> files;
  for (int i = 0; i < 100; i++)
  {
    if (dir_struct.files[i] == NULL)
    {
      break;
    }

    files.push_back(dir_struct.files[i]);
  }

  return files;
}
