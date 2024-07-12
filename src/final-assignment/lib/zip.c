#pragma once

#include <stdbool.h>

#include "./consts.c"
#include "./dir.c"
#include "./file.c"
#include "./miniz/miniz.c"
#include "./types.c"

#define MINIZ_HEADER_FILE_ONLY

ResultZipEntry create_zip_entry(const char *zip_file_name, DirStuct value)
{
  FileEntry file_entries[ARR_MAX] = {};

  for (int i = 0; i < value.file_count; i++)
  {
    char file_path[ARR_MAX];
    sprintf(file_path, "%s/%s", value.base_path, value.files[i]);

    ResultChar r_file_content = get_file_content(file_path);

    if (r_file_content.error_message != NULL)
    {
      fprintf(stderr, "ERROR: %s\n", r_file_content.error_message);
      exit(EXIT_FAILURE);
    }

    file_entries[i] = (FileEntry){
        .path = value.files[i],
        .content = r_file_content.value,
    };
  }

  ZipEntry zip_entry = {
      .zip_file_name = (char *)zip_file_name,
      .file_entry_count = value.file_count,
  };

  for (int i = 0; i < value.file_count; i++)
  {
    zip_entry.fileEntries[i] = file_entries[i];
  }

  return (ResultZipEntry){.value = zip_entry};
}

ResultVoid create_zip(ZipEntry zip_entry)
{
  mz_zip_archive zip_archive;
  memset(&zip_archive, 0, sizeof(zip_archive));

  bool init_result = mz_zip_writer_init_file_v2(&zip_archive, zip_entry.zip_file_name, 0, 0);
  if (!init_result)
  {
    return (ResultVoid){
        .err_message = "Failed to initialize zip writer",
    };
  }

  for (int i = 0; i < zip_entry.file_entry_count; i++)
  {
    char *filename = zip_entry.fileEntries[i].path;
    char *fileContents = zip_entry.fileEntries[i].content;

    bool writer_add_result =
        mz_zip_writer_add_mem(&zip_archive, filename, fileContents, strlen(fileContents), MZ_BEST_COMPRESSION);
    if (!writer_add_result)
    {
      return (ResultVoid){.err_message = "Failed to add file to zip"};
    }
  }

  bool finalize_result = mz_zip_writer_finalize_archive(&zip_archive);
  if (!finalize_result)
  {
    mz_zip_writer_end(&zip_archive);
    return (ResultVoid){
        .err_message = "Failed to finalize zip archive",
    };
  }

  mz_zip_writer_end(&zip_archive);
  printf("ZIP file created successfully!\n");
  return (ResultVoid){};
}
