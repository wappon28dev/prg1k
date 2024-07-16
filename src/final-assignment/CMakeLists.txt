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

add_executable(cook-zip-c main.c lib/ftxui/bindings.cpp)
target_link_libraries(cook-zip-c PRIVATE ftxui::component)
target_link_libraries(cook-zip-c PRIVATE ncurses)

enable_testing()

add_executable(my_test tests/test.c)
add_test(NAME MyTest COMMAND my_test)
