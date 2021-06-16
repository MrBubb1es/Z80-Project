#ifndef Z80OPCODES_H
#define Z80OPCODES_H

#include <stdint.h>
#include <stdlib.h>

#include "z80error.h"
#include "z80cpu.h"

typedef struct {
  char *name;
  int cycles;
  int bytes;
  void (*func)();
} Opcode_t;

// Jump table of all opcodes
Opcode_t *instructionTable[2];

// Constructor method for Opcode_t struct
//   name - used for logging, the name doesn't affect the function of the instruction
//   cycles - the number of clock cycles the cpu takes to execute the instruction
//   bytes - the total length of the instruction in memory
//   func - the function the instruction calls when it is executed
Opcode_t *newOpcode(char *name, int cycles, int bytes, void (*func)()) {
  Opcode_t *new_instruction = malloc(sizeof(Opcode_t));
  new_instruction->name = name;
  new_instruction->cycles = cycles;
  new_instruction->bytes = bytes;
  new_instruction->func = func;
  return new_instruction;
}


void invalidInstruction() {
  error("tried to execute illegal opcode", ILLEGAL_OPCODE);
}


void NOP() {
  return;
}

void LD_A_N() {
  // Store next byte in A register
  A = read(memory, MEMSIZE, PC + 1);
}


void populateJumpTable(Opcode_t *table[]) {

  table[0x00] = newOpcode("NOP", 4, 1, &NOP);
  table[0x3E] = newOpcode("LD A, ", 2, 2, &LD_A_N);

}


#endif
