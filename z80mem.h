#ifndef Z80MEMORY_H
#define Z80MEMORY_H

#include "z80config.h"
#include "z80error.h"

uint8_t memory[MEMSIZE];

// read a byte from memory
uint8_t read(uint8_t *memory, int size, uint16_t address) {
  if (address >= size) {
    char errorMsg[100];
    sprintf(errorMsg, "addressing out of bounds memory @%04X (max %04X)\n", address, size);
    error(errorMsg, OUT_OF_BOUNDS_READ);
  }
  return memory[address];
}

// write a byte to memory
void write(uint8_t *memory, int size, uint16_t address, uint8_t data) {
  if (address >= size) {
    char errorMsg[100];
    sprintf(errorMsg, "addressing out of bounds memory @%04X (max %04X)\n", address, size);
    error(errorMsg, OUT_OF_BOUNDS_WRITE);
  }
  memory[address] = data;
}


#endif
