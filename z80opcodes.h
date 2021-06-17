#ifndef Z80OPCODES_H
#define Z80OPCODES_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "z80config.h"
#include "z80error.h"
#include "z80cpu.h"

typedef struct {
  char *name;
  char *addressing_mode;
  int cycles;
  int bytes;
  void (*func)();
} Opcode_t;

// Jump table of all opcodes
Opcode_t *instruction_table[256];

// Constructor method for Opcode_t struct
//   name - used for logging, the name doesn't affect the function of the instruction
//   cycles - the number of clock cycles the cpu takes to execute the instruction
//   bytes - the total length of the instruction in memory
//   func - the function the instruction calls when it is executed
Opcode_t *newOpcode(char *name, char *addressing_mode, int cycles, int bytes, void (*func)()) {
  Opcode_t *new_instruction = malloc(sizeof(Opcode_t));
  new_instruction->name = name;
  new_instruction->addressing_mode = addressing_mode;
  new_instruction->cycles = cycles;
  new_instruction->bytes = bytes;
  new_instruction->func = func;
  return new_instruction;
}


void invalidInstruction() {
  error("tried to execute illegal opcode", ILLEGAL_OPCODE);
}


void NOP() {
  printf("NOP\n");
  return;
}

// Store next byte in A register
void LD_A_N() {
  printf("LD_A_N\n");
  A = read(memory, MEMSIZE, PC + 1);
}

// Add the next byte to A
void ADD_A_N() {
  printf("ADD_A_N\n");
  // get next byte in memory
  uint8_t next_byte = read(memory, MEMSIZE, PC + 1);
  uint8_t result = A + next_byte;

  int half_carry = ((A & 0xF) + (next_byte & 0xF)) >> 4;
  int carry = (A + next_byte) >> 8;

  // Set S if the result is negative
  setFlagBit(SIGN, result & 0x80 >> 7);
  // Set Z if result is 0
  setFlagBit(ZERO, result == 0);
  // Set H if carry from bit 3
  setFlagBit(HALF_CARRY, half_carry);
  // Set P/V if overflow
  setFlagBit(OVERFLOW, result < A);
  // Reset N
  setFlagBit(ADD_SUBTRACT, 0);
  // Set C if carry from bit 7
  setFlagBit(CARRY, carry);

  A += next_byte;
}

void PUSH_BC() {
  printf("PUSH_BC\n");

  write(memory, MEMSIZE, --SP, B);
  write(memory, MEMSIZE, --SP, C);
}

void POP_BC() {
  printf("POP_BC\n");

  C = read(memory, MEMSIZE, SP++);
  B = read(memory, MEMSIZE, SP++);
}

void LD_SP_HL() {
  printf("LD_SP_HL\n");

  SP = (H << 8) | L;
}

void populateJumpTable(Opcode_t *table[]) {

  table[0x00] = newOpcode("NOP",      "NONE",  4, 1, &NOP);

  table[0x3E] = newOpcode("LD A",     "IMM",   2, 2, &LD_A_N);

  table[0xC1] = newOpcode("POP BC",   "REG",   3, 1, &POP_BC);

  table[0xC5] = newOpcode("PUSH BC",  "REG",   3, 1, &PUSH_BC);

  table[0xC6] = newOpcode("ADD A",    "IMM",   2, 2, &ADD_A_N);

  table[0xF9] = newOpcode("LD SP HL", "REG",   1, 1, &LD_SP_HL);
}


#endif
