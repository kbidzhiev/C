int foo(int *x, int y, int z) {
  if(z <= 0) return z;
  int i;
  for(i = z-1; i >= 0 && x[i] > y; --i) {
    x[i + 1] = x[i];
  }
  return i+1;
}
