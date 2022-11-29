#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int sig)
{
    if (sig == SIGUSR1)
    {
        printf("kills child\n");
        kill(getppid(), SIGUSR2);
        exit(0);
    }
    else if (sig == SIGUSR2)
    {
        printf("rekt child\n");
        exit(0);
    }
}

int main()
{
    pid_t pid, pid2;
    pid = fork();

    if (pid == 0)
    {
        pid2 = fork();

        if(pid2 > 0)
        {
            signal(SIGUSR1, handler);
            while(1)
                printf("child\n");
                sleep(1);
        }
        else if(pid2 == 0)
        {
            for(int i = 0; i < 10; i++)
            {
                printf("grandchild\n");
                sleep(1);
            }
            kill(getppid(), SIGUSR1);
            // if(getppid() == 1)
            //     exit(0);
        }
    }
    if (pid > 0)
    {
        signal(SIGUSR2, handler);
        while(1)
            printf("parent\n");
            sleep(1);
        exit(1);
    }
    return 0;
}