#include "../types.c"

#ifdef __cplusplus
extern "C"
{
#endif

  ResultVoid cpp_function();
  ResultVoid print_text(char *body);
  ResultUserData cpp_ask_user_data();
  ResultDirStruct cpp_ask_dir_struct(DirStruct dir_struct);

#ifdef __cplusplus
}
#endif
