#ifndef Z80OPCODES_H
#define Z80OPCODES_H



typedef struct {
  char *name;
  int cycles;
  int bytes;
  void (*func)();
} Opcode_t;


void NOP() {
  return;
}



Opcode_t *instructions[256] = {(Opcode_t){"NOP", 4, 1, NOP}};


#endif
