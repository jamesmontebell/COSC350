#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FILE_MODE (S_IRUSR | S_IWUSR)

int main()
{
    char buf;
    int fd1, fd2;
    int offset;

    fd1 = open("foo.txt", O_RDONLY);
    fd2 = open("palindrome.txt", O_WRONLY | O_CREAT, FILE_MODE);

    while((read(fd1, &buf, 1)) > 0)
    {
        write(fd2, &buf, 1);
    }
    offset = lseek(fd1, 0, SEEK_END);
    printf("%d\n", offset);
    for(int i = offset-1; i >= 0; i--)
    {
        offset = lseek(fd1, i, SEEK_SET);
        read(fd1, &buf, 1);
        write(fd2, &buf, 1);
    }
    exit(0);
}