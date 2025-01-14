#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

#include "header.h"

int main(int argc, char** argv) { 

    int shmid, semid; 
    key_t key; 

    struct Memory *shm;
    union semun1 arg; 

    key = ftok(".", 'x'); 

    shmid = shmget(key, sizeof(struct Memory), IPC_CREAT | 0666);
    shm = (struct Memory*) shmat(shmid, NULL, 0);
    semid = semget(key, 3, 0666 | IPC_CREAT);

    arg.val = 1; 
    semctl(semid, MUTEX, SETVAL, arg);

    arg.val = N; 
    semctl(semid, EMPTY, SETVAL, arg);

    arg.val = 0;
    semctl(semid, FULL, SETVAL, arg);

    shm->status = NOT_READY;
    shm->gostop = GO; 

    exit(0); 
}