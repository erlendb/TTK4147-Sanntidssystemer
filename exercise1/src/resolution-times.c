#include <sys/times.h>
#include <stdio.h>
#include <string.h>
#include <helpers.h>

void main() {
  int ns_max = 5;
  int histogram[ns_max];
  memset(histogram, 0, sizeof(int)*ns_max);
  struct tms t1, t2;
  clock_t c1, c1;

  for (int i = 0; i < 10*1000*1000; i++) {
    c1 = times(&t1);
    c2 = times(&t2);
    int ns = (t2.tms_utime - t1.tms_utime);
    int ns = ()
    if (ns >= 0 && ns < ns_max) {
      histogram[ns]++;
    }
  }

  for (int i = 0; i < ns_max; i++) {
    printf("%d\n", histogram[i]);
  }
}