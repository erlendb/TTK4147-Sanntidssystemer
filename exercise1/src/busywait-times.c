#include "helpers.h"
#include <time.h>

int main() {
  struct timespec t;
  t.tv_sec = 1;
  
  int usec = 100;
  busy_wait_times(usec);
  
  return 0;
}