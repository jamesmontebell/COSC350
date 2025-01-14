#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig)
{
    if (sig == SIGUSR1)
    {
        puts("My child sent signal to me, now I kill myself");
        exit(0);
    }
}

void up(int semid, int index)
{
    struct sembuf sb = {index, 1, 0};
    semop(semid, &sb, 1);
}

void down(int semid, int index)
{
    struct sembuf sb = {index, -1, 0};
    semop(semid, &sb, 1);
}

#define SEM1 0
#define SEM2 1

int main(void)
{

    key_t key = ftok(".", 'K');
    
    int semid = semget(key, 2, 0);
    
    signal(SIGUSR1, handler);

    pid_t pid = fork();

    pid_t ogPid = getppid();

    if (pid == 0)
    {
        int i = 0;

        while (true)
        {
            i++;
            if (i == 10)
            {
                kill(getppid(), SIGUSR1);
            }   
            pid = getppid();
            if (pid != ogPid)
            {
                puts("My parent killed himself, now I die");
                semctl(semid, 2, IPC_RMID);
                _exit(0);
            }
            up(semid, SEM1);
            up(semid, SEM2);
            printf("child crit\n");
            down(semid, SEM1);
            down(semid, SEM2);
            sleep(2);
        }
    }
    else
    {
        while (true)
        {
            signal(SIGUSR1, handler);

            
            up(semid, SEM1);
            up(semid, SEM2);
            printf("parent crit\n");
            down(semid, SEM1);
            down(semid, SEM2);
            sleep(2);
        }
    }
    return 0;
}