#include "foxui.h"

int main(int, char**)
{
  FoxUI interf(800,500);

  while (interf.isAlive())
  {
    interf.runUI();
  }

  return 0;
}
