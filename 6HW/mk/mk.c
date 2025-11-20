#include <stdio.h>
#include <stdlib.h>

enum reg_t { A = 0, B = 1, C = 2, D = 3 };

enum mnem_t {
  MOVI = 0, // 0III II II
  ADD = 8,  // 1000 RR RR
  SUB = 9,  // 1001 RR RR
  MUL = 10, // 1010 RR RR
  DIV = 11, // 1011 RR RR
  IN = 48,  // 1100 00 RR
  OUT = 49, // 1100 01 RR
  LAST
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

  instr.mnem = LAST;
  return instr;
  // fprintf(stderr, "ERROR\n");
  // abort();
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

unsigned char regs[4];

void execute_instr(const struct instr_t instr) {
  switch (instr.mnem) {
  case MOVI:
    regs[D] = instr.op.imm;
    break;
  case OUT:
    printf("%d\n", regs[instr.op.reg]);
    break;
  case IN:
    scanf(" %hhu", regs + instr.op.reg);
    // printf("IN %s\n", regnames[instr.op.reg]);
    break;
  case ADD:
    regs[instr.op.regs.rd] += regs[instr.op.regs.rs];
    regs[instr.op.regs.rd] %= 256; 
    break;
  case SUB:
    regs[instr.op.regs.rd] -= regs[instr.op.regs.rs];
    regs[instr.op.regs.rd] %= 256; 
    break;
  case MUL:
    regs[instr.op.regs.rd] *= regs[instr.op.regs.rs];
    regs[instr.op.regs.rd] %= 256; 
    break;
  case DIV:
    regs[instr.op.regs.rd] /= regs[instr.op.regs.rs];
    regs[instr.op.regs.rd] %= 256; 
    break;
    // printf("%s %s, %s\n", arithnames[instr.mnem - ADD],
    //        regnames[instr.op.regs.rd], regnames[instr.op.regs.rs]);
  default:
    fprintf(stderr, "Unrecognised instruction\n");
    abort();
    break;
  }
}

struct vector_t {
  struct instr_t *instrs;
  int size;
  int capacity;
};

struct vector_t init_vector(const int capacity) {
  struct vector_t vec;
  vec.instrs = calloc(capacity, sizeof(struct vector_t));
  vec.size = 0;
  vec.capacity = capacity;
  return vec;
}

void free_vector(struct vector_t *vec) {
  free(vec->instrs);
  vec->size = 0;
  vec->capacity = 0;
}

void push_back(struct vector_t *vec, const struct instr_t instr) {
  if (vec->size == vec->capacity) {
    int new_cap = 2 * vec->capacity;
    struct instr_t *new_instrs =
        realloc(vec->instrs, new_cap * sizeof(struct instr_t));
    if (!new_instrs) {
      fprintf(stderr, "realloc failed\n");
      free(vec->instrs);
      abort();
    }
    vec->instrs = new_instrs;
    vec->capacity = new_cap;
  }
  vec->instrs[vec->size] = instr;
  vec->size += 1;
}

int main(void) {
  unsigned cmd;
  struct vector_t vec;
  vec = init_vector(10);
  while (scanf("%x", &cmd) == 1) {
    struct instr_t instr;
    unsigned char command = cmd & 0xFF;
    instr = decode_command(command);
    if (instr.mnem == LAST) break;

    push_back(&vec, instr);
  }
  for (int i = 0; i < vec.size; ++i) {
    execute_instr(vec.instrs[i]);
    //print_instr(vec.instrs[i]);
  }
  free_vector(&vec);
  return 0;
}
