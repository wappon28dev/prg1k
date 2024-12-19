#include <stdio.h>

typedef struct Elem
{
  int data;
  struct Elem *next;
} Elem;

int main(int argc, const char *argv[])
{
  Elem *head = NULL;

  Elem l1 = {10, head};
  head = &l1;

  Elem l2 = {7, head};
  head = &l2;

  Elem l3 = {4, head};
  head = &l3;
  
  return 0;
}
