#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

long global = 0;
sem_t sem;

void* fn(void* args)
{
  long local = 0;
  for (size_t i = 0; i < 5000000; i++) {
    sem_wait(&sem);
    global++;
    sem_post(&sem);
    local++;
  }
  printf("global: %ld\n", global);
  printf("local: %ld\n", local);
  return NULL;
}

int main(int argc, char const *argv[]) {
  sem_init(&sem, 1, 1);
  pthread_t threadHandle1, threadHandle2;
  pthread_create(&threadHandle1, NULL, fn, NULL);
  pthread_create(&threadHandle2, NULL, fn, NULL);
  pthread_join(threadHandle1, NULL);
  pthread_join(threadHandle2, NULL);
  return 0;

  // TASK C
  // * Tid: Semaphore kjøres på kernel og det tar ekstra tid å switche mellom prosessor og kernel
}
