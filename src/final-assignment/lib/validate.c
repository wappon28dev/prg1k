#pragma once

#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "./types.c"

ResultBool regex_match(const char *expr, const char *text)
{
  regex_t regex;
  int regex_result;
  char msgbuf[100];

  regex_result = regcomp(&regex, expr, 0);
  if (regex_result)
  {
    return (ResultBool){.err_message = "Could not compile regex"};
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
    ResultBool result = regex_match(pattern, filePaths[i]);
    if (!result.value)
    {
      return false;
    }
  }
  return true;
}

char *get_prefix(const char *src, const char **filePaths, int length)
{
  char *last_segment = get_last_segment(src);
  if (all_match(filePaths, length, "^\\d{2}_\\d{2}_"))
  {
    return NULL;
  }
  ResultBool result = regex_match("^\\d{2}$", last_segment);
  if (result.value)
  {
    char *prefix = (char *)malloc(strlen(last_segment) + 2);
    snprintf(prefix, strlen(last_segment) + 2, "%s_", last_segment);
    return prefix;
  }
  return NULL;
}

char *get_suffix(const char **filePaths, int length, const char *mode, const char *name)
{
  if (strcmp(mode, "issues") != 0)
  {
    return NULL;
  }
  if (all_match(filePaths, length, "_k\\d{5}.c$"))
  {
    return NULL;
  }
  char *suffix = (char *)malloc(strlen(name) + 2);
  snprintf(suffix, strlen(name) + 2, "_%s", name);
  return suffix;
}

ResultBool validate_student_id(const char *student_id)
{
  return regex_match("^k2[0-9][0-9][0-9][0-9]$", student_id);
}
