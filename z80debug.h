#ifndef Z80DEBUG_H
#define Z80DEBUG_H

#include <stdint.h>
#include <stdio.h>

#include "z80config.h"
#include "z80error.h"
#include "z80cpu.h"
#include "z80opcodes.h"


FILE *debugInit() {
  FILE *log = NULL;
  log = fopen("z80log.txt", "w");

  if (!log) {
    error("Failed to open log file z80log.txt", DEBUG_FILE_DOES_NOT_EXIST);
  }

  return log;
}

// Log cpu registers
void logReg(FILE *log) {
  fprintf(log, "CPU Registers:\n");
  fprintf(log, "  A = %X\n", A);
  fprintf(log, "  F = %X\n", F);
  fprintf(log, "  B = %X\n", B);
  fprintf(log, "  C = %X\n", C);
  fprintf(log, "  D = %X\n", D);
  fprintf(log, "  E = %X\n", E);
  fprintf(log, "  H = %X\n", H);
  fprintf(log, "  L = %X\n\n", L);

  fprintf(log, "  A2 = %X\n", A2);
  fprintf(log, "  F2 = %X\n", F2);
  fprintf(log, "  B2 = %X\n", B2);
  fprintf(log, "  C2 = %X\n", C2);
  fprintf(log, "  D2 = %X\n", D2);
  fprintf(log, "  E2 = %X\n", E2);
  fprintf(log, "  H2 = %X\n", H2);
  fprintf(log, "  L2 = %X\n\n", L2);

  fprintf(log, "  I = %X\n", I);
  fprintf(log, "  R = %X\n\n", R);

  fprintf(log, "  PC = %X\n", PC);
  fprintf(log, "  SP = %X\n", SP);
  fprintf(log, "  IX = %X\n", IX);
  fprintf(log, "  IY = %X\n", IY);
}

void debugCycle(FILE *log) {
  Opcode_t *instruction;

  switch (memory[PC]) {
    case 0xDE:
      instruction = EXTD_instruction_table[memory[PC+1]];
      break;
    default:
      instruction = instruction_table[memory[PC]];
      break;
  }

  if (instruction->addressing_mode == "IMM") {
    fprintf(log, "Instruction: %X, Addressing Mode: IMM, Opcode: %s, Next byte: %X\n", memory[PC], instruction->name, memory[PC + 1]);
  } else if (instruction->addressing_mode == "NONE") {
    fprintf(log, "Instruction: %X, Addressing Mode: NONE, Opcode: %s\n", memory[PC], instruction->name);
  } else if (instruction->addressing_mode == "REG") {
    fprintf(log, "Instruction: %X, Addressing Mode: REG, Opcode: %s\n", memory[PC], instruction->name);
    logReg(log);
  } else {
    fprintf(log, "Instruction: %X, Addressing Mode: UNKNOWN, Opcode: %s\n", memory[PC], instruction->name);
  }
}

/*
void debugCycleTest(FILE *log, Opcode_t *instruction) {
  if (instruction->addressing_mode == "IMM") {
    fprintf(log, "Instruction: %X, Addressing Mode: IMM, Opcode: %s, Next byte: %X\n", memory[PC] & 0xFF, instruction->name, memory[PC + 1] & 0xFF);
  } else if (instruction->addressing_mode == "NONE") {
    fprintf(log, "Instruction: %X, Addressing Mode: NONE, Opcode: %s\n", memory[PC] & 0xFF, instruction->name);
  } else {
    fprintf(log, "Instruction: %X, Addressing Mode: UNKNOWN, Opcode: %s\n", memory[PC] & 0xFF, instruction->name);
  }
}
*/

#endif
