#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

int main()
{
    pid_t pid;
    int foo, fd1;
    char buf;

    pid = fork();

    switch (pid)
    {
    case -1:
        /* Failure */
        perror("fork failed");
        exit(1);
    case 0:
        /* child */
        foo = open("foo", O_CREAT | O_RDWR, 0777);
        char wrd[] = "Hi, Mom";
        write(foo, &wrd, 7);
        exit(0);
    default:
        wait(&pid);
        fd1 = open("foo", O_RDONLY);
        printf("My son said ");
        while(read(fd1, &buf, 1) > 0) {
			printf("%c", buf);
		}
    }
    exit(0);
}