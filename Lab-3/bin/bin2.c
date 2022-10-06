#include <fcntl.h>     /* defines options flags */
#include <sys/types.h> /* defines types used by sys/stat.h */
#include <sys/stat.h>  /* defines S_IREAD & S_IWRITE */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /*STDIN_FILENO, STDOUT_FILENO*/
#define FILE_MODE (S_IRUSR | S_IWUSR)

void err_sys(char *str)
{
    printf("%s", str);
    exit(1);
}

int main()
{
    int foo, sym, offset, n;
    char buf;
    if((foo = open("foo.txt", O_RDONLY)) < 0)
    {
        err_sys("Error1");
    }
    if((sym = open("symmetry.txt", O_RDWR | O_CREAT | O_EXCL, FILE_MODE)) < 0)
    {
        err_sys("Error2");
    }

    if((offset = lseek(foo, 0, SEEK_END)) < 0)
    {
        err_sys("Error3");
    }

    for(int i = offset - 1; i >=0 ; i-- )
    {
        if((lseek(foo, i, SEEK_SET)) < 0)
        {
            err_sys("Error4");
        }
        if((n = read(foo, &buf, 1)) < 0)
        {
            err_sys("Error5");
        }
        if((n = write(sym, &buf, 1)) < 0)
        {
            err_sys("Error6");
        }
    }

    close(foo);
    close(sym);
    exit(0);
}