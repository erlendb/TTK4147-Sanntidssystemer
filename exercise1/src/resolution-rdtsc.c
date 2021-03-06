#include <x86intrin.h>
#include <stdio.h>
#include <string.h>

void main() {
  int ns_max = 50;
  int histogram[ns_max];
  memset(histogram, 0, sizeof(int)*ns_max);

  for (int i = 0; i < 10*1000*1000; i++) {
    int t1 = __rdtsc();
    int t2 = __rdtsc();
    int ns = (t2 - t1); // todo: convert to ns
    if (ns >= 0 && ns < ns_max) {
      histogram[ns]++;
    }
  }

  for (int i = 0; i < ns_max; i++) {
    printf("%d\n", histogram[i]);
  }
}