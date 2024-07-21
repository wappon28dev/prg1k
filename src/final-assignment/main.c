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

  // ResultUserData r_ask_user_data = cpp_ask_user_data();

  // if (r_ask_user_data.err_message != NULL)
  // {
  //   return (ResultVoid){.err_message = r_ask_user_data.err_message};
  // }

  // ResultDirStruct r_ask_dir_struct = get_dir_files(r_ask_user_data.value.path);
  ResultDirStruct r_ask_dir_struct = get_dir_files("/workspaces");

  if (r_ask_dir_struct.err_message != NULL)
  {
    return (ResultVoid){.err_message = r_ask_dir_struct.err_message};
  }

  r_ask_dir_struct = cpp_ask_dir_struct(r_ask_dir_struct.value);

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
