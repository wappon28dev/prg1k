#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./lib/dir.c"
#include "./lib/types.c"
#include "./lib/zip.c"

#define MINIZ_HEADER_FILE_ONLY

ResultVoid _main()
{
  ResultDirStruct r_dir_files = get_dir_files("/Users/wataru/development/prg1k/src/13");

  if (r_dir_files.err_message != NULL)
  {
    return (ResultVoid){.err_message = r_dir_files.err_message};
  }

  ResultZipEntry r_zip_entry = create_zip_entry("output.zip", r_dir_files.value);

  if (r_zip_entry.err_message != NULL)
  {
    return (ResultVoid){.err_message = r_zip_entry.err_message};
  }

  ResultVoid r_zip = create_zip(r_zip_entry.value);

  puts("Success!");

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
