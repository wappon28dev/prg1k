#include <errno.h>
#include <stdbool.h>
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

/// Member ///

typedef struct Member
{
  char *name;
  float height;
  float weight;
} Member;

void print_member(Member member)
{
  printf("{name: %s, height: %.1f, weight: %.1f}\n", member.name, member.height, member.weight);
}

bool is_member_sorted(Member a, Member b)
{
  return strcmp(a.name, b.name) < 0;
}

/// Elem ///

typedef struct Elem
{
  Member data;
  struct Elem *next;
} Elem;

void print_elem(Elem *head)
{
  Elem *current = head;

  printf("    ");
  while (current != NULL)
  {
    print_member(current->data);
    printf(" -> ");
    current = current->next;
  }
  printf("NULL\n");
}

Elem *prepend(Elem *head, Member data)
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

Elem *insert_as_sorted(Elem *head, Member data)
{
  Elem *new_elem = malloc(sizeof(Elem));
  continue_or_handle_malloc_error(new_elem);

  new_elem->data = data;
  new_elem->next = NULL;

  if (head == NULL || is_member_sorted(data, head->data))
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
  while (current->next != NULL && is_member_sorted(current->next->data, data))
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

/// Main ///

int main(int argc, const char *argv[])
{
  Elem *head = NULL;

  head = insert_as_sorted(head, (Member){"Hyodo", 1.7, 70});
  head = insert_as_sorted(head, (Member){"Akihisa", 1.8, 60});
  head = insert_as_sorted(head, (Member){"nasubi", 1.6, 80});

  print_elem(head);

  free_all(head);

  return 0;
}
