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

// Jump table of all normal opcodes
Opcode_t *instruction_table[256];
// All extended opcodes
Opcode_t *EXTD_instruction_table[96];

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

// Nothing happens
void NOP() {
  printf("NOP\n");
  return;
}

// Store next byte in A register
void LD_A_N() {
  printf("LD_A_N\n");
  A = read(memory, MEMSIZE, PC + 1);
}

// Push the contents of BC onto the stack
void PUSH_BC() {
  printf("PUSH_BC\n");

  write(memory, MEMSIZE, --SP, B);
  write(memory, MEMSIZE, --SP, C);
}

// Pop off the stack and store the contents in BC
void POP_BC() {
  printf("POP_BC\n");

  C = read(memory, MEMSIZE, SP++);
  B = read(memory, MEMSIZE, SP++);
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

// Swap register pairs BC, DE, and HL with each of their secondary counterparts
void EXX() {
  printf("EXX\n");

  int temp = B;
  B = B2;
  B2 = temp;

  temp = C;
  C = C2;
  C2 = temp;

  temp = D;
  D = D2;
  D2 = temp;

  temp = E;
  E = E2;
  E2 = temp;

  temp = H;
  H = H2;
  H2 = temp;

  temp = L;
  L = L2;
  L2 = temp;
}

// Exchange the contents of register pairs DE and HL
void EX_DE_HL() {
  printf("EX_DE_HL\n");

  int temp = D;
  D = H;
  H = temp;

  temp = E;
  E = L;
  L = temp;
}

// Load the contents of HL onto the stack pointer
void LD_SP_HL() {
  printf("LD_SP_HL\n");

  SP = (H << 8) | L;
}



/*  EXTENDED OPCODES  */
// Write the contents of memory at address HL to address DE
void LDI() {
  printf("LDI\n");
  write(memory, MEMSIZE, (D << 8) | E, read(memory, MEMSIZE, (H << 8) | L));

  // Increment HL and DE registers
  uint16_t temp = ((H << 8) | L) + 1;
  H = (temp & 0xFF00) >> 8;
  L = (temp & 0x00FF);

  temp = ((D << 8) | E) + 1;
  D = (temp & 0xFF00) >> 8;
  E = (temp & 0x00FF);

  // Decrement BC register
  temp = ((B << 8) | C) - 1;
  B = (temp & 0xFF00) >> 8;
  C = (temp & 0x00FF);

  setFlagBit(HALF_CARRY, 0);
  setFlagBit(OVERFLOW, ((B << 8) | C) == 0);
  setFlagBit(ADD_SUBTRACT, 0);
}

// Set the Z bit is A is equal to the byte in memory found at HL
void CPI() {
  setFlagBit(ZERO, A == read(memory, MEMSIZE, (H << 8) | L));

  uint16_t temp = ((B << 8) | C) - 1;
  // Set S if the result is negative
  setFlagBit(SIGN, (A & 0x80) >> 7);
  // Set H if there is a borrow from bit 4
  setFlagBit(HALF_CARRY, (temp & 0x000F) <= 1);
  // Set P/V if BC - 1 != 0, else reset
  setFlagBit(OVERFLOW, temp - 1 == 0);
  setFlagBit(ADD_SUBTRACT, 1);

  B = (temp & 0xFF00) >> 8;
  C = temp & 0x00FF;

  temp = ((H << 8) | L) + 1;
  H = (temp & 0xFF00) >> 8;
  L = temp & 0x00FF;
}


void populateInstructionTable(Opcode_t *table[]) {

  table[0x00] = newOpcode("NOP",      "NONE",  4, 1, &NOP);

  table[0x3E] = newOpcode("LD A",     "IMM",   2, 2, &LD_A_N);

  table[0xC1] = newOpcode("POP BC",   "REG",   3, 1, &POP_BC);

  table[0xC5] = newOpcode("PUSH BC",  "REG",   3, 1, &PUSH_BC);

  table[0xC6] = newOpcode("ADD A",    "IMM",   2, 2, &ADD_A_N);

  table[0xD9] = newOpcode("EXX",      "REG",   1, 1, &EXX);

  // No opcode required for EXTD (0xDE) opcodes, that
  // is handled by the switch case in the main loop.

  table[0xEB] = newOpcode("EX DE HL", "REG",   1, 1, &EX_DE_HL);

  table[0xF9] = newOpcode("LD SP HL", "REG",   1, 1, &LD_SP_HL);
}

void populateEXTDInstructionTable(Opcode_t *table[]) {
  table[0xA0] = newOpcode("LDI",      "REG",   4, 2, &LDI);
  table[0xA1] = newOpcode("CPI",      "REG",   4, 2, &CPI);
}

#endif
