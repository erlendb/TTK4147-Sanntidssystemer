#include <time.h>

int main() {
  struct timespec t;
  for(int i = 0; i < 10*1000*1000; i++){
    clock_gettime(CLOCK_MONOTONIC, &t);
  }
  return 0;
}