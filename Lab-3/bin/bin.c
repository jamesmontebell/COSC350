#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void error_sys(char *str)
{
    printf("%s", str);
    exit(1);
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        error_sys("Error1");
    }

    int fd;
    char buf;


    if((fd = open(argv[1], O_RDONLY)) < 0)
    {
        error_sys("Error2");
    }

    // if(fd != 1)
    // {
    //     while ((read(fd, &buf, 1) > 0))
    //     {
    //         printf("reading");
    //     }
    // }
    // else
    // {
    //     error_sys("Error3");
    // }

    printf("%d", fd);
    return 0;
}
