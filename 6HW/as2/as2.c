#include <stdio.h>
#include <stdlib.h>
#include "assembly.h" 

int main(void) {
  unsigned cmd;

  while(scanf("%x", &cmd) == 1) {
    struct instr_t instr;
    unsigned char command = cmd & 0xFF;
    instr = decode_command(command);
    print_instr(instr);
  }


  return 0;
}
