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
  char *name;
  float height;
  float weight;
  struct Elem *next;
} Elem;

Elem *prepend(Elem *head, char *name, float height, float weight)
{
  Elem *new_elem = malloc(sizeof(Elem));
  continue_or_handle_malloc_error(new_elem);

  new_elem->name = name;
  new_elem->height = height;
  new_elem->weight = weight;
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

int main(int argc, const char *argv[])
{
  Elem *head = NULL;

  free_all(head);

  return 0;
}
