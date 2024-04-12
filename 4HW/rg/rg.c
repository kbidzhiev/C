//#include "rg.h"


unsigned cycle_len(generator_t gen) {
  int hare = gen(gen(0));
  int turtle = gen(0);
  unsigned i = 0;
  for(; hare != turtle;) {
    hare = gen(gen(hare));
    turtle = gen(turtle);
  }
  turtle = gen(turtle);
  for(i = 1; turtle != hare; ++i)
    turtle = gen(turtle);
  return i;
}
