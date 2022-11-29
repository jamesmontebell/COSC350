#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int sig)
{
    if (sig == SIGUSR1)
    {
        printf("kill child");
        kill(getppid(), SIGUSR2);
        exit(0);
    }
    if (sig == SIGUSR2)
    {
        printf("kill parent");
        exit(0);
    }
}


int main()
{
    pid_t p1, p2;
    p1 = fork();
    if (p1 > 0)
    {
        while(1)
        {
            signal(SIGUSR2, handler);
            printf("parent process");
            sleep(1);
        }
    }
    if (p1 == 0)
    {
        p2 = fork();
        if(p2 == 0)
        {
            int counter = 0;
            while(1)
            {
                if (counter == 10)
                {
                    signal(SIGUSR1, handler);
                    exit(0);
                }
                printf("grandchild process\n");
                counter++;
            }
        }
        else if (p2 > 0)
        {
            while(1)
            {   
                printf("child process\n");
                sleep(1);
            }
        }
    }
    exit(0);
}