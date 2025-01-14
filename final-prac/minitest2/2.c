#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("error");
        exit(0);
    }
    char buf;
    int fd;

    fd = open(argv[1], O_RDONLY);
    int n;
    int c;
    while((n = read(fd, &buf, 1)) > 0)
    {
        c++;
        printf("reading");
    }
    printf("%d\n", c);
    exit(0);
}