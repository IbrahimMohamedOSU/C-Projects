#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "definition.h" 

/* the buffer */
buffer_item buffer[BUFFER_SIZE];
/* semaphores & mutex lock */
sem_t empty, full;
pthread_mutex_t mutex;
/* integers that serve insert_item & remove_item */
int add, withdraw;

/* insert_item function definition */
int insert_item(buffer_item item) {
  if (add < BUFFER_SIZE) {
    /* insert an item into the buffer */
    buffer[add] = item;
    add = (add + 1) % BUFFER_SIZE;
    /* return 0 if successful, otherwise return -1 indicating an error condition */
    return 0;
  } else { return -1; }
}

/* producer thread */
void *producer(void *param) {
  buffer_item random;
  /* assigning thread identifier */
  int spawn;
  spawn = pthread_self();

  while (1) {
    /* sleep for a random period of time */
    int randomTime = rand() / 1000000000;
    sleep(randomTime);
    /* generate a random number */
    random = rand_r(&spawn);
    /* Make sure to wait for empty before acquiring the mutex lock */
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);

    /* Loop to indicate a successul or failed production */
    if (insert_item(random) < 0) {
      printf("Error: Producer cannot produce with insert_item.\n"); // report error condition
    } else {
      printf("Producer produced %d\n", random); // report successful production
    }

    /* release the mutex lock */
    pthread_mutex_unlock(&mutex);
    /* post full */
    sem_post(&full);
  }
}

/* remove_item function definition */
int remove_item(buffer_item *item) {
/* remove an object from buffer and place it in item*/    
  if (withdraw < BUFFER_SIZE) {
    *item = buffer[withdraw];
    withdraw = (withdraw + 1) % BUFFER_SIZE;
    /* return 0 if successful, otherwise return -1 indicating an error condition */
    return 0;
  } else { return -1; }
}

/* consumer thread */
void *consumer(void *param) {
  buffer_item random;

  while (1) {
    /* sleep for a random period of time */
    int randomTime = rand() / 1000000000;
    sleep(randomTime);
    /* Make sure to wait for full before acquiring the mutex lock */
    sem_wait(&full);
    pthread_mutex_lock(&mutex);

/* Loop to indicate a successul or failed consumption */
    if (remove_item(&random) < 0) {
      printf("Error: Consumer cannot consume with remove_item.\n"); // report error condition
    } else {
      printf("Consumer consumed %d\n", random); // report successful consumption
    }

    /* release the mutex lock */
    pthread_mutex_unlock(&mutex);
    /* post empty */
    sem_post(&empty);
  }
}

int main(int argc, char *argv[]) {
/* declaring thread identifiers and attributes */
  pthread_t tid;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
/* an integer used to create the producer and consumer threads */
  int k;
  
  /* 1. Get command line arguments argv[1], argv[2], argv[3] */
  if (argc != 4) fprintf(stderr, "Error: Only 3 parameters allowed.");
  /* argv[1] = sleep time
     argv[2] = number of producers
     argv[3] = number of consumers */
  int timeAsleep = atoi(argv[1]);
  int producerAmount = atoi(argv[2]);
  int consumerAmount = atoi(argv[3]);
  /* 2. Initialize buffer, mutex, semaphores, and other global vars */
  add, withdraw = 0;
  sem_init(&empty, 0, BUFFER_SIZE);
  sem_init(&full, 0, 0);
  pthread_mutex_init(&mutex, NULL);
  /* 3. Create producer thread(s) */
  for (k = 0; k < producerAmount; k++) {
    pthread_create(&tid, &attr, producer, NULL);
  }
  /* 4. Create consumer thread(s) */
  for (k = 0; k < consumerAmount; k++) {
    pthread_create(&tid, &attr, consumer, NULL);
  }
  /* 5. Sleep */
  sleep(timeAsleep);
  /* 6. Release resources, e.g. destroy mutex and semaphores */
  pthread_mutex_destroy(&mutex);
  sem_destroy(&full);
  sem_destroy(&empty);
  /* 7. Exit */
  return (0);
}
