#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#if 0
struct point_t {
  int x, y;
};
struct triangle_t {
  struct point_t pts[3];
};
#endif

int iabs(int x){
  return x > 0 ? x : -x;
}


int double_area(struct triangle_t tr){
  int darea;
  int x1x3, x2x3;
  int y1y3, y2y3;

  x1x3 = tr.pts[0].x - tr.pts[2].x;
  x2x3 = tr.pts[1].x - tr.pts[2].x;

  y1y3 = tr.pts[0].y - tr.pts[2].y;
  y2y3 = tr.pts[1].y - tr.pts[2].y;

  darea = x1x3*y2y3 - x2x3*y1y3;
  return iabs(darea);
}

#if 0
int main(){
  int darea;
  struct point_t p0, p1, p2;

  if (6 != scanf("%d%d%d%d%d%d", &p0.x, &p0.y, &p1.x, &p1.y, &p2.x, &p2.y)) abort();
  struct triangle_t tr;

  tr.pts[0] = p0;
  tr.pts[1] = p1;
  tr.pts[2] = p2;
  darea = double_area(tr);
  printf("%d\n", darea);


  return 0;
}
#endif
