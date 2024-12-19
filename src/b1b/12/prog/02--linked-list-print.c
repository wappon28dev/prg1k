#include <stdio.h>

typedef struct Elem
{
  int data;
  struct Elem *next;
} Elem;

void print_elems(Elem *head)
{
  Elem *current = head;
  while (current != NULL)
  {
    printf("%d -> ", current->data);
    current = current->next;
  }
  printf("NULL\n");
}

int main(int argc, const char *argv[])
{
  Elem *head = NULL;

  Elem l1 = {10, head};
  head = &l1;

  Elem l2 = {7, head};
  head = &l2;

  Elem l3 = {4, head};
  head = &l3;

  print_elems(head);

  return 0;
}
