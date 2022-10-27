#include <fcntl.h>     /* defines options flags */
#include <sys/types.h> /* defines types used by sys/stat.h */
#include <sys/stat.h>  /* defines S_IREAD & S_IWRITE */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /*STDIN_FILENO, STDOUT_FILENO*/

int isDigit(int c)
{
    if (c >= 48 && c <= 57)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void err_sys(char *str)
{
    printf("%s", str);
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        err_sys("input error");
    }

    int in;
    int parentOut, childOut;
    int pOff = 0;
    int cOff = 0;
    int pid;
    char buf;
    int exit_code;

    if ((in = open(argv[1], O_RDWR)) < 0)
    {
        err_sys("error1");
    }
    if ((parentOut = open("parent.txt", O_WRONLY | O_CREAT | O_EXCL, 0777)) < 0)
    {
        err_sys("error2");
    }
    if ((childOut = open("child.txt", O_WRONLY | O_CREAT | O_EXCL, 0777)) < 0)
    {
        err_sys("error3");
    }

    pid = fork();

    switch (pid)
    {

    case -1:
        err_sys("error4");
        exit(1);
    case 0:
        exit_code = 37;
        while (pread(in, &buf, 1, cOff) == 1)
        {
            if (isDigit(buf) == 0)
            {
                write(childOut, &buf, 1);
            }
            cOff++;
        }
        break;
    default:
        exit_code = 0;
        while (pread(in, &buf, 1, pOff) == 1)
        {
            if (isDigit(buf) == 1)
            {
                write(parentOut, &buf, 1);
            }
            pOff++;
        }

        break;
    }
    exit(exit_code);
}