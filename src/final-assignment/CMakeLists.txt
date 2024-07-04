cmake_minimum_required(VERSION 3.5.0)
project(cook-zip-c VERSION 0.1.0 LANGUAGES C)

add_executable(cook-zip-c main.c)
target_link_libraries(cook-zip-c ncurses)

include(CTest)
enable_testing()

add_executable(my_test tests/test.c)
add_test(NAME MyTest COMMAND my_test)
