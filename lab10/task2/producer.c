#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>
#include "header.h"
#include <unistd.h>

int main(int argc, char **argv)
{
    int shmid;
    key_t key;
    struct Memory *shm;
    key = ftok(".", 'x');                              
    if ((shmid = shmget(key, sizeof(struct Memory), 0)) < 0) 
    {
        perror("shmget error \n");
        exit(1);
    }
    shm = (struct Memory *)shmat(shmid, NULL, 0);
    if ((long)shm == -1)
    {
        perror("shmat error \n");
        exit(1);
    }
    shm->gostop = GO;
    shm->status = NOT_READY;

    int size = sizeof(shm->data.numbers) / sizeof(shm->data.numbers[0]);
    shm->data.counter = 0;

    while (1)
    {
        for (int i = 0; i < size; i++)
        {
            shm->data.numbers[i] = (rand() % (10 - 0 + 1)) + 0;
            shm->data.counter++;
            if (shm->data.counter == size)
            {
                shm->status = FILLED;
                while (shm->status != TAKEN)
                    ;
            }
            for (int j = 0; j < size; j++)
            {
                printf("%d ", shm->data.numbers[j]);
            }
            printf("\n");
            sleep(1);
        }
    }
    shm->gostop = STOP;
    shmdt((void *)shm);
    return 0;
}