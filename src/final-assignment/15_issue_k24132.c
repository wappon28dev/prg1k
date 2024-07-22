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
  DirStruct dir_struct_renamed = cpp_ask_dir_struct_renamed(dir_struct_filtered, user_data);

  ResultChar r_make_dir_in_tmp = make_dir_in_tmp();
  if (r_make_dir_in_tmp.err_message != NULL)
  {
    return (ResultVoid){.err_message = r_make_dir_in_tmp.err_message};
  }

  char *zip_file_path;
  const char *dir_name = get_dir_name(user_data);
  asprintf(&zip_file_path, "%s/%s.zip", r_make_dir_in_tmp.value, dir_name);

  printf("`%s` に `%s` を作成中...\n", r_make_dir_in_tmp.value, dir_name);

  ResultZipEntry r_create_zip_entry = create_zip_entry(zip_file_path, dir_struct_filtered, dir_struct_renamed.files);
  if (r_create_zip_entry.err_message != NULL)
  {
    return (ResultVoid){.err_message = r_create_zip_entry.err_message};
  }

  printf("`%s` にファイルを書き込み中...\n", zip_file_path);

  ResultVoid r_create_zip = create_zip(r_create_zip_entry.value);
  if (r_create_zip.err_message != NULL)
  {
    return (ResultVoid){.err_message = r_create_zip.err_message};
  }

  printf("正常に Zip ファイル `%s` が作成されました\n", zip_file_path);
  open_path(zip_file_path);

  return (ResultVoid){};
}

int main()
{

  ResultVoid result = _main();
  if (result.err_message != NULL)
  {
    handle_unexpected_error(result.err_message);
  }

  return EXIT_SUCCESS;
}
