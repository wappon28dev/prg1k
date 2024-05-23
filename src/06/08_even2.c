#include <stdio.h>

int main(int argc, char *argv[])
{
  int i = 0;
  for (;;)
  {
    printf("%d\n", i);

    i += 2;
    if (i > 10)
    {
      break;
    }
  }

  return 0;
}

// int main(int argc, char *argv[])
// {
//   int i = 0;
//   for (int i = 0; i < 10; i++)
//   {
//     if (i % 2 == 0)
//     {
//       printf("%d\n", i);
//     }

//     i++;
//   }
// }
