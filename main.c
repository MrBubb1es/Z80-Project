#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "z80cpu.h"
#include "z80opcodes.h"

#define MEMSIZE 65536

uint8_t memory[MEMSIZE];



int main(int argc, char const *argv[]) {
  A=0;
  printf("%d\n", fetch(memory, MEMSIZE, 255));
  printf("%d\n", fetch(memory, MEMSIZE, 755));
  return A;
}
