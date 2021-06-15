#ifndef Z80ERROR_H
#define Z80ERROR_H

#include <stdio.h>

enum errorCodes {OUT_OF_BOUNDS_READ, OUT_OF_BOUNDS_WRITE};


// prints an error message and immediately quits the program
void error(char *message, int retVal) {
  fprintf(stderr, "ERROR: %s\n", message);
  exit(retVal);
}

#endif
