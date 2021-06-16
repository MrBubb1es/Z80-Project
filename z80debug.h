#ifndef Z80DEBUG_H
#define Z80DEBUG_H

#include <stdint.h>
#include <stdio.h>

#include "z80config.h"
#include "z80error.h"



FILE *debugInit() {
  FILE *log = NULL;
  log = fopen("z80log.txt", "w");

  if (!log) {
    error("Failed to open log file z80log.txt", DEBUG_FILE_DOES_NOT_EXIST);
  }

  return log;
}

void debugCycle(FILE *log) {
  Opcode_t *instruction = instruction_table[memory[PC]];

  if (instruction->addressing_mode == "IMM") {
    fprintf(log, "Instruction: %x, Addressing Mode: IMM, Opcode: %s, Next byte: %x\n", memory[PC] && 0xFF, instruction->name, memory[PC + 1] && 0xFF);
  } else if (instruction->addressing_mode == "NONE") {
    fprintf(log, "Instruction: %x, Addressing Mode: NONE, Opcode: %s\n", memory[PC] && 0xFF, instruction->name);
  } else {
    fprintf(log, "Instruction: %x, Addressing Mode: UNKNOWN, Opcode: %s\n", memory[PC] && 0xFF, instruction->name);
  }
}

void debugCycleTest(FILE *log, Opcode_t *instruction) {
  if (instruction->addressing_mode == "IMM") {
    fprintf(log, "Instruction: %x, Addressing Mode: IMM, Opcode: %s, Next byte: %x\n", memory[PC] && 0xFF, instruction->name, memory[PC + 1] && 0xFF);
  } else if (instruction->addressing_mode == "NONE") {
    fprintf(log, "Instruction: %x, Addressing Mode: NONE, Opcode: %s\n", memory[PC] && 0xFF, instruction->name);
  } else {
    fprintf(log, "Instruction: %x, Addressing Mode: UNKNOWN, Opcode: %s\n", memory[PC] && 0xFF, instruction->name);
  }
}

#endif
