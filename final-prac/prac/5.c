#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>

void handler(int sig)
{
    if (sig == SIGUSR1)
    {
        printf("I am terminated\n");
        kill(getppid(), SIGUSR2);
        exit(0);
    }
    if(sig == SIGUSR2)
    {
        printf("parent terminated");
        exit(0);
    }
}

int main()
{
    pid_t pid;
    pid = fork();

    if (pid == 0)
    {
        while(1)
        {
            signal(SIGUSR1, handler);
            printf("child is running\n");
            sleep(1);   
        }
    }
    else
    {
        int i = 1;
        while(1)
        {
            if(i == 5)
            {
                kill(pid, SIGUSR1);
            }
            signal(SIGUSR2, handler);
            printf("parent is running\n");
            sleep(1);
            i++;
        }
    }

}