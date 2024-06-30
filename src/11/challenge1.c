#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define LENGTH 100

int indexOf(char *paragraph, char *searchTerm)
{
  int paragraphLength = strlen(paragraph);
  int searchTermLength = strlen(searchTerm);

  for (int i = 0; i < paragraphLength; i++)
  {
    if (paragraph[i] == searchTerm[0])
    {
      bool isMatch = true;
      for (int j = 1; j < searchTermLength; j++)
      {
        if (paragraph[i + j] != searchTerm[j])
        {
          isMatch = false;
          break;
        }
      }

      if (isMatch)
      {
        return i;
      }
    }
  }

  return -1;
}

int main(int argc, char *argv[])
{
  char paragraph[] =
      "we hold these truths to be self-evident, that all men are created "
      "equal, that they are endowed by their creator with certain unalienable "
      "rights, that among these are life, liberty and the pursuit of "
      "happiness.";
  char searchTerm[LENGTH] = {'\0'};

  printf("searchTerm: ");
  scanf("%s", searchTerm);

  printf("indexOf: %d\n", indexOf(paragraph, searchTerm));

  return 0;
}
