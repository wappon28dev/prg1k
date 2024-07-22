# コンパイル方法

# ZIP の作成には miniz というポータブルライブラリを使用しています. (`/lib/miniz` に格納しています.)
# C と C++ とのバインディングについては, `lib/ftxui/bindings.h` を参照してください.
# TUI の提供には, ftxui という C++ のライブラリを使用しており, CMake を用いてコンパイルします.
# または, Linux と macOS 用に既にコンパイル済みのバイナリを `bin` ディレクトリーに格納しています. (`chmod` などで実行権限を与えてください.)
# 試しに実行する際, `/sample` ディレクトリーにサンプルファイルがあるので, それを使ってみてください.

# ```bash
# mkdir build
# cmake -S . -B ./build 
# cmake --build ./build --target cook-zip-c
# ./build/cook-zip-c
# ```


cmake_minimum_required(VERSION 3.5.0)
project(cook-zip-c VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v5.0.0
  GIT_PROGRESS   TRUE
  GIT_SHALLOW    TRUE
  EXCLUDE_FROM_ALL
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_executable(cook-zip-c 15_issue_k24132.c lib/ftxui/bindings.cpp)
target_link_libraries(cook-zip-c PRIVATE ftxui::component)
