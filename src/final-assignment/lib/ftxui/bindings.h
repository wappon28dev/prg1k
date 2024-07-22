#include "../types.c"

#ifdef __cplusplus
extern "C"
{
#endif

  ResultUserData cpp_ask_user_data();
  ResultDirStruct cpp_ask_dir_struct_filter(DirStruct dir_struct);
  ResultDirStruct cpp_ask_dir_struct_renaming(DirStruct dir_struct, UserData user_data);

#ifdef __cplusplus
}
#endif
