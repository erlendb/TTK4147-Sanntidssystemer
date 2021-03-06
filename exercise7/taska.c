#include "io.h"
#include <rtdk.h>
#include <sys/mman.h>
#include <native/task.h>
#include <native/timer.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include "helpers.h"

unsigned long duration = 10000000000; // 10 nuller = 10 sek

int set_cpu(int cpu_number) {
  cpu_set_t cpu;
  CPU_ZERO(&cpu);
  CPU_SET(cpu_number, &cpu);
  return pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpu);
}

void taskAfunc() {
  unsigned long endTime = rt_timer_read() + duration;
  
  while (1) {
    if (!io_read(1)) {
      io_write(1,0);
      rt_timer_spin(5000);
      io_write(1,1);
    }
    
    if (rt_timer_read() > endTime) {
      rt_printf("Time expired\n");
      rt_task_delete(NULL);
    }
    if (rt_task_yield()) {
      rt_printf("Task failed to yield\n");
      rt_task_delete(NULL);
    }
  }
}

void taskBfunc() {
  unsigned long endTime = rt_timer_read() + duration;
  
  while (1) {
    if (!io_read(2)) {
      io_write(2,0);
      rt_timer_spin(5000);
      io_write(2,1);
    }
    
    if (rt_timer_read() > endTime) {
      rt_printf("Time expired\n");
      rt_task_delete(NULL);
    }
    if (rt_task_yield()) {
      rt_printf("Task failed to yield\n");
      rt_task_delete(NULL);
    }
  }
}

void taskCfunc() {
  unsigned long endTime = rt_timer_read() + duration;
  
  while (1) {
    if (!io_read(3)) {
      io_write(3,0);
      rt_timer_spin(5000);
      io_write(3,1);
    }
    
    if (rt_timer_read() > endTime) {
      rt_printf("Time expired\n");
      rt_task_delete(NULL);
    }
    if (rt_task_yield()) {
      rt_printf("Task failed to yield\n");
      rt_task_delete(NULL);
    }
  }
}

void taskAperiodic() {
  unsigned long endTime = rt_timer_read() + duration;
  
  rt_task_set_periodic(NULL, TM_NOW, 1*10*100000);
  
  while (1) {
    if (!io_read(1)) {
      io_write(1,0);
      rt_timer_spin(5000);
      io_write(1,1);
    }
    
    if (rt_timer_read() > endTime) {
      rt_printf("Time expired\n");
      rt_task_delete(NULL);
    }
    if (rt_task_yield()) {
      rt_printf("Task failed to yield\n");
      rt_task_delete(NULL);
    }
    
    rt_task_wait_period(NULL);
    
  }
}

void taskBperiodic() {
  unsigned long endTime = rt_timer_read() + duration;
  
  rt_task_set_periodic(NULL, TM_NOW, 1*10*100000);
  
  while (1) {
    if (!io_read(2)) {
      io_write(2,0);
      rt_timer_spin(5000);
      io_write(2,1);
    }
    
    if (rt_timer_read() > endTime) {
      rt_printf("Time expired\n");
      rt_task_delete(NULL);
    }
    if (rt_task_yield()) {
      rt_printf("Task failed to yield\n");
      rt_task_delete(NULL);
    }
    
    rt_task_wait_period(NULL);
    
  }
}

void taskCperiodic() {
  unsigned long endTime = rt_timer_read() + duration;
  
  rt_task_set_periodic(NULL, TM_NOW, 1*10*100000);
  
  while (1) {
    if (!io_read(3)) {
      io_write(3,0);
      rt_timer_spin(5000);
      io_write(3,1);
    }
    
    if (rt_timer_read() > endTime) {
      rt_printf("Time expired\n");
      rt_task_delete(NULL);
    }
    if (rt_task_yield()) {
      rt_printf("Task failed to yield\n");
      rt_task_delete(NULL);
    }
    
    rt_task_wait_period(NULL);
    
  }
}

void* disturbance() {
  set_cpu(0);
  while (1) {
    asm volatile("" ::: "memory");
  }
}

int main() {
  mlockall(MCL_CURRENT|MCL_FUTURE);
  rt_print_auto_init(1);
  rt_printf("main\n");
  
  RT_TASK taskA;
  RT_TASK taskB;
  RT_TASK taskC;
  
 // pthread_t d1, d2, d3, d4, d5, d6, d7, d8, d9, d10;
  
  rt_task_create(&taskA, "taskA", 0, 99, T_CPU(0));
  rt_task_create(&taskB, "taskB", 0, 99, T_CPU(0));
  rt_task_create(&taskC, "taskC", 0, 99, T_CPU(0));
/*
  pthread_create(&d1, NULL, disturbance, NULL);
  pthread_create(&d2, NULL, disturbance, NULL);
  pthread_create(&d3, NULL, disturbance, NULL);
  pthread_create(&d4, NULL, disturbance, NULL);
  pthread_create(&d5, NULL, disturbance, NULL);
  pthread_create(&d6, NULL, disturbance, NULL);
  pthread_create(&d7, NULL, disturbance, NULL);
  pthread_create(&d8, NULL, disturbance, NULL);
  pthread_create(&d9, NULL, disturbance, NULL);
  pthread_create(&d10, NULL, disturbance, NULL);
  */
  /*
  rt_task_start(&taskA, &taskAfunc, NULL);
  rt_task_start(&taskB, &taskBfunc, NULL);
  rt_task_start(&taskC, &taskCfunc, NULL);
  */                       
  rt_task_start(&taskA, &taskAperiodic, NULL);
  rt_task_start(&taskB, &taskBperiodic, NULL);
  rt_task_start(&taskC, &taskCperiodic, NULL);
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
  while (1) {
    sleep(1);
  }
  
  return 0;
}