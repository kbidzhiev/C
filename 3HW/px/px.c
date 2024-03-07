void powNxN (unsigned (*A)[N], unsigned k, unsigned m) {
  unsigned mult = n%m;
  unsigned prod = 1;
  while (k > 0) {
    if ((k % 2) == 1)
      prod = (prod * mult) % m;
    mult = (mult * mult) % m;
    k /= 2;
  }
}

void powNxN (unsigned (*A)[N], unsigned k, unsigned m) {
  int i;
  int Prod[SIZE];
  int Mult[SIZE];
  reminder(N, Mult, m);

  Identity(Prod);
  while (k>0){
    if ((k%2) == 1){
      //prod = (prod*mult)%m;
      multiplication(Prod, Mult, Prod);
      reminder(Prod, Prod, m);
    }
    //mult = (mult * mult)%m;
    multiplication(Mult, Mult, Mult);
    reminder(Mult, Mult, m);
    k = k/2;
  }
  for(i = 0; i<SIZE; ++i){
    N[i] = Prod[i];
  }
}


