#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

void somefunc(unsigned long n) {
  int *a = (int*)malloc(n);

  if (!a) {
    return;
  }

  for (unsigned long i = 0; i < n/400; i++) {
    *(a + i * 100) = 0;
  }
  usleep(9000);
}

int main() {
  void* a;
  int iter = 1000;

  for (int i = 0; i < iter; i++) {
    somefunc(5 * 1024 * 1024); // 5 mb
  }

  return 0;
}

