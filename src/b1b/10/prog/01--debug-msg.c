#include <stdio.h>

void print_on_debug(const char *msg)
{
#ifdef DEBUG
  printf("DEBUG: %s\n", msg);
#endif
}

int main(int argc, const char *argv[])
{

  print_on_debug("やっほー！");

  return 0;
}
