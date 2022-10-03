#include <fcntl.h>     /* defines options flags */
#include <sys/types.h> /* defines types used by sys/stat.h */
#include <sys/stat.h>  /* defines S_IREAD & S_IWRITE */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /*STDIN_FILENO, STDOUT_FILENO*/
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP)

void err_sys(char *str)
{
    printf("%s", str);
    exit(1);
}
int main()
{
    int n;
    int foo, foorev;
    char buffer;

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

    for(int i = foo, j = 0; i >=0; i--, j++ )
    {
        // if ((lseek(foo, i, SEEK_SET)) < 0)
        // {
        //     err_sys("error");
        // }
        if((n = pread(foo, &buffer, 1, i)) < 0)
        {
            err_sys("error");
        }
        if((n = pwrite(foorev, &buffer, 1, j)) < 0)
        {
            err_sys("error");
        }
    }
    close(foo);
    close(foorev);
    exit (0);
}