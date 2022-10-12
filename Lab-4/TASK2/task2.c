#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void err_sys(char *str)
{
    printf("%s", str);
    exit(1);
}

int palind(int fd1, int fd2)
{
    char buf1, buf2;
    struct stat buf;
    int i, n;

    fstat(fd2, &buf);
    off_t size = buf.st_size;

    for (i = size - 1; i >=0; i--)
    {
        if((n = read(fd1, &buf1, 1)) < 0)
        {
            err_sys("error");
        }

        if((n = pread(fd2, &buf2, 1, i)) < 0)
        {
            err_sys("error");
        }

        if (buf1 != buf2)
        {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[])
{
    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = dup(fd1);
    int isPalind = palind(fd1, fd2);
    printf("%d", isPalind);
    return 0;
}