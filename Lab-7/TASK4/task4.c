#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handler(int sig)
{
    if (sig == SIGUSR1)
    {
        printf("Hi Honey, Anything wrong?\n");
    }
    else if (sig == SIGUSR2)
    {
        printf("Do you make trouble again?\n");
    }
}

int main()
{
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    int status;
    int Kill;

    pid_t pid1 = fork();
    pid_t pid2;

    if (pid1 < 0)
    {
        printf("fork failed");
        exit(1);
    }
    else if (pid1 == 0)
    {
         // First Child
        kill(getppid(), SIGUSR1);
        exit(0);
    }
    else
    {
        pid2 = fork();

        if (pid2 < 0)
        {
            printf("fork failed");
            exit(1);
        }
        else if (pid2 == 0)
        { 
            // Second Child
            Kill = waitpid(pid1, &status, WUNTRACED);
            kill(getppid(), SIGUSR2);
            exit(0);
        }
        else
        { 
            // Parent
            sigaction(SIGUSR1, &act, NULL);
            pause();

            sigaction(SIGUSR2, &act, NULL);
            pause();

            exit(0);
        }
    }

    return 0;
}
