#ifndef POW
#define POW


#define N 10
typedef unsigned row_t[N];
void powNxN (unsigned (*A)[N], unsigned k, unsigned m);



row_t ** idMat();
void Mfree(row_t ** M);

void Mprintf(row_t **M);
#endif
