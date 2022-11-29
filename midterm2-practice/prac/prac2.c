#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int n, fd1[2], fd2[2]; // [0] = READ, [1] = WRITE

    pid_t pid;
    pipe(fd1);
    pipe(fd2);

    pid = fork();
    
    if (pid > 0)
    {
        // write to parent

       char* msg = "Hi mom\n";
       close(fd1[0]); // closing child read
       close(fd2[1]); // closing parent write

       char* prec = malloc(10);
       write(fd1[1], msg, strlen(msg));

       // read from parent
       read(fd2[0], prec, 10);
       printf("My mom said %s\n", prec);

       close(fd1[1]); // closing child write
       close(fd2[0]); // closing parent read
    }
    if (pid == 0)
    {
        char* msg = "I love you\n";
        close(fd1[1]); // closing child write
        close(fd2[0]); // closing parent read

        char* prec = malloc(7);
        read(fd1[0], prec, 7);
        printf("My child said %s\n", prec);
        write(fd2[1], msg, strlen(msg));

        close(fd1[0]); // closing child read
        close(fd2[1]); // closing parent write
    }
    exit(0);
}