#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd1, fd2, fd3;
    char buf;
    fd1 = open(argv[1], O_RDONLY);

    fd2 = open(argv[2], O_WRONLY | O_CREAT, 0644);
    fd3 = open(argv[3], O_WRONLY | O_CREAT, 0644);

    while((read(fd1, &buf, 1)) > 0)
    {
        if(buf >= '0' && buf <= '9')
        {
            write(fd2, &buf, 1);
        }
        else
        {
            write(fd3, &buf, 1);
        }
    }
    exit(0);
}