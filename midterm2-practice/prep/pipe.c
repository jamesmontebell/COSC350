#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    pid_t p;
    int f1[2]; // 0 = read
    int f2[2]; // 1 = write
    char buf[BUFSIZ];
    pipe(f1);
    pipe(f2);

    p = fork();

    if (p > 0)
    {
        close(f1[0]);
        close(f2[1]);
        char* msg = "I love you \n";
        write(f1[1], msg, strlen(msg));

        char* msg2 = malloc(10);
        read(f2[0], msg2, 10);
        printf("my child said %s\n", msg2);
        close(f1[1]);
        close(f2[0]);

    }
    else if (p == 0)
    {
        close(f1[1]);
        close(f2[0]);
        char* msg = "I love you too\n";
        write(f2[1], msg, strlen(msg));

        char* msg2 = malloc(10);
        read(f1[0], msg2, 10);
        printf("my mom said %s\n", msg2);
        close(f1[0]);
        close(f2[1]);
    }
    exit(0);
}