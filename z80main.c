#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "z80config.h"
#include "z80cpu.h"
#include "z80opcodes.h"
#include "z80mem.h"
#include "z80debug.h"

void blank() {
  return;
}

int main(int argc, char const *argv[]) {
  populateJumpTable(instructionTable);

  printf("%s\n", instructionTable[0x00]->name);
  printf("%s\n", instructionTable[0x3E]->name);

#ifdef DEBUGGING
  FILE *log = debugInit();
#endif

  int running = 1;
  while (running) {
    running = 0;
  }

  return 0;
}
