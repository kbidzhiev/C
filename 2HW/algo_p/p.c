

int is_prime(unsigned long long n){
  if ((n ==2) || (n==3)) return 1;
  if ((n<2) || ((n%2)== 0) || ((n%3)==0)) return 0;

  for (unsigned long long j = 5; j*j <= n; j +=6)
    if (((n%j)==0) || (n%(j+2))==0) return 0;
  return 1;
}
