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
    if((shmid = shmget(key, sizeof(struct Memory), IPC_CREAT | 0666)) < 0)
    {
        perror("shmget error\n");
        exit(1);
    }
    shm = (struct Memory *) shmat(shmid, NULL, 0);
    if((long)shm == -1)
    {
        perror("shmat error\n");
        exit(1);
    }   
    while(shm->gostop == GO)
    {
        int size = sizeof(shm->data.numbers)/sizeof(shm->data.numbers[0]);
        for(int i = 0; i < size; i++)
        {
            while(shm->data.counter == 0)
            {
                if(shm->gostop == STOP)
                {
                    break;
                }
            }
            for(int j = 0; j <size ; j++)
            {
                printf("%d", shm->data.numbers[j]);
            }
            printf("\n");
            shm->status = TAKEN;
            sleep(1);
        }
    }
    shmdt((void*)shm);
    return 0;
}