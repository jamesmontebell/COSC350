
#include <fcntl.h>     /* defines options flags */
#include <sys/types.h> /* defines types used by sys/stat.h */
#include <sys/stat.h>  /* defines S_IREAD & S_IWRITE */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /*STDIN_FILENO, STDOUT_FILENO*/
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP)
// task5 opens the already created file foo,
// then creates a file foorev if its not already created.
// with the created struct buf, get the size stat using fstat()
// which is used in a for loop to decrement the offset from the end of file
// and use pread to set that offset and read the file foo, then write writes
// byte by byte to foorev.
void err_sys(char *str)
{
    printf("%s", str);
    exit(1);
}
int main()
{
    int n, offset;
    int foo, foorev;
    char buffer;
    struct stat buf;

    if((foo = open("foo.txt", O_RDONLY)) < 0)
    {
        err_sys("error");
    }

    if((foorev = open("foorev.txt", O_RDWR | O_CREAT | O_EXCL, FILE_MODE)) < 0)
    {
        err_sys("error");
    }

    // if ((offset = lseek (foo, 0, SEEK_END))== -1)
    // {
    //     err_sys("error");
    // }

    printf("foo.txt opened for read access\n");

    fstat(foo, &buf);
    off_t size = buf.st_size;

    for(int i = size-1; i >=0; i--)
    {
        // if ((lseek(foo, i, SEEK_SET)) < 0)
        // {
        //     err_sys("error");
        // }
        if((n = pread(foo, &buffer, 1, i)) < 0)
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