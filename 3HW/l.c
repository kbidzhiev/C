

unsigned search(const int * arr, unsigned len, int elem) {
  for(unsigned i = 0; i < len; ++i) {
    if(arr[i] == elem) {
      return i;
    }
  }
  return len;
}
