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

  // Fill instruction jump tables
  populateInstructionTable(instruction_table);
  populateEXTDInstructionTable(EXTD_instruction_table);
  Opcode_t *current_instruction;

#ifdef DEBUGGING
  FILE *log = debugInit();
#endif

  memory[1] = 0xDE;
  memory[2] = 0xA0;

  memory[0xFFFF] = 0x22;

  B = 0x00;
  C = 0x01;

  D = 0x10;
  E = 0x00;

  H = 0xFF;
  L = 0xFF;

  PC = 0;
  int instruction;

  int running = 1;
  while (running) {
    instruction = read(memory, MEMSIZE, PC);

    // Takes care of opcodes not found in the standard instruction table
    switch (instruction) {
      case 0xDE:
        current_instruction = EXTD_instruction_table[read(memory, MEMSIZE, PC + 1)];
        break;
      default:
        current_instruction = instruction_table[instruction];
        break;
    }

    current_instruction->func();

    debugCycle(log);

    PC += current_instruction->bytes;

    if (PC > 3) {
      running = 0;
    }
  }

  printf("%X\n", read(memory, MEMSIZE, 0xFFFF));
  printf("%X\n", read(memory, MEMSIZE, 0x1000));

  fclose(log);

  return 0;
}
