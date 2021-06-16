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
  int instruction = memory[PC];


}

#endif
