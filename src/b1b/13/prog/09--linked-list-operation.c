#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN_MAX 128

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

/// `member.name` の free 忘れずに！！！
Member parse_from_str(const char *data)
{
  Member member = {NULL, 0, 0};
  member.name = malloc(NAME_LEN_MAX);
  continue_or_handle_malloc_error(member.name);
  sscanf(data, "%[^,],%f,%f", member.name, &member.height, &member.weight);
  return member;
}

/// Elem ///

typedef struct Elem
{
  Member member;
  struct Elem *next;
} Elem;

void print_elems(Elem *head)
{
  Elem *current = head;

  printf("    ");
  while (current != NULL)
  {
    print_member(current->member);
    printf(" -> ");
    current = current->next;
  }
  printf("NULL\n");
}

Elem *prepend(Elem *head, Member member)
{
  Elem *new_elem = malloc(sizeof(Elem));
  continue_or_handle_malloc_error(new_elem);

  new_elem->member = member;
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

Elem *insert_as_sorted_distinct(Elem *head, Member member)
{
  Elem *new_elem = malloc(sizeof(Elem));
  continue_or_handle_malloc_error(new_elem);

  new_elem->member = member;
  new_elem->next = NULL;

  if (head == NULL || is_member_sorted(member, head->member))
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
  while (current->next != NULL && is_member_sorted(current->next->member, member))
  {
    previous = current;
    current = current->next;
  }

  if (current != NULL && is_member_same_person(current->member, member))
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
  while (head != NULL && strcmp(head->member.name, name) == 0)
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
    if (strcmp(current->next->member.name, name) == 0)
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

/// Operation ///

typedef enum OperationKey
{
  ADD,
  DEL,
  PRINT,
  QUIT,
  UNKNOWN
} OperationKey;

typedef struct Operation
{
  OperationKey key;
  char char_key;
  const char *name;
} Operation;

const Operation __operation_map[] = {
    {ADD, 'a', "追加"}, {DEL, 'd', "削除"}, {PRINT, 'p', "表示"}, {QUIT, 'q', "終了"}, {UNKNOWN, '\0', "不明"},
};

Operation get_operation_from_key(const OperationKey key)
{
  int idx = 0;
  while (__operation_map[idx].key != UNKNOWN)
  {
    if (__operation_map[idx].key == key)
    {
      return __operation_map[idx];
    }
    idx++;
  }

  return __operation_map[idx]; // To be UNKNOWN
}

Operation get_operation_from_char(const char input)
{
  int idx = 0;
  while (__operation_map[idx].key != UNKNOWN)
  {
    if (__operation_map[idx].char_key == input)
    {
      return __operation_map[idx];
    }
    idx++;
  }

  return __operation_map[idx]; // To be UNKNOWN
}

/// Main ///

int main(int argc, const char *argv[])
{
  Elem *head = NULL;

  while (true)
  {
    printf("操作を選択してください (a: 追加, d: 削除, p: 表示, q: 終了): ");
    char buf[256];
    fgets(buf, sizeof(buf), stdin);
    char input = '\0';

    char data[NAME_LEN_MAX];
    int result = sscanf(buf, "%c %s", &input, data);

    bool has_data = result == 2;

    Operation operation = get_operation_from_char(input);
    printf("%c: %s\n", operation.char_key, operation.name);

    switch (operation.key)
    {
    case ADD:
      if (!has_data)
      {
        printf("データが入力されていません\n");
        break;
      }

      Member member = parse_from_str(data);
      print_member(member);

      head = insert_as_sorted_distinct(head, member);

      break;
    case DEL:
      if (!has_data)
      {
        printf("名前が入力されていません\n");
        break;
      }
      del_by(head, data);
      break;
    case PRINT:
      print_elems(head);
      break;
    case QUIT:
      break;
    case UNKNOWN:
      printf("不明な操作です\n");
      break;
    }

    if (operation.key == QUIT)
    {
      break;
    }
  }

  puts("---");
  print_elems(head);

  free_all(head);

  return 0;
}
