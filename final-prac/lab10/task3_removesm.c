#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

#include "header.h"

int main(int argc, char **argv) { 

    key_t key = ftok(".", 'x');
    int shmid, semid; 
    struct Memory *shm;
    union semun1 arg; 

    shmid = shmget(key, sizeof(struct Memory), 0);

    shmctl(shmid, IPC_RMID, NULL);

    semid = semget(key, 3, 0);

    semctl(semid, 0, IPC_RMID, arg);

    exit(0);
}