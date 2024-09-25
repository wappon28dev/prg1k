#include <stdio.h>

void p(char *s)
{
  printf("%s\n", s);
}

int main(int argc, char *argv[])
{

  p("    #    ");
  p("   # #   ");
  p("  #   #  ");
  p(" ####### ");
  p("#       #");

  return 0;
}
