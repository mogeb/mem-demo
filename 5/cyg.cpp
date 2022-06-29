//#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <iostream>
#include <linux/perf_event.h>
#include <sys/mman.h>
#include <unistd.h>
#include <asm/unistd.h>

#ifdef __cplusplus
extern "C"
{
#endif

void __cyg_profile_func_enter(void *this_fn, void *call_site);

void perf_init();

#ifdef __cplusplus
}
#endif

using malloc_fn = void* (*)(size_t);
using free_fn = void (*)(void*);


struct perf_event_attr *attr1;
struct perf_event_mmap_page *thepage;
int globalfd;
bool init = false;

/* perf_event_open syscall wrapper */
static long
sys_perf_event_open(struct perf_event_attr *hw_event,
                    pid_t pid, int cpu, int group_fd, unsigned long flags)
{
    return syscall(__NR_perf_event_open, hw_event, pid, cpu, group_fd, flags);
}

struct perf_event_mmap_page *setup_perf(struct perf_event_attr *attr)
{
    struct perf_event_mmap_page *perf_addr;
    int fd, ret;
    size_t pgsz;

    pgsz = sysconf(_SC_PAGESIZE);

    fd = sys_perf_event_open(attr, 0, -1, -1, 0);

    globalfd = sys_perf_event_open(attr, 0, -1, -1, 0);

    return perf_addr;
}

void perf_init()
{
    attr1 = (struct perf_event_attr *) malloc(sizeof(struct perf_event_attr));
 
    attr1->size = sizeof(struct perf_event_attr);
    attr1->pinned = 1;
    attr1->disabled = 0;
    attr1->type = PERF_TYPE_SOFTWARE;
    attr1->config = PERF_COUNT_SW_PAGE_FAULTS;
    // attr1->read_format = PERF_FORMAT_GROUP|PERF_FORMAT_ID;

    setup_perf(attr1);
}

long long lastRes = 0;
long long lastRSP = 0;
long long cumulRSP = 0;
long long cumulRes = 0;

void __cyg_profile_func_enter(void *this_fn, void *call_site)
{
  register unsigned long rsp asm("rsp");
  if (!init) {
    perf_init();
    init = true;
  }

  int count = 10;
  char data[4096 * count];

  long long res;
  read(globalfd, &res, sizeof(long long));

  if (lastRSP == 0) {
    lastRSP = rsp;
  }

  cumulRSP += lastRSP - rsp;
  cumulRes += (res - lastRes) * 4096;

  struct timespec ts;
  if (!clock_gettime(CLOCK_REALTIME,&ts)) {
    fprintf(stderr,
        "%lu.%lu,%lu,%lu\n",
        ts.tv_sec,
        (ts.tv_nsec / 1000),
        cumulRSP,
        cumulRes);
  }
  lastRes = res;
  lastRSP = rsp;
}
