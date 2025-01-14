#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sighandler(int sig)
{
    if (sig == SIGUSR1)
    { 
        printf("terminated by my parents\n");
        kill(getppid(), SIGUSR2);
        exit(0);
    }
    else if (sig == SIGUSR2)
    {
        printf("my child gone so am i");
        exit(0);
    }

}

int main()
{
    pid_t pid;
    pid = fork();

    if (pid > 0)
    {
        int i = 0;
        while(1)
        {
            if(i == 9)
            {
                kill(pid, SIGUSR1);
            }
            signal(SIGUSR2, sighandler);
            printf("i am parent\n");
            sleep(1);
            i++;
        }
    }
    else if (pid == 0)
    {
        while(1)
        {
            printf("i am child\n");
            signal(SIGUSR1, sighandler);    
            sleep(1);
        }
    }
}