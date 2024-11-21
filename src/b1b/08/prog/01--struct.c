// cspell:disable
#include <stdio.h>

typedef struct Student
{
  char name[20];
  int age;
  char id[1 + 5 + 1];
  int grade;
} Student;

int main(int argc, char *argv[])
{
  Student students[3] = {
      {"hyodo", 18, "K24123", 1},
      {"Akihisa", 19, "K24137", 1},
      {"nasubi", 19, "K24083", 1},
  };
  int students_len = sizeof(students) / sizeof(students[0]);

  puts("名前\t年齢\t学籍番号\t学年");
  puts("----\t----\t--------\t----");
  for (int i = 0; i < students_len; i++)
  {
    Student student = students[i];
    printf("%s\t%d\t%s\t学部 %d 年\n", student.name, student.age, student.id, student.grade);
  }

  return 0;
}
