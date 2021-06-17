#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "z80config.h"
#include "z80error.h"
#include "z80mem.h"
#include "z80cpu.h"
#include "z80opcodes.h"
#include "z80debug.h"


int main(int argc, char const *argv[]) {

  // Fill instruction jump table
  populateJumpTable(instruction_table);
  Opcode_t *current_instruction;
#ifdef DEBUGGING
  FILE *log = debugInit();
#endif

  memory[1] = 0x3E;
  memory[2] = 0xFF;
  memory[3] = 0xC6;
  memory[4] = 0x01;

  memory[6] = 0xC1;

  memory[0xFFFD] = 0x11;
  memory[0xFFFE] = 0xDD;

  H = 0xFF;
  L = 0xFF;

  SP = 0xFFFD;
  PC = 0;
  int instruction;

  int running = 1;
  while (running) {
    instruction = read(memory, MEMSIZE, PC);
    current_instruction = instruction_table[instruction];
    current_instruction->func();
    debugCycle(log);

    PC += current_instruction->bytes;

    if (PC > 25) {
      running = 0;
    }
  }

  fclose(log);

  return 0;
}
