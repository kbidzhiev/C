#ifndef timer
#define timer
#include<stdlib.h>
#include<time.h>

const int MICROSEC_AS_NSEC = 1000;
const int SEC_AS_MICROSEC = 1000000;
const int SEC_AS_NSEC = 1000000000;

double diff(struct timespec start, struct timespec end) {
  struct timespec temp;
  double msec;
  if(end.tv_sec - start.tv_nsec < 0) {
    temp.tv_sec = end.tv_sec - start.tv_sec - 1;
    temp.tv_nsec = SEC_AS_NSEC + end.tv_nsec - start.tv_nsec;
  } else {
    temp.tv_sec = end.tv_sec - start.tv_sec;
    temp.tv_nsec = end.tv_nsec - start.tv_nsec;
  }
  msec = temp.tv_sec * SEC_AS_MICROSEC + temp.tv_nsec/MICROSEC_AS_NSEC;
  return msec/SEC_AS_MICROSEC;

}

#endif


