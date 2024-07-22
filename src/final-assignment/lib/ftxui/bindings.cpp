#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"

#include <algorithm>
#include <iostream>

#include "../dir.c"
#include "../file.c"
#include "../validate.c"
#include "./bindings.h"

using namespace ftxui;

ResultUserData cpp_ask_user_data()
{
  auto screen = ScreenInteractive::TerminalOutput();

  std::string status;

  std::string student_id;
  bool is_valid_student_id = false;

  std::string path;
  bool is_valid_path = false;

  int selected = 0;

  std::vector<std::string> entries = {
      "演習問題 - 講義の中で行った問題のことだよ.",
      "課題, チャレンジ問題 - 問題詳細の最後のほうにある問題だよ.",
  };

  auto button = Button("   NEXT >   ", [&] { screen.Exit(); });
  auto input_path =
      Input(&path, "",
            InputOption{
                .multiline = false,
                .on_change =
                    [&] {
                      auto r_files = get_dir_files(path.c_str());
                      if (r_files.err_message != NULL)
                      {
                        is_valid_path = false;
                        status = "🔧 Path (" + path + "): invalid -> " + std::string(r_files.err_message);
                        return;
                      }

                      is_valid_path = r_files.value.file_count != 0;
                      status = "🔧 Path (" + path + "): valid -> count: " + std::to_string(r_files.value.file_count);
                    },
                .on_enter =
                    [&] {
                      if (is_valid_path)
                      {
                        button->TakeFocus();
                      }
                    },
            });

  auto submission_type = Menu(&entries, &selected,
                              MenuOption{
                                  .on_enter = [&] { input_path->TakeFocus(); },
                              });
  auto input_student_id =
      Input(&student_id, "",
            InputOption{
                .multiline = false,
                .on_change =
                    [&] {
                      auto r_validate = validate_student_id(student_id.c_str());

                      if (r_validate.err_message != NULL)
                      {
                        is_valid_student_id = false;
                        return;
                      }

                      if (student_id.length() != 0)
                      {
                        is_valid_student_id = r_validate.value;
                      }

                      status = "validate: " + student_id + " -> " + (is_valid_student_id ? "true" : "false");
                    },
                .on_enter =
                    [&] {
                      if (is_valid_student_id)
                      {
                        submission_type->TakeFocus();
                      }
                    },
            });

  auto component = Container::Vertical({
      input_student_id,
      submission_type,
      input_path,
      button,
  });

  // Tweak how the component tree is rendered:
  auto renderer = Renderer(component, [&] {
    auto input_student_id_message =
        student_id.length() == 0
            ? text("")
            : (is_valid_student_id ? color(Color::Green, text("✓ OK!: " + student_id))
                                   : color(Color::Red, text("✗ 正しい学籍番号を入力してください")));

    auto input_path_message = path.length() == 0
                                  ? text("")
                                  : (is_valid_path ? color(Color::Green, text("✓ OK!: " + path))
                                                   : color(Color::Red, text("✗ ディレクトリが存在しません")));
    return vbox({
               vbox(text("学籍番号: "), input_student_id->Render(), input_student_id_message),
               separator(),
               vbox(text("どんな提出物？:"), submission_type->Render()),
               separator(),
               vbox(text("ソースコードを含んだディレクトリを指定してください (Finder から D&D しても OK):"),
                    input_path->Render(), input_path_message),
               separator(),
               hbox(text("   "), button->Render()),
               separator(),
               color(Color::GrayDark, text(status)),
           }) |
           border;
  });

  screen.Loop(renderer);

  printf("student_id: %s\n", student_id.c_str());
  printf("selected: %d\n", selected);
  printf("path: %s\n", path.c_str());

  return (ResultUserData){.value = {.student_id = student_id.c_str(), .mode = (Mode)selected, .path = path.c_str()}};
}

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

ResultDirStruct cpp_ask_dir_struct(DirStruct dir_struct)
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
