//#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <iostream>

#ifdef __cplusplus
extern "C"
{
#endif

void* malloc(size_t size);

void free(void *p);

#ifdef __cplusplus
}
#endif

using malloc_fn = void* (*)(size_t);
using free_fn = void (*)(void*);

void* malloc(size_t size)
{
  static void *(*libc_malloc)(size_t) = NULL;
  if (!libc_malloc) {
      libc_malloc = (malloc_fn)dlsym(RTLD_NEXT, "malloc");
  }

  struct timespec ts;
  if (!clock_gettime(CLOCK_REALTIME,&ts)) {
    fprintf(stderr,
        "%lu.%lu,%lu\n",
        ts.tv_sec,
        (ts.tv_nsec / 1000),
        size);
  }
  return libc_malloc(size);
}

void free(void *p)
{
    void (*libc_free)(void*) = (free_fn)dlsym(RTLD_NEXT, "free");
    libc_free(p);
}

