#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Error Handlers ///

void continue_or_handle_malloc_error(const void *ptr)
{
  if (ptr == NULL)
  {
    fprintf(stderr, "メモリの確保に失敗しました: %s\n", strerror(errno));
    exit(1);
  }
}

/// Elem ///

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

Elem *prepend(Elem *head, int data)
{
  Elem *new_elem = malloc(sizeof(Elem));
  continue_or_handle_malloc_error(new_elem);

  new_elem->data = data;
  new_elem->next = head;
  return new_elem;
}

void free_all(Elem *head)
{
  Elem *current = head;
  while (current != NULL)
  {
    Elem *next = current->next;
    free(current);
    current = next;
  }
}

/// Main ///

int main(int argc, const char *argv[])
{
  Elem *head = NULL;

  head = prepend(head, 10);
  head = prepend(head, 7);
  head = prepend(head, 4);

  head = prepend(head, 2);

  print_elems(head);

  free_all(head);

  return 0;
}
