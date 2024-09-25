#include "../types.c"

/*
  このヘッダーファイルは C++ で記述した関数を C 側から呼ぶためのバインディングです.
  `cpp` から始まる関数は C から呼ばれることを想定しており, すべて TUI (Terminal based user interfaces)
  をユーザーに提供します.
  +------+      +-----------------+      +---------------+      +-----------------+
  |  C   |  <-  |   bindings.h    |  ->  | bindings.cpp  |  ->  |   ftxui::cpp    |
  +------+      +-----------------+      +---------------+      +-----------------+
    C に対して C++ の関数を公開                     |              TUI を提供するライブラリ群
                                                 |
  +-------+                                      |
  | regex | <------------------------------------+
  +-------+     C++ は C で記述した関数をバインディング無しで呼び出せる
*/
#ifdef __cplusplus
extern "C"
{
#endif

  UserData cpp_ask_user_data();
  DirStruct cpp_ask_dir_struct_filtered(DirStruct dir_struct);
  DirStruct cpp_ask_dir_struct_renamed(DirStruct dir_struct, UserData user_data);

#ifdef __cplusplus
}
#endif
