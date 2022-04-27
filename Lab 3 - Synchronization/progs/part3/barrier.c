#include <stdio.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int nproc, shmid, shmid_m, shmid_c;
int *count;
sem_t *barrier;
sem_t *mutex;

void init_barrier(int numproc) {
  
  nproc = numproc;
  shmid = shmget(IPC_PRIVATE, sizeof(sem_t), IPC_CREAT | 0600);
  if (shmid == -1) {
    printf("Cannot create shared memory!\n");
    exit(1);
  }
  barrier = (sem_t *)shmat(shmid, NULL, 0);

  shmid_m = shmget(IPC_PRIVATE, sizeof(sem_t), IPC_CREAT | 0600);
  if (shmid_m == -1) {
    printf("Cannot create shared memory!\n");
    exit(1);
  }
  mutex = (sem_t *)shmat(shmid_m, NULL, 0);

  
  sem_init(barrier, 1, 0);
  sem_init(mutex, 1, 1); // mutex 

  shmid_c = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0600);
  if (shmid_c == -1) {
    printf("Cannot create shared memory!\n");
    exit(1);
  }

  count = (int*) shmat(shmid_c, NULL, 0);
}

void reach_barrier() {
  sem_wait(mutex);
  (*count)++;
  sem_post(mutex);

  if (*count != nproc){
    sem_wait(barrier);
  } 
  sem_post(barrier);
 
  
}

void destroy_barrier(int my_pid) {
    if(my_pid != 0) {
        // Destroy the semaphores and detach
        // and free any shared memory. Notice
        // that we explicity check that it is
        // the parent doing it.
        sem_destroy(mutex);
        sem_destroy(barrier);
        shmdt(mutex);
        shmdt(barrier);
        shmdt(count);
        shmctl(shmid, IPC_RMID, 0);
        shmctl(shmid_m, IPC_RMID, 0);
        shmctl(shmid_c, IPC_RMID, 0);
    }
}


