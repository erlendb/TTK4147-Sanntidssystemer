#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

pthread_mutex_t mtx1, mtx2, mtx3, mtx4, mtx5;

void* eat1 ()
{
  while (1) {
    pthread_mutex_lock(&mtx1);
    //sleep(1);
    pthread_mutex_lock(&mtx5);
    // Spise
    printf("1 spiser :)\n");
    sleep(1);
    pthread_mutex_unlock(&mtx5);
    pthread_mutex_unlock(&mtx1);
    //sleep(1);
  }
  return NULL;
}

void* eat2 ()
{
  while (1) {
    pthread_mutex_lock(&mtx1);
    //sleep(1);
    pthread_mutex_lock(&mtx2);
    // Spise
    printf("2 spiser :)\n");
    sleep(1);
    pthread_mutex_unlock(&mtx1);
    pthread_mutex_unlock(&mtx2);
    //sleep(1);
  }
  return NULL;
}

void* eat3 ()
{
  while (1) {
    
    pthread_mutex_lock(&mtx2);
    //sleep(1);
    pthread_mutex_lock(&mtx3);
    // Spise
    printf("3 spiser :)\n");
    sleep(1);
    pthread_mutex_unlock(&mtx2);
    pthread_mutex_unlock(&mtx3);
    //sleep(1);
  }
  return NULL;
}

void* eat4 ()
{
  while (1) {
    pthread_mutex_lock(&mtx3);
    //sleep(1);
    pthread_mutex_lock(&mtx4);
    // Spise
    printf("4 spiser :)\n");
    sleep(1);
    pthread_mutex_unlock(&mtx3);
    pthread_mutex_unlock(&mtx4);
    //sleep(1);
  }
  return NULL;
}

void* eat5 ()
{
  while (1) {
    pthread_mutex_lock(&mtx4);
    //sleep(1);
    pthread_mutex_lock(&mtx5);
    // Spise
    printf("5 spiser :)\n");
    sleep(1);
    pthread_mutex_unlock(&mtx4);
    pthread_mutex_unlock(&mtx5);
    //sleep(1);
  }
  return NULL;
}

int main(int argc, char const *argv[]) {

  pthread_t p1, p2, p3, p4, p5;



  pthread_mutex_init(&mtx1, NULL);
  pthread_mutex_init(&mtx2, NULL);
  pthread_mutex_init(&mtx3, NULL);
  pthread_mutex_init(&mtx4, NULL);
  pthread_mutex_init(&mtx5, NULL);

  pthread_create(&p1, NULL, eat1, NULL);
  pthread_create(&p2, NULL, eat2, NULL);
  pthread_create(&p3, NULL, eat3, NULL);
  pthread_create(&p4, NULL, eat4, NULL);
  pthread_create(&p5, NULL, eat5, NULL);

  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  pthread_join(p3, NULL);
  pthread_join(p4, NULL);
  pthread_join(p5, NULL);

  pthread_mutex_destroy(&mtx1);
  pthread_mutex_destroy(&mtx2);
  pthread_mutex_destroy(&mtx3);
  pthread_mutex_destroy(&mtx4);
  pthread_mutex_destroy(&mtx5);

  return 0;
}
