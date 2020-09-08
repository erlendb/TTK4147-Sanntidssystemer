#include <time.h>

int main() {
  struct timespec t, t2;
  t.tv_sec = 1;
  nanosleep(&t, &t2);
  return 0;
}