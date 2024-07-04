#include <stdio.h>

#define MINIZ_HEADER_FILE_ONLY
#include "lib/miniz/miniz.c"

int main()
{

  const char *zipFileName = "test.zip";

  mz_zip_archive zip_archive;
  memset(&zip_archive, 0, sizeof(zip_archive));

  if (!mz_zip_writer_init_file_v2(&zip_archive, zipFileName, 0, 0))
  {
    printf("Failed to initialize zip writer\n");
    return -1;
  }

  const char *filename = "test.txt";
  const char *fileContents = "Hello, World!";

  if (!mz_zip_writer_add_mem(&zip_archive, filename, fileContents, strlen(fileContents), MZ_BEST_COMPRESSION))
  {
    printf("Failed to add file to zip\n");
    return -1;
  }

  if (!mz_zip_writer_finalize_archive(&zip_archive))
  {
    printf("Failed to finalize zip archive!\n");
    mz_zip_writer_end(&zip_archive);
    return -1;
  }

  mz_zip_writer_end(&zip_archive);

  printf("ZIP file created successfully!\n");
}
