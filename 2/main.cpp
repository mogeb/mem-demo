#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

void somefunc(unsigned long n) {
    int *buf = (int*)malloc(n);
    if (!buf) {
        return;
    }
    usleep(500000);
}

int main() {
  int iter = 100;
  for (int i = 0; i < iter; i++) {
    somefunc(10 * 1024 * 1024); // 10 mb
  }

  return 0;
}
