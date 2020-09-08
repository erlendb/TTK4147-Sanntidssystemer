#include <stdio.h>
#include <sched.h>
#include <time.h>
#include <x86intrin.h>
#include <string.h>

// int main()
// {
//   struct timespec now, after;

//   clock_gettime(CLOCK_MONOTONIC, &now);
//   sched_yield();
//   clock_gettime(CLOCK_MONOTONIC, &after);

//   printf("%ldns\n", (after.tv_nsec - now.tv_nsec));
//   return 0;
// }


int main() {
  struct timespec now, after;
  int ns_max = 50;
  int histogram[ns_max];
  memset(histogram, 0, sizeof(int)*ns_max);

  for (int i = 0; i < 10*1000*1000; i++) {
    clock_gettime(CLOCK_MONOTONIC, &now);
    sched_yield();
    clock_gettime(CLOCK_MONOTONIC, &after);
    int ns = (after.tv_nsec - now.tv_nsec);
    if (ns >= 0 && ns < ns_max) {
      histogram[ns]++;
    }
  }

  for (int i = 0; i < ns_max; i++) {
    printf("%d\n", histogram[i]);
  }
  
  return 0;
}