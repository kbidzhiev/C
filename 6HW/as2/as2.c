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

struct instr_t decode_command(unsigned char cmd) {
  struct instr_t instr;
  cmd = cmd & 0xFF;

  if ((cmd >> 7) == 0) {
    // MOVI = 0, // 0III II II
    instr.mnem = MOVI;
    instr.op.imm = cmd;
    return instr;
  }

  if ((cmd >> 6) == 0x2) {
    // ADD = 8,  // 1000 RR RR
    // SUB = 9,  // 1001 RR RR
    // MUL = 10, // 1010 RR RR
    // DIV = 11, // 1011 RR RR
    instr.mnem = cmd >> 4;
    instr.op.regs.rd = (cmd >> 2) & 0x3;
    instr.op.regs.rs = cmd & 0x3;
    return instr;
  }

  if ((cmd >> 2) == 0x30) {
    // IN  1100 00 RR
    instr.mnem = IN;
    instr.op.reg = (cmd & 0x3);
    return instr;
  }
  if ((cmd >> 2) == 0x31) {
    // OUT 1100 01 RR
    instr.mnem = OUT;
    instr.op.reg = (cmd & 0x3);
    return instr;
  }

  fprintf(stderr, "ERROR\n");
  abort();
}

const char *regnames[] = {"A", "B", "C", "D"};
const char *arithnames[] = {"ADD", "SUB", "MUL", "DIV"};

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
  case ADD:
  case SUB:
  case MUL:
  case DIV:
    printf("%s %s, %s\n", arithnames[instr.mnem - ADD],
           regnames[instr.op.regs.rd], regnames[instr.op.regs.rs]);
    break;

  default:
    fprintf(stderr, "Unrecognised instruction\n");
    abort();
    break;
  }
}


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
