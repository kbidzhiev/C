#ifndef CM
#define CM


int find_end(int *sizes, int nelts);
int find_mid(int *sizes, int nelts);


typedef int (*xcmp_t)(void *lhs, int lsz, void *rhs, int rsz);
void xmsort(void *mem, int *sizes, int nelts, xcmp_t cmp);

#endif
