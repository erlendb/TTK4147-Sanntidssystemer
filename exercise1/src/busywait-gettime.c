#include "helpers.h"
#include <time.h>


int main() {
  struct timespec t;
  t.tv_sec = 1;
  
  busy_wait_gettime(t);
  
  return 0;
}