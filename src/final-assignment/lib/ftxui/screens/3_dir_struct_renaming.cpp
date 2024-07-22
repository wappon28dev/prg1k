#pragma once

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"

#include <algorithm>
#include <iostream>
#include <optional>
#include <regex>

#include "../../dir.c"
#include "../../file.c"
#include "../../validate.c"
#include "../bindings.h"
#include "../utils.cpp"

using namespace ftxui;

ResultDirStruct cpp_ask_dir_struct_renaming(DirStruct dir_struct, UserData user_data)
{
  auto screen = ScreenInteractive::Fullscreen();
  auto files = dir_files_to_vector(dir_struct);

  char *c_prefix = get_prefix(dir_struct.base_path, dir_struct.files, dir_struct.file_count);
  char *c_suffix =
      get_suffix(dir_struct.files, dir_struct.file_count, std::to_string(user_data.mode).c_str(), user_data.student_id);

  // printf("Prefix: %s\n", prefix ? prefix : "NULL");
  // printf("Suffix: %s\n", suffix ? suffix : "NULL");

  std::string status;
  std::string prefix = c_prefix;
  std::string suffix = c_suffix;

  auto input_prefix = Input(&prefix);
  auto input_suffix = Input(&suffix);

  auto files_before = Container::Vertical({});
  auto files_after = Container::Vertical({});

  auto components = Container::Vertical({input_prefix, input_suffix});

  auto renderer = Renderer(components, [&] {
    return vbox({

        hbox({
            text("Prefix: "),
            input_prefix->Render() | size(WIDTH, EQUAL, 20),
            text("XXXXXX"),
            input_suffix->Render() | size(WIDTH, EQUAL, 20),
            text(": Suffix"),
        }),

        hbox({
            files_before->Render() | flex,
            separator(),
            files_after->Render() | flex,
        }) | flex,
    });
  });

  return ResultDirStruct{.value = dir_struct};
}
