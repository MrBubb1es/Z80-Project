#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "z80cpu.h"
#include "z80opcodes.h"
#include "z80mem.h"



int main(int argc, char const *argv[]) {
  int running = 1;

  while (running) {

#ifdef DEBUGGING
  debugCycle();
#endif

  clock();


  }

  A=0;
  printf("%d\n", fetch(memory, MEMSIZE, 255));
  printf("%d\n", fetch(memory, MEMSIZE, 755));


  return A;
}
