#ifndef Z80CPU_H
#define Z80CPU_H

#include <stdint.h>
#include <stdio.h>
#include "z80mem.h"
#include "z80error.h"


uint8_t A,F,B,C,D,E,H,L;
uint8_t A2,F2,B2,C2,D2,E2,H2,L2;
uint8_t I,R;

uint16_t PC,SP,IX,IY;

// read a byte from memory
uint8_t fetch(uint8_t *memory, int size, uint16_t address) {
  return read(memory, size, PC++);
}


void clock(/* arguments */) {
  /* code */
}

#endif
