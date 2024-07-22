#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./lib/dir.c"
#include "./lib/ftxui/bindings.h"
#include "./lib/types.c"
#include "./lib/validate.c"
#include "./lib/zip.c"

#define MINIZ_HEADER_FILE_ONLY

ResultVoid _main()
{

  puts(LOGO);

  UserData user_data = cpp_ask_user_data();

  ResultDirStruct r_ask_dir_struct = get_dir_files(user_data.path);
  if (r_ask_dir_struct.err_message != NULL)
  {
    return (ResultVoid){.err_message = r_ask_dir_struct.err_message};
  }

  DirStruct dir_struct_filtered = cpp_ask_dir_struct_filtered(r_ask_dir_struct.value);
  for (int i = 0; i < dir_struct_filtered.file_count; i++)
  {
    printf("%s\n", dir_struct_filtered.files[i]);
  }

  DirStruct dir_struct_renamed = cpp_ask_dir_struct_renamed(dir_struct_filtered, user_data);

  return (ResultVoid){};
}

int main()
{

  ResultVoid result = _main();
  if (result.err_message != NULL)
  {
    handle_unhanded_error(result.err_message);
  }

  return EXIT_SUCCESS;
}
