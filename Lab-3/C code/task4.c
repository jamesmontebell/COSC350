#include <fcntl.h>     /* defines options flags */
#include <sys/types.h> /* defines types used by sys/stat.h */
#include <sys/stat.h>  /* defines S_IREAD & S_IWRITE */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /*STDIN_FILENO, STDOUT_FILENO*/
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP)
// task4 opens the already created file foo, and the
// already created file foo1,
// then creates a file foo12 if its not already created.
// Then if foo and foo1 doesn't open with an error, read foo byte by byte to buffer
// then write byte by byte to file foo12, then set the offset to the end of file
// then read foo1 byte by byte then write byte by byte to foo12.
void err_sys(char *str)
{
    printf("%s", str);
    exit(1);
}
int main()
{
    int foo, foo1, foo12, offset;
    char buffer;

    if((foo = open("foo.txt", O_RDWR)) < 0)
    {
        err_sys("error");
    }

    if((foo1 = open("foo1.txt", O_RDWR)) < 0)
    {
        err_sys("error");
    }

    if((foo12 = open("foo12.txt", O_RDWR | O_CREAT | O_EXCL, FILE_MODE)) < 0)
    {
        err_sys("error");
    }

    if (foo != -1 && foo1 != -1)
    {
        printf("foo.txt opened for read access\n");
        while ((read(foo, &buffer, 1) > 0))
        {
            write(foo12, &buffer, 1);
        }
        if ((offset = lseek (foo12, 0, SEEK_CUR))== -1)
        {
             err_sys("error");
        }

        printf("Copied contents of foo1.txt to foo12.txt");
        
        printf("foo.txt opened for read access\n");
        while ((read(foo1, &buffer, 1) > 0))
        {
            write(foo12, &buffer, 1);
        }
        printf("Copied contents of foo.txt to foo12.txt");
    }
    else
    {
        err_sys("error");
    }
    close(foo);
    close(foo1);
    close(foo12);
    return 0;
}