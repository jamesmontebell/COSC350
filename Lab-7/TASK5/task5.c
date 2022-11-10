#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void handler(int sig)
{
    signal(SIGQUIT, SIG_DFL);
}

int main()
{
    sigset_t mask, mask2, orig_mask;

    sigemptyset(&mask);  // clear signal set
    sigemptyset(&mask2); 

    sigaddset(&mask, SIGINT);
    sigaddset(&mask2, SIGQUIT);

    sigprocmask(SIG_BLOCK, &mask, &orig_mask);  // add blocking for SIGINT
    sigprocmask(SIG_BLOCK, &mask2, &orig_mask); // add blocking for SIGQUIT

    for (int i = 1; i <= 5; i++) 
    {
        printf("%d\n", i);
        sleep(1);
    }

    signal(SIGQUIT, handler);
    signal(SIGINT, handler);

    sigprocmask(SIG_UNBLOCK, &mask2, &orig_mask); // unblock SIGQUIT

    sigemptyset(&mask);  // clear signal set
    sigemptyset(&mask2);

    sigaddset(&mask, SIGINT);
    sigaddset(&mask2, SIGQUIT);

    sigprocmask(SIG_BLOCK, &mask, &orig_mask); // add blocking for SIGINT again

    for (int i = 1; i <= 5; i++) // loop 5 print and wait 5 seconds
    {
        printf("%d\n", i);
        sleep(1);
    }

    exit(0);
}