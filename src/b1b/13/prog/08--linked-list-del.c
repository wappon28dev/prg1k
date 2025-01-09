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

bool is_member_same_person(Member a, Member b)
{
  return strcmp(a.name, b.name) == 0;
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

Elem *insert_as_sorted_distinct(Elem *head, Member data)
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

  Elem *previous = NULL;
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
    previous = current;
    current = current->next;
  }

  if (current != NULL && is_member_same_person(current->data, data))
  {
    /*
     Member の名前が同じで, current が先頭の要素だったら, head を new_elem に置き換える
                                   +---+---+
                                   | 8 | *-+------+
                                   +---+---+      |
                                   new_elem       |
                    +---+---+               +---+-|-+
         NULL       | 8 | * +               | 10| *-+-----> ...
                    +---+---+               +---+---+
      previous       current              current->next
    */
    bool should_current_replaced = previous == NULL;
    if (should_current_replaced)
    {
      new_elem->next = current->next;
      free(current);
      return new_elem;
    }

    /*
      Member の名前が同じだったら, previous の next に new_elem を挿入する
                                   +---+---+
             --------------------->| 8 | *-+------+
            |                      +---+---+      |
            |                       new_elem       |
      +---+-|-+       +---+---+              +---+-|-+
      | 7 | * +       | 8 | *-+------------->| 10| *-+-----> ...
      +---+---+       +---+---+              +---+---+
      previous         current              current->next
    */
    new_elem->next = current->next;
    previous->next = new_elem;
    free(current);
    return head;
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

Elem *del_by(Elem *head, const char *name)
{
  /*
                 +---+---+      +---+---+
     NULL        | 7 | *-+----->| 10| *-+-----> ...
                 +---+---+      +---+---+
  current     current->next current->next->next

  del_by(head, 7);
                               +---+---+
     NULL          NULL        | 10| *-+-----> ...
                               +---+---+
  current     current->next current->next->next
*/
  while (head != NULL && strcmp(head->data.name, name) == 0)
  {
    Elem *next = head->next;
    free(head);
    head = next;
  }

  /*
    +---+---+      +---+---+      +---+---+
    | 4 | *-+----->| 7 | *-+----->| 10| *-+-----> ...
    +---+---+      +---+---+      +---+---+
    current     current->next current->next->next

    del_by(head, 7);
          +-----------------------------+
          |                             |
    +---+-|-+      +---+---+      +---+-|-+
    | 4 | * +      | 7 | *-+----->| 10| *-+-----> ...
    +---+---+      +---+---+      +---+---+
    current     current->next current->next->next
  */
  Elem *current = head;
  while (current != NULL && current->next != NULL)
  {
    if (strcmp(current->next->data.name, name) == 0)
    {
      Elem *next = current->next->next;
      free(current->next);
      current->next = next;
      return head;
    }
    current = current->next;
  }

  return head;
}

/// Main ///

int main(int argc, const char *argv[])
{
  Elem *head = NULL;

  head = insert_as_sorted_distinct(head, (Member){"Hyodo", 1.7, 70});
  head = insert_as_sorted_distinct(head, (Member){"Hyodo", 1.5, 70}); // 同じ名前のメンバー
  head = insert_as_sorted_distinct(head, (Member){"Akihisa", 1.8, 60});
  head = insert_as_sorted_distinct(head, (Member){"nasubi", 1.6, 80});

  head = del_by(head, "Akihisa");

  print_elem(head);

  free_all(head);

  return 0;
}
