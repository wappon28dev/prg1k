#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"
#include <iostream>

#include "../dir.c"
#include "../validate.c"
#include "./bindings.h"

using namespace ftxui;

ResultVoid print_text(char *body)
{
  auto document = text(body);

  auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
  Render(screen, document);

  std::cout << screen.ToString() << '\0' << std::endl;
  return (ResultVoid){};
}

ResultVoid cpp_function()
{

  auto screen = ScreenInteractive::TerminalOutput();

  std::vector<std::string> entries = {
      "PULL: 受信",
      "PUSH: 送信",
  };
  int selected = 0;

  MenuOption option;
  option.on_enter = screen.ExitLoopClosure();
  auto menu = Menu(&entries, &selected, option);

  screen.Loop(menu);

  std::cout << "mode = " << selected << std::endl;

  return (ResultVoid){};
}

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

  return (ResultUserData){.value = {.student_id = student_id.c_str(), .mode = (Mode)selected, .path = path.c_str()}};
}

ResultDirStruct cpp_ask_dir_struct(DirStruct dir_struct)
{
  auto screen = ScreenInteractive::TerminalOutput();

  auto component = Container::Vertical({});

  auto renderer = Renderer(component, [&] {
    return hbox({
               text("left-column"),
               separator(),
               vbox({
                   center(text("top")) | flex,
                   separator(),
                   center(text("bottom")),
               }) | flex,
               separator(),
               text("right-column"),
           }) |
           border;
  });

  screen.Loop(renderer);

  return ResultDirStruct{
      .value = dir_struct,
  };
}
