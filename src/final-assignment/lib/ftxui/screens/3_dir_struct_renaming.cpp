#pragma once

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"

#include <algorithm>
#include <iostream>
#include <map>
#include <optional>
#include <regex>

#include "../../dir.c"
#include "../../file.c"
#include "../../validate.c"
#include "../bindings.h"
#include "../utils.cpp"

using namespace ftxui;

Element get_hightailed_file_name(std::string before, std::string prefix, std::string suffix)
{
  auto fileName = analyze_file_name(before);
  return hbox({
      color(Color::Red, text(prefix)),
      text(fileName.name),
      color(Color::Red, text(suffix)),
      text("." + fileName.ext),
  });
}

DirStruct cpp_ask_dir_struct_renaming(DirStruct dir_struct, UserData user_data)
{
  auto screen = ScreenInteractive::Fullscreen();
  auto files = dir_files_to_vector(dir_struct);
  sort(files.begin(), files.end());

  char *c_prefix = get_prefix(dir_struct.base_path, dir_struct.files, dir_struct.file_count);
  char *c_suffix =
      get_suffix(dir_struct.files, dir_struct.file_count, std::to_string(user_data.mode).c_str(), user_data.student_id);

  std::string status;
  std::string prefix = c_prefix ? c_prefix : "";
  std::string suffix = c_suffix ? c_suffix : "";

  auto input_prefix = Input(&prefix, InputOption{.placeholder = "Prefix"});
  auto input_suffix = Input(&suffix, InputOption{.placeholder = "Suffix"});

  auto components = Container::Vertical({input_prefix, input_suffix});

  auto renderer = Renderer(components, [&] {
    std::vector<Element> idx_arr;
    std::vector<Element> files_before_arr;
    std::vector<Element> files_after_arr;

    for (int i = 0; i < files.size(); i++)
    {
      auto file = files[i];
      idx_arr.push_back(text(std::to_string(i)));
      files_before_arr.push_back(text(file));
      files_after_arr.push_back(get_hightailed_file_name(file, prefix, suffix));
    }

    return vbox({hbox({
                     input_prefix->Render() | size(WIDTH, EQUAL, 20),
                     text("___"),
                     input_suffix->Render() | size(WIDTH, EQUAL, 20),
                 }),
                 separator(),
                 hbox({
                     vbox(idx_arr),
                     separator(),
                     vbox(files_before_arr) | size(WIDTH, EQUAL, 50),
                     separator(),
                     text("→"),
                     separator(),
                     vbox(files_after_arr) | size(WIDTH, EQUAL, 50),
                 })});
  });

  screen.Loop(renderer);

  return dir_struct;
}
