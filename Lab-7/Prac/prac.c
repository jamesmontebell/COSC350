#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handler(int sig)
{
    if (sig == SIGUSR1)
    {
        printf("child = ded\n");
        kill(getppid(), SIGUSR2);
        exit(0);
    }
    else if (sig == SIGUSR2)
    {
        printf("get rekt child\n");
        exit(0);
    }
}

int main()
{
    pid_t pid1 = fork();

    if (pid1 < 0)
    {
        printf("fork failed");
        exit(1);
    }
    else if (pid1 == 0)
    {
        while(1)
        {
            signal(SIGUSR1, handler);
            printf("immprtal\n");
            sleep(1);
        }
    }
    else
    {
        while(1)
        {
            signal(SIGUSR2, handler);
            for(int i = 0; i < 10 ; i++)
            {
                printf("no youre mortal\n");
                sleep(1);
            }
            kill(pid1, SIGUSR1);
        }
        exit(0);
    }
    return 0;
}
