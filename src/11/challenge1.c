#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define LENGTH 100
#define IS_DEBUG false
#define SYM "<SYM>"

void splitWithSpace(char *paragraph, char terms[LENGTH][LENGTH])
{
  int paragraphLen = strlen(paragraph);

  char currentTermIdx = 0;
  char currentTermCharIdx = 0;
  char prevChar = '\0';
  for (int i = 0; i < paragraphLen; i++)
  {
    int termLen = strlen(terms[currentTermIdx]);
    char ch = paragraph[i];

    bool isSymbol = ch == ',' || ch == '.' || ch == '\0';
    bool needFinalize = ch == ' ';

    if (IS_DEBUG)
    {

      printf(
          " | [%2d] -> term[%2d][%2d]: %c\t prevChar: %c\t needFinalize: %d \t currentTerm: %s\n",
          i, currentTermIdx, currentTermCharIdx, ch, prevChar, needFinalize, terms[currentTermIdx]);
    }

    if (isSymbol)
    {
      currentTermIdx++;
      strcpy(terms[currentTermIdx], SYM);
      continue;
    }

    if (needFinalize)
    {
      currentTermIdx++;
      currentTermCharIdx = 0;

      terms[currentTermIdx][0] = '\0';

      continue;
    }

    {
      prevChar = ch;
      terms[currentTermIdx][currentTermCharIdx] = prevChar;
      currentTermCharIdx++;

      continue;
    }
  }
}

void dumpTerms(char terms[LENGTH][LENGTH])
{
  for (int i = 0; i < LENGTH; i++)
  {

    if (terms[i][0] == '\0')
    {
      return;
    }

    printf("terms[%d]: %s\n", i, terms[i]);
  }
}

int getTermIdx(char terms[LENGTH][LENGTH], char *searchTerm)
{
  for (int i = 0; i < LENGTH; i++)
  {
    if (strcmp(terms[i], searchTerm) == 0)
    {
      return i;
    }
  }

  return -1;
}

int getStrIdx(char terms[LENGTH][LENGTH], int termIdx)
{
  int strIdx = 0;

  for (int i = 0; i < termIdx; i++)
  {
    char *term = terms[i];
    bool isSymbol = strcmp(term, SYM) == 0;
    int termLen = strlen(term);
    bool isLast = i == termIdx - 1;

    strIdx += isSymbol ? 1 : termLen;

    if (!isLast)
    {
      strIdx++;
    }
  }
  return strIdx;
}

int indexOf(char *paragraph, char *searchTerm)
{
  char terms[LENGTH][LENGTH] = {'\0'};
  splitWithSpace(paragraph, terms);

  int termIdx = getTermIdx(terms, searchTerm);

  if (IS_DEBUG)
  {
    printf("termIdx: %d\n", termIdx);
    dumpTerms(terms);
  }

  if (termIdx == -1)
  {
    return -1;
  }

  int strIdx = getStrIdx(terms, termIdx);

  if (IS_DEBUG)
  {
    printf("strIdx: %d\n", strIdx);
  }

  return strIdx;
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
