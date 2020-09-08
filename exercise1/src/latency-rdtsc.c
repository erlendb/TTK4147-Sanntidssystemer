#include <x86intrin.h>

int main() {
  for(int i = 0; i < 10*1000*1000; i++){
    __rdtsc();
  }
  return 0;
}