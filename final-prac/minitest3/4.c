#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd1 = open(argv[1], O_RDONLY);
    pid_t pid;
    pid = fork();
    char buf;
    int i, j;
    int size = lseek(fd1, 0, SEEK_END);
    if (pid > 0)
    {
        int fd2 = open("parent.txt", O_WRONLY | O_CREAT, 0666);
        for(i = 0; i < size; i++)
        {
            lseek(fd1, i, SEEK_SET);
            read(fd1, &buf, 1);
            write(fd2, &buf, 1);
        }
    }
    else if (pid == 0)
    {
        int fd3 = open("child.txt", O_WRONLY | O_CREAT, 0666);
        for(j = 0; j < size; j++)
        {
            lseek(fd1, j, SEEK_SET);
            read(fd1, &buf, 1);
            write(fd3, &buf, 1);
        }
    }
    exit(0);
    
}