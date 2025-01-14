#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>

#include "header.h"

void down(int semid, int index) { 

    struct sembuf buf = {index, -1, 0};
    semop(semid, &buf, 1);

}

void up(int semid, int index) { 

    struct sembuf buf = {index, 1, 0};
    semop(semid, &buf, 1);

}

int main(int argc, char** argv) { 

    key_t key = ftok(".", 'x'); 
    int shmid, semid; 
    struct Memory *shm; 
    
    shmid = shmget(key, sizeof(struct Memory), 0);

    shm = (struct Memory*)shmat(shmid, NULL, 0);

    semid = semget(key, 3, 0);

    int item, index; 
    int size = sizeof(shm->numbers)/sizeof(shm->numbers[0]);

    while(1) { 

        down(semid, FULL);
        down(semid, MUTEX);
        
        item = 0; 

        index = semctl(semid, FULL, GETVAL);

        printf("%d\n", index);

        shm->numbers[index-1] = item; 

        for (int i = 0; i < size; i++)
            printf("%d", shm->numbers[i]);

        printf("\n");

        up(semid, MUTEX);
        up(semid, EMPTY);
        
        sleep(1);

    }

    shmdt((void*)shm);
    return 0; 

}