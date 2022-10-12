#include <fcntl.h>     /* defines options flags */
#include <sys/types.h> /* defines types used by sys/stat.h */
#include <sys/stat.h>  /* defines S_IREAD & S_IWRITE */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /*STDIN_FILENO, STDOUT_FILENO*/
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP)
// task5 opens the already created file foo,
// then creates a file foorev if its not already created.
// Then set current offset to the end of file of foo.
// Next in a for loop that decrements the offset, set the offset to the
// newly decremented offset, then read foo byte by byte, and write byte
// by byte to foorev.
void err_sys(char *str)
{
    printf("%s", str);
    exit(1);
}
int main()
{
    int n;
    int foo, foorev, offset;
    char buffer;    

    if((foo = open("foo.txt", O_RDONLY)) < 0)
    {
        err_sys("error");
    }

    if((foorev = open("foorev.txt", O_RDWR | O_CREAT | O_EXCL, FILE_MODE)) < 0)
    {
        err_sys("error");
    }

    if ((offset = lseek (foo, 0, SEEK_END))== -1)
    {
        err_sys("error");
    }

    printf("foo.txt opened for read access\n");

    for(int i = offset - 1; i >=0; i-- )
    {
        if ((lseek(foo, i, SEEK_SET)) < 0)
        {
            err_sys("error");
        }
        if((n = read(foo, &buffer, 1)) < 0)
        {
            err_sys("error");
        }
        if((n = write(foorev, &buffer, 1)) < 0)
        {
            err_sys("error");
        }
    }
    close(foo);
    close(foorev);
    exit (0);
}