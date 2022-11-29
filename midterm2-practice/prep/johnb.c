#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid;

    pid = fork();
    if (pid > 0)
    {
        while(1)
        {
            sleep(1);
        }
    }
    else if (pid == 0)
    {
        exit(0);
    }
    exit(0);
}