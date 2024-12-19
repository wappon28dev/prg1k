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

/// File ///

int load_elems_from_file(const char *file_name, Elem **head)
{
  FILE *fp = fopen(file_name, "r");
  continue_or_handle_file_error(fp, file_name);

  char line[LINE_MAX];
  int lines_len = 0;

  while (fgets(line, LINE_MAX, fp) != NULL)
  {
    *head = prepend(*head, atoi(line));
    lines_len++;
  }

  fclose(fp);
  return lines_len;
}

void write_elems_to_file(const char *file_name, const Elem *head)
{
  FILE *fp = fopen(file_name, "w");
  continue_or_handle_file_error(fp, file_name);

  const Elem *current = head;
  while (current != NULL)
  {
    fprintf(fp, "%d\n", current->data);
    current = current->next;
  }

  fclose(fp);
}

/// Main ///

int main(int argc, const char *argv[])
{
  const char *file_name = "assets/numlist.txt";

  Elem *head = NULL;
  int elems_len = load_elems_from_file(file_name, &head);

  while (true)
  {
    printf("操作を選択してください (a: 追加, d: 削除, p: 表示, q: 終了): ");
    char buf[256];
    fgets(buf, sizeof(buf), stdin);
    char input = '\0';
    int data = 0;
    int result = sscanf(buf, "%c %d", &input, &data);
    bool has_data = result == 2;

    Operation operation = get_operation_from_char(input);
    printf("%c: %s\n", operation.char_key, operation.name);
    printf("data: %d\n", data);

    switch (operation.key)
    {
    case ADD:
      if (!has_data)
      {
        printf("データが入力されていません\n");
        break;
      }
      head = prepend(head, data);
      break;
    case DEL:
      if (!has_data)
      {
        printf("データが入力されていません\n");
        break;
      }
      del_at(head, data);
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

  write_elems_to_file(file_name, head);

  free_all(head);

  return 0;
}
