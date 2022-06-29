#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

void recur(int n) {
  int npages = 200;
  char data[4096 * npages];

  struct timespec ts;
  if (!clock_gettime(CLOCK_REALTIME,&ts)) {
    register long rsp asm("rsp");
    fprintf(stderr,
        "%lu.%lu,%lu\n",
        ts.tv_sec,
        (ts.tv_nsec / 1000),
        rsp);
    // fprintf(stderr,
    //     "%lu.%lu,%lu\n",
    //     ts.tv_sec,
    //     (ts.tv_nsec / 1000),
    //     npages * 4096);
  }

  if (!n) {
    return;
  }
  for (volatile int i = 0; i < 40000000; i++);
  recur(n - 1);
}


void somefunc(unsigned long n) {
    int *a = (int*)malloc(n);
    if (!a) {
        return;
    }
    for (unsigned long i = 0; i < n/400; i++) {
        *(a + i * 100) = 0;
       usleep(4);
    }
}

int main() {
  void* a;
   int i, iter = 1000;
   for (i = 0; i < iter; i++) {
     somefunc(5 * 1024 * 1024);
   }

    return 0;
}

