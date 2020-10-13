#define _GNU_SOURCE
#include <stdio.h>
#include "io.h"
#include <pthread.h>
#include <sched.h>
#include <time.h>
#include "helpers.h"

void busy_delay_short(void) {
  for (size_t i = 0; i < 10; i++) {
    asm volatile ("" ::: "memory");
  }
}

int set_cpu(int cpu_number) {
  cpu_set_t cpu;
  CPU_ZERO(&cpu);
  CPU_SET(cpu_number, &cpu);
  return pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpu);
}


void* taskAfunc() {
  set_cpu(0);
  while (1) {
    if (!io_read(1)) {
      io_write(1,0);
      busy_delay_short();
      io_write(1,1);
    }
  }
}

void* taskBfunc() {
  set_cpu(0);
  while (1) {
    if (!io_read(2)) {
      io_write(2,0);
      busy_delay_short();
      io_write(2,1);
    }
  }
}

void* taskCfunc() {
  set_cpu(0);
  while (1) {
    if (!io_read(3)) {
      io_write(3,0);
      busy_delay_short();
      io_write(3,1);
    }
  }
}




void* taskAperiodic() {
  set_cpu(0);

  struct timespec waketime;
  clock_gettime(CLOCK_REALTIME, &waketime);
  struct timespec period = { .tv_sec = 0, .tv_nsec = 1*10*1000 };

  while (1) {
    if (!io_read(1)) {
      io_write(1,0);
      busy_delay_short();
      io_write(1,1);
    }

    waketime = timespec_add(waketime, period);
    clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &waketime, NULL);
  }
}

void* taskBperiodic() {
  set_cpu(0);

  struct timespec waketime;
  clock_gettime(CLOCK_REALTIME, &waketime);
  struct timespec period = { .tv_sec = 0, .tv_nsec = 1*10*1000 };

  while (1) {
    if (!io_read(2)) {
      io_write(2,0);
      busy_delay_short();
      io_write(2,1);
    }

    waketime = timespec_add(waketime, period);
    clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &waketime, NULL);
  }
}

void* taskCperiodic() {
  set_cpu(0);

  struct timespec waketime;
  clock_gettime(CLOCK_REALTIME, &waketime);
  struct timespec period = { .tv_sec = 0, .tv_nsec = 1*10*1000 };

  while (1) {
    if (!io_read(3)) {
      io_write(3,0);
      busy_delay_short();
      io_write(3,1);
    }

    waketime = timespec_add(waketime, period);
    clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &waketime, NULL);
  }
}

void* disturbance() {
  set_cpu(0);
  while (1) {
    asm volatile("" ::: "memory");
  }
}


int main(int argc, char const *argv[]) {

  io_init();

  pthread_t threadA, threadB, threadC;
  pthread_t d1, d2, d3, d4, d5, d6, d7, d8, d9, d10;

  pthread_create(&threadA, NULL, taskAperiodic, NULL);
  pthread_create(&threadB, NULL, taskBperiodic, NULL);
  pthread_create(&threadC, NULL, taskCperiodic, NULL);

  // pthread_create(&d1, NULL, disturbance, NULL);
  // pthread_create(&d2, NULL, disturbance, NULL);
  // pthread_create(&d3, NULL, disturbance, NULL);
  // pthread_create(&d4, NULL, disturbance, NULL);
  // pthread_create(&d5, NULL, disturbance, NULL);
  // pthread_create(&d6, NULL, disturbance, NULL);
  // pthread_create(&d7, NULL, disturbance, NULL);
  // pthread_create(&d8, NULL, disturbance, NULL);
  // pthread_create(&d9, NULL, disturbance, NULL);
  // pthread_create(&d10, NULL, disturbance, NULL);

  pthread_join(threadA, NULL);
  pthread_join(threadB, NULL);
  pthread_join(threadC, NULL);
  /*
  pthread_join(d1, NULL);
  pthread_join(d2, NULL);
  pthread_join(d3, NULL);
  pthread_join(d4, NULL);
  pthread_join(d5, NULL);
  pthread_join(d6, NULL);
  pthread_join(d7, NULL);
  pthread_join(d8, NULL);
  pthread_join(d9, NULL);
  pthread_join(d10, NULL);
  */
  return 0;
}
