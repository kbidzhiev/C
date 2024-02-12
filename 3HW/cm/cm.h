#ifndef CM
#define CM

typedef int (*xcmp_t)(void *lhs, int lsz, void *rhs, int rsz);

void xmsort(void *mem, int *sizes, int nelts, xcmp_t cmp);

#endif
