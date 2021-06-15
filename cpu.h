#ifndef _Z80_CPU
#define _Z80_CPU


struct {
  uint8_t A,F,B,C,D,E,H,L;
} Registers;

typedef struct {
  // 8-bit registers
  struct Registers *front;
  struct Registers *back;
  uint8_t I,R; // Interrupt and Refresh registers

  // 16-bit registers
  // Stack Pointer, Program Counter, Index Registers X and Y
  uint16_t SP, PC, IX, IY;

  // Clock cycles left before next instruction
  int cycles;
  // Interrupt state
  int maskable;
  int mode;
} Z80_t;


// Simulates receiving a reset signal on the bus - sets CPU to default state
void reset(Z80_t *cpu) {
  // Set all CPU Registers to 0
  cpu->I = 0;
  cpu->R = 0;

  cpu->PC = 0;
  cpu->maskable = 0;
  cpu->mode = 0;
}

void clock(Z80_t *cpu) {
  if (cpu->cycles == 0) {

  }

  // Decrement cycles remaining
  cpu->cycles--;
}


#endif
