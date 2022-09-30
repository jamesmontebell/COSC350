#include <fcntl.h>     /* defines options flags */
#include <sys/types.h> /* defines types used by sys/stat.h */
#include <sys/stat.h>  /* defines S_IREAD & S_IWRITE */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /*STDIN_FILENO, STDOUT_FILENO*/

#define BUFFER_SIZE 32
void err_sys(char *str)
{
    printf("%s", str);
    exit(1);
}
int main()
{
    int foo, foo1, foo12, offset;
    char buffer[BUFFER_SIZE];
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP)

    foo = open("foo.txt", O_RDWR);
    foo1 = open("foo1.txt", O_RDWR);
    foo12 = open("foo12.txt", O_RDWR | O_CREAT | O_EXCL, FILE_MODE);

    if (foo != -1)
    {
        printf("foo.txt opened for read access\n");
        while ((read(foo, buffer, 1) > 0))
        {
            write(foo12, buffer, foo);
        }
        if ((offset = lseek (foo12, 0, SEEK_CUR))== -1)
        {
             err_sys("error");
        }

        printf("Copied contents of foo1.txt to foo12.txt");
        
        printf("foo.txt opened for read access\n");
        while ((read(foo1, buffer, 1) > 0))
        {
            write(foo12, buffer, foo1);
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