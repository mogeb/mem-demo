#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <linux/perf_event.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/perf_event.h>
#include <asm/unistd.h>

struct perf_event_attr *attr1;
struct perf_event_mmap_page *thepage;
int globalfd;

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

    // std::cout << "globalfd = " << globalfd << std::endl;

    // if (fd < 0)
    //     return NULL;

    // perf_addr = mmap(NULL, pgsz, PROT_READ, MAP_SHARED, fd, 0);

    // if (perf_addr == MAP_FAILED)
    //     return NULL;

    // ret = close(fd);
    // if (ret) {
    //     perror("Error closing perf memory mapping FD");
    // }

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
}

long long lastRes = 0;
long long lastRSP = 0;
long long cumulRSP = 0;
long long cumulRes = 0;




void recursive(int n) {
  int count = 10;
  char data[4096 * count];

  if (n == 0) {
    return;
  }

  recursive(n - 1);
}

int main() {
  recursive(20);
  return 0;
}

