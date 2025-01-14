#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    char *buf;
    int fd1, fd2, offset;

    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[2], O_WRONLY | O_CREAT, 0760);

    offset = lseek(fd1, 0, SEEK_END);

    while(offset> 0)
    {
        read(fd1, &buf, 1);
        if(buf < '0' || buf > '9')
        {
            write(fd2, &buf, 1);
        }
        lseek(fd1, -2, SEEK_CUR);
        offset--;
    }
    exit(0);

}