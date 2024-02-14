#ifndef CM
#define CM


int compute_size(int *sizes, int nelts, int begin, int num);
void *arr_elem(void *mem, int* sizes, int nelts, int elem_id);

typedef int (*xcmp_t)(void *lhs, int lsz, void *rhs, int rsz);
void xmsort(void *mem, int *sizes, int nelts, xcmp_t cmp);

#endif
