#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum reg_t { A = 0, B, C, D, RLAST };

enum mnem_t {
  MOVI = 0, // 0III II II
  ADD = 8,  // 1000 RR RR
  SUB = 9,  // 1001 RR RR
  MUL = 10, // 1010 RR RR
  DIV = 11, // 1011 RR RR
  IN = 48,  // 1100 00 RR
  OUT = 49, // 1100 01 RR
  OPLAST
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

int read_line(char *buff) {
  char c;
  int i = 0;
  while (scanf("%c", &c) == 1) {
    assert(i < 10);
    if (c == '\n') {
      buff[i] = '\0';
      return 1;
    }
    buff[i] = c;
    ++i;
  }
  return 0;
}

int str_to_mnem(const char *buff) {
  if (strcmp(buff, "MOVI") == 0)
    return MOVI;
  if (strcmp(buff, "ADD") == 0)
    return ADD;
  if (strcmp(buff, "SUB") == 0)
    return SUB;
  if (strcmp(buff, "MUL") == 0)
    return MUL;
  if (strcmp(buff, "DIV") == 0)
    return DIV;
  if (strcmp(buff, "IN") == 0)
    return IN;
  if (strcmp(buff, "OUT") == 0)
    return OUT;
  return OPLAST;
}

struct instr_t scanf_instr(const char *str) {
  struct instr_t instr;
  char buff[5];
  char c1, c2;
  int rg;

  if (sscanf(str, "%s", buff) == 1) {
    instr.mnem = str_to_mnem(buff);
  }

  switch (instr.mnem) {
  case MOVI:
    sscanf(str, "%s %d", buff, &rg);
    instr.op.imm = rg;
    break;
  case IN:
  case OUT:
    sscanf(str, "%s %c", buff, &c1);
    instr.op.reg = c1 - 'A';
    if(instr.op.reg < 0 || instr.op.reg > 4) {
      fprintf(stderr, "ERROR\n");
      abort();
    }
    break;
  case ADD:
  case SUB:
  case MUL:
  case DIV:
    sscanf(str, "%s %c, %c", buff, &c1, &c2);
    instr.op.regs.rd =  c1 - 'A';
    instr.op.regs.rs =  c2 - 'A';
    if(instr.op.regs.rd < 0 || instr.op.regs.rd > 4) {
      fprintf(stderr, "ERROR\n");
      abort();
    }
    if(instr.op.regs.rs < 0 || instr.op.regs.rs > 4) {
      fprintf(stderr, "ERROR\n");
      abort();
    }
    break;
  default:
    instr.mnem = OPLAST;
    break;
  }
  return instr;
}

unsigned char instr_to_char(const struct instr_t instr) {
  unsigned char res = 0;
  unsigned char mnem = (instr.mnem);
  switch (mnem) {
  case MOVI:
    res = (unsigned char)instr.op.imm;
    break;
  case IN:
  case OUT:
    res = mnem << 2;
    res = res | (unsigned char)instr.op.reg;
    break;
  case ADD:
  case SUB:
  case MUL:
  case DIV:
    res = mnem << 4;
    res = res | ((unsigned char)instr.op.regs.rd << 2);
    res = res | (unsigned char)instr.op.regs.rs;
    break;
  default:
    fprintf(stderr, "ERROR\n");
    abort();
  }

  return res;
}

int main(void) {
  char buff[10];
  while (read_line(buff) == 1) {
    if (strlen(buff) != 0) {
      struct instr_t instr;
      unsigned char code = 0;
      instr = scanf_instr(buff);
      code = instr_to_char(instr);
      fprintf(stdout, "0x%x ", code);
    }
  }
  fprintf(stdout, "\n");

  return 0;
}
