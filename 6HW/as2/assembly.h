#include <stdio.h>
#include <stdlib.h>

enum reg_t { A = 0, B, C, D };

enum mnem_t {
  MOVI = 0, // 0III II II
  ADD = 8,  // 1000 RR RR
  SUB = 9,  // 1001 RR RR
  MUL = 10, // 1010 RR RR
  DIV = 11, // 1011 RR RR
  IN = 48,  // 1100 00 RR
  OUT = 49  // 1100 01 RR
};

union operand_u {
  struct {
    int rd;
    int rs;
  } regs;
  int imm;
  int reg;
};

struct instr_t {
  enum mnem_t mnem;
  union operand_u op;
};

struct instr_t decode_command(const unsigned char cmd) {
  struct instr_t instr;

  if ((cmd >> 7) == 0) { // MOVI
    instr.mnem = MOVI;
    instr.op.imm = cmd;
    return instr;
  }

  if (((cmd >> 6) & 1) == 1) {
    // IN  1100 00 RR
    // OUT 1100 01 RR
    if ((cmd >> 2) == 0x30) {
      instr.mnem = OUT;
    } else if ((cmd >> 2) == 0x31) {
      instr.mnem = IN;
    } else {
      fprintf(stderr, "Bad input, cmd %x is not recognised", cmd);
      abort();
    }
    instr.op.reg = (cmd & 0x3);
    return instr;
  }

  if() {
  // ADD = 8,  // 1000 RR RR
  // SUB = 9,  // 1001 RR RR
  // MUL = 10, // 1010 RR RR
  // DIV = 11, // 1011 RR RR
 

  }

  fprintf(stderr, "Unrecognised command %x\n", cmd);
  abort();
}

const char *regnames[] = {"A", "B", "C", "D"};
void print_instr(struct instr_t instr) {
  switch (instr.mnem) {
  case MOVI:
    printf("MOVI %d\n", instr.op.imm);
    break;
  case OUT:
    printf("OUT %s\n", regnames[instr.op.reg]);
    break;
  case IN:
    printf("IN %s\n", regnames[instr.op.reg]);
    break;

  default:
    fprintf(stderr, "Unrecognised instruction\n");
    abort();
    break;
  }
}
