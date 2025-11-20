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


