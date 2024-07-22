#include "../types.c"

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
