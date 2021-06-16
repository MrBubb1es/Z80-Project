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
  populateJumpTable(instruction_table);
  Opcode_t *current_instruction;
#ifdef DEBUGGING
  FILE *log = debugInit();
#endif

  memory[1] = 0x3E;
  memory[2] = 0xFF;
  PC = 0;

  int running = 2;
  while (running) {
    current_instruction = instruction_table[read(memory, MEMSIZE, PC)];
    current_instruction->func();
    debugCycle(log);

    PC++;
    running--;
  }

  return 0;
}
