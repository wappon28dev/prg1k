#pragma once

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"

#include <algorithm>
#include <iostream>

#include "../../dir.c"
#include "../../file.c"
#include "../../validate.c"
#include "../bindings.h"
#include "../utils.cpp"

using namespace ftxui;

ResultDirStruct cpp_ask_dir_struct_filter(DirStruct dir_struct)
{
  auto screen = ScreenInteractive::Fullscreen();

  std::string status;
  std::string file_content;
  auto files = dir_files_to_vector(dir_struct);
  sort(files.begin(), files.end());

  auto input_lists = Container::Vertical({});
  int focused_idx = 0;

  // NOTE: `std::vector<bool>` は特殊化されているため、`std::deque<bool>` を使う
  // ref:
  // https://zenn.dev/reputeless/books/standard-cpp-for-competitive-programming/viewer/vector#%E6%96%B9%E5%BC%8F-c%3A-std%3A%3Adeque%3Cbool%3E-%E3%81%A7%E4%BB%A3%E6%9B%BF%E3%81%99%E3%82%8B
  std::deque<bool> selected_arr(files.size(), false);

  for (int i = 0; i < 10; i++)
  {
    input_lists->Add(Checkbox(files[i], &selected_arr[i]));
  }

  auto button = Button("   NEXT >   ", [&] { screen.Exit(); });

  auto components = Container::Vertical({
      input_lists,
      button,
  });

  auto renderer = Renderer(components, [&] {
    for (int i = 0; i < (input_lists->ChildCount()); i++)
    {
      auto component = input_lists->ChildAt(i);
      auto path = std::string(dir_struct.base_path) + "/" + files[i];

      if (component->Focused())
      {
        auto r_content = get_file_content(path.c_str());

        if (r_content.err_message != NULL)
        {
          status = "🔧 Focused: `" + path + "`: invalid -> " + std::string(r_content.err_message);
          continue;
        }

        file_content = std::string(r_content.value);
        status = "🔧 Focused: `" + path + "`: " + std::to_string(file_content.length()) + " bytes";
        focused_idx = i;
        break;
      }
    }

    auto file_content_comp = [&] {
      std::vector<Element> lines;
      std::istringstream stream(file_content);
      std::string line;
      while (std::getline(stream, line))
      {
        lines.push_back(paragraphAlignLeft(line));
      }
      return lines;
    }();

    return vbox({hbox({
                     input_lists->Render() | vscroll_indicator | frame,
                     separator(),
                     vbox(file_content_comp) | vscroll_indicator | frame | flex,
                 }) | flex,
                 hbox({
                     color(Color::GrayDark, text(status)) | border | flex,
                     button->Render(),
                 })}) |
           border;
  });

  renderer |= CatchEvent([&](Event event) {
    if (event == Event::Character('q'))
    {
      screen.ExitLoopClosure()();
      return true;
    }

    if (event == Event::Character('a'))
    {
      bool is_fully_selected = std::all_of(selected_arr.begin(), selected_arr.end(), [](bool v) { return v; });

      for (int i = 0; i < files.size(); i++)
      {
        selected_arr[i] = !is_fully_selected;
      }
      return true;
    }

    if (event == Event::Return)
    {
      if (!button->Focused())
      {
        button->TakeFocus();
      }
      else
      {
        screen.Exit();
      }
      return true;
    }

    return false;
  });

  screen.Loop(renderer);

  std::vector<std::string> selected_files(files.size());
  int selected_files_count = 0;

  for (int i = 0; i < files.size(); i++)
  {
    if (selected_arr[i])
    {
      selected_files[selected_files_count] = files[i].c_str();
      selected_files_count++;
    }
  }

  return ResultDirStruct{
      .value =
          {
              .base_path = dir_struct.base_path,
              .files = (const char *)selected_files.data(),
              .file_count = selected_files_count,
          },
  };
}
