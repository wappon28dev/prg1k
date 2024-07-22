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

std::string get_file_name(std::string file_name, std::string prefix, std::string suffix)
{
  auto fileName = analyze_file_name(file_name);
  return prefix + fileName.name + suffix + "." + fileName.ext;
}

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

DirStruct cpp_ask_dir_struct_renamed(DirStruct dir_struct, UserData user_data)
{
  auto screen = ScreenInteractive::Fullscreen();
  std::string status = "";

  auto files = dir_files_to_vector(dir_struct);
  sort(files.begin(), files.end());

  char *c_prefix = get_prefix(dir_struct);
  char *c_suffix = get_suffix(dir_struct, user_data);
  std::string prefix = c_prefix == NULL ? "" : c_prefix;
  std::string suffix = c_suffix == NULL ? "" : c_suffix;

  if (c_prefix != NULL)
  {
    status = "🔧 Prefix: " + prefix;
  }

  if (c_suffix != NULL)
  {
    status += "🔧 Suffix: " + suffix;
  }

  auto button = Button("   CREATE >   ", [&] { screen.ExitLoopClosure()(); });
  auto input_suffix = Input(
      &suffix, InputOption{.placeholder = "Suffix", .multiline = false, .on_enter = [&] { button->TakeFocus(); }});
  auto input_prefix =
      Input(&prefix,
            InputOption{.placeholder = "Prefix", .multiline = false, .on_enter = [&] { input_suffix->TakeFocus(); }});

  auto components = Container::Vertical({input_prefix, input_suffix, button});

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
    return vbox({
        vbox({
            hbox({
                text("Prefix: "),
                input_prefix->Render() | size(WIDTH, EQUAL, 20),
            }),
            hbox({
                text("Suffix: "),
                input_suffix->Render() | size(WIDTH, EQUAL, 20),
            }),
        }),
        separator(),
        hbox({
            vbox(idx_arr),
            separator(),
            vbox(files_before_arr) | size(WIDTH, GREATER_THAN, 50),
            separator(),
            text("→"),
            separator(),
            vbox(idx_arr),
            separator(),
            vbox(files_after_arr) | size(WIDTH, GREATER_THAN, 50),
        }) | flex,
        hbox({
            color(Color::GrayDark, text(status)) | border | flex,
            button->Render(),
        }),

    });
  });

  screen.Loop(renderer);

  DirStruct dir_struct_renamed = {.base_path = dir_struct.base_path, .file_count = dir_struct.file_count};

  for (int i = 0; i < files.size(); i++)
  {
    auto file = files[i];
    auto new_file = get_file_name(file, prefix, suffix);
    dir_struct_renamed.files[i] = strdup(new_file.c_str());
  }

  return dir_struct_renamed;
}
