#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "config.h"
#include "cpu.h"
#include "ram.h"
#include "opcodes.h"


uint8_t memory[MEM_SIZE];

int main(int argc, char const *argv[]) {
  memset(memory, 0, MEM_SIZE);

  printf("Hello, World!");

  return 0;
}
