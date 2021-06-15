#ifndef _Z80_RAM
#define _Z80_RAM


uint8_t readMem(uint8_t mem[], uint16_t address) {
  return mem[address];
}

void writeMem(uint8_t mem[], uint16_t address, uint8_t data) {
  mem[address] = data;
}


#endif
