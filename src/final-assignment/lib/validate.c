#include <regex.h>
#include <stdbool.h>
#include <stdio.h>

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

ResultBool validate_student_id(const char *student_id)
{
  return regex_match("^k2[0-9][0-9][0-9][0-9]$", student_id);
}
