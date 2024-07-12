#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./lib/dir.c"
#include "./lib/types.c"
#include "./lib/zip.c"

#define MINIZ_HEADER_FILE_ONLY

int main()
{
  ResultDirStruct r_dir_files = get_dir_files("/Users/wataru/development/prg1k/src/13");

  if (r_dir_files.err_message != NULL)
  {
    fprintf(stderr, "ERROR: %s\n", r_dir_files.err_message);
    exit(EXIT_FAILURE);
  }

  DirStuct dir_struct = r_dir_files.value;

  ResultZipEntry r_zip_entry = create_zip_entry("output.zip", dir_struct);

  if (r_zip_entry.err_message != NULL)
  {
    fprintf(stderr, "ERROR: %s\n", r_zip_entry.err_message);
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < r_zip_entry.value.file_entry_count; i++)
  {
    printf("[%02d] %s\n", i, r_zip_entry.value.fileEntries[i].path);
    printf("%s\n", r_zip_entry.value.fileEntries[i].content);
  }

  return EXIT_SUCCESS;
}
