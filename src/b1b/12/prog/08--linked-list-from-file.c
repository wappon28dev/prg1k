#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 256

/// Error Handlers ///

void continue_or_handle_malloc_error(const void *ptr)
{
  if (ptr == NULL)
  {
    fprintf(stderr, "メモリの確保に失敗しました: %s\n", strerror(errno));
    exit(1);
  }
}

void continue_or_handle_file_error(const FILE *fp, const char *file_name)
{
  if (fp == NULL)
  {
    fprintf(stderr, "ファイル (`%s`) を開けませんでした: %s\n", file_name, strerror(errno));
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

Elem *insert_sorted(Elem *head, int data)
{
  Elem *new_elem = malloc(sizeof(Elem));
  continue_or_handle_malloc_error(new_elem);

  new_elem->data = data;
  new_elem->next = NULL;

  if (head == NULL || data < head->data)
  {
    new_elem->next = head;
    return new_elem;
  }

  Elem *current = head;
  /*
            +---+---+
            | 8 | *-+---> NULL
            +---+---+
             new_elem

    +---+---+      +---+---+
    | 4 | *-+----->| 7 | *-+-----> ...
    +---+---+      +---+---+
     current      current->next
  */
  while (current->next != NULL && current->next->data < data)
  {
    current = current->next;
  }

  /*
                    +---+---+
            +------>| 8 | *-+------+
            |       +---+---+      |
            |       new_elem       |
      +---+-|-+              +---+-|-+
      | 7 | * +              | 10| *-+-----> ...
      +---+---+              +---+---+
      current               current->next
  */
  new_elem->next = current->next;
  current->next = new_elem;

  return head;
}

void del_at(Elem *head, int index)
{
  if (index < 0 || head == NULL)
  {
    printf("無効なインデックスです\n");
    return;
  }

  if (index == 0)
  {
    Elem *next = head->next;
    free(head);
    head = next;
    return;
  }

  Elem *current = head;
  for (int i = 0; i < index - 1; i++)
  {
    current = current->next;
  }

  /*
    +---+---+      +---+---+      +---+---+
    | 4 | *-+----->| 7 | *-+----->| 10| *-+-----> ...
    +---+---+      +---+---+      +---+---+
     current     current->next current->next->next
   (index - 1)      (index)       (index + 1)

   del_at(head, index)
          +-----------------------------+
          |                             |
    +---+-|-+      +---+---+      +---+-|-+
    | 4 | * +      | 7 | *-+----->| 10| *-+-----> ...
    +---+---+      +---+---+      +---+---+
     current     current->next current->next->next
   (index - 1)      (index)       (index + 1)
  */
  Elem *next = current->next->next;
  free(current->next);
  current->next = next;
}

/// File ///

int load_elems_from_file(const char *file_name, Elem **head)
{
  FILE *fp = fopen(file_name, "r");
  continue_or_handle_file_error(fp, file_name);

  char line[LINE_MAX];
  int lines_len = 0;

  while (fgets(line, LINE_MAX, fp) != NULL)
  {
    *head = insert_sorted(*head, atoi(line));
    lines_len++;
  }

  fclose(fp);
  return lines_len;
}

/// Main ///

int main(int argc, const char *argv[])
{
  const char *file_name = "assets/numlist.txt";

  Elem *head = NULL;
  int elems_len = load_elems_from_file(file_name, &head);

  print_elems(head);

  free_all(head);

  return 0;
}
