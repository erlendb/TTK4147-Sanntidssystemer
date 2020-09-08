#include <stdio.h>
#include <sched.h>
#include <time.h>

int main()
{
  struct timespec now, after;
  clock_gettime(CLOCK_MONOTONIC, &now);

  //clock_t t1, t2;
  clock_gettime(CLOCK_MONOTONIC, &now);
  sched_yield();
  clock_gettime(CLOCK_MONOTONIC, &after);
  //printf("%Lfs\n", (long double)(t2 - t1)/CLOCKS_PER_SEC);
  printf("%ldns\n", (after.tv_nsec - now.tv_nsec));
  return 0;
}