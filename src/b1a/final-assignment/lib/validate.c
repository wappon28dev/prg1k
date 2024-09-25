#pragma once

#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./types.c"

ResultBool regex_match(const char *text, const char *expr)
{
  regex_t regex;
  int regex_result;
  char msgbuf[100];

  regex_result = regcomp(&regex, expr, 0);
  if (regex_result)
  {
    return (ResultBool){.err_message = "regex_match: Could not compile regex"};
  }

  regex_result = regexec(&regex, text, 0, NULL, 0);

  switch (regex_result)
  {
  case false:
    return (ResultBool){.value = true};
  case REG_NOMATCH:
    return (ResultBool){.value = false};
  default:
    regerror(regex_result, &regex, msgbuf, sizeof(msgbuf));
    return (ResultBool){.err_message = msgbuf};
  }

  regfree(&regex);
}

char *get_last_segment(const char *src)
{
  char *token, *last = NULL;
  char *src_copy = strdup(src);
  token = strtok(src_copy, "/");
  while (token != NULL)
  {
    last = token;
    token = strtok(NULL, "/");
  }
  return last;
}

bool all_match(const char **filePaths, int length, const char *pattern)
{
  for (int i = 0; i < length; i++)
  {
    ResultBool result = regex_match(filePaths[i], pattern);
    if (!result.value)
    {
      return false;
    }
  }
  return true;
}

char *get_prefix(DirStruct dir_struct)
{
  static char prefix[10];

  int all_files_match = true;
  for (int i = 0; i < dir_struct.file_count; i++)
  {
    if (!regex_match(dir_struct.files[i], "^\\d{2}_\\d{2}_").value)
    {
      all_files_match = false;
      break;
    }
  }

  if (all_files_match)
  {
    return NULL;
  }

  const char *last_file = dir_struct.files[dir_struct.file_count - 1];
  const char *last_segment = strrchr(dir_struct.base_path, '/');
  if (last_segment)
  {
    last_segment++;
  }
  else
  {
    last_segment = last_file;
  }

  if (regex_match(last_segment, "^\\d{2}$").value)
  {
    snprintf(prefix, sizeof(prefix), "%s_", last_segment);
    return prefix;
  }

  return NULL;
}

char *get_suffix(DirStruct dir_struct, UserData user_data)
{
  static char suffix[10];

  if (user_data.mode != ISSUES)
  {
    return NULL;
  }

  int all_files_match = 1;
  for (int i = 0; i < dir_struct.file_count; i++)
  {
    if (!regex_match(dir_struct.files[i], "_k\\d{5}\\.c$").value)
    {
      all_files_match = 0;
      break;
    }
  }

  if (all_files_match)
  {
    return NULL;
  }

  snprintf(suffix, sizeof(suffix), "_%s", user_data.student_id);
  return suffix;
}

ResultBool validate_student_id(const char *student_id)
{
  return regex_match(student_id, "^k2[0-9][0-9][0-9][0-9]$");
}
