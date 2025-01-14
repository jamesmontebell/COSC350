#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    pid_t ppid = getpid();

    pid = fork();

    if (pid > 0)
    {
        int count = 0;
        while (count < 10)
        {
            printf("i am your parents\n");
            sleep(1);
            count++;
        }
        printf("my job is done\n");
        exit(0);
    }
    else if (pid == 0)
    {
        while (1)
        {
            if (getppid() == ppid)
            {
                printf("i am your child\n");
                sleep(1);
            }
            else
            {
                printf("my parent is done so im done\n");
                exit(0);
            }
        }
    }
    exit(0);
}