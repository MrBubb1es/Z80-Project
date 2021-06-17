#ifndef Z80CPU_H
#define Z80CPU_H

#include <stdio.h>
#include <stdint.h>

#include "z80config.h"
#include "z80error.h"
#include "z80mem.h"

// C, N, P/V, X, H, X, Z, S
enum flagBits {CARRY, ADD_SUBTRACT, OVERFLOW, UNUSED_1, HALF_CARRY, UNUSED_2, ZERO, SIGN};

uint8_t A,F,B,C,D,E,H,L;
uint8_t A2,F2,B2,C2,D2,E2,H2,L2;
uint8_t I,R;

uint16_t PC,SP,IX,IY;

// Set one bit in the F register
void setFlagBit(int bit, int val) {
  if (val) {
    F |= val << bit;
  } else {
    F &= ~(1 << bit);
  }
}

int getFlagBit(int bit) {
  return (F >> bit) & 0x01;
}

// read a byte from memory
uint8_t fetch(uint8_t *memory, int size, uint16_t address) {
  return read(memory, size, PC);
}


void clock(/* arguments */) {
  /* code */
}

#endif
