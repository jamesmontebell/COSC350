#include <fcntl.h>     /* defines options flags */
#include <sys/types.h> /* defines types used by sys/stat.h */
#include <sys/stat.h>  /* defines S_IREAD & S_IWRITE */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /*STDIN_FILENO, STDOUT_FILENO*/
 #define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

void err_sys(char *str)
{
    printf("%s", str);
    exit(1);
}
int main()
{
    int foo, clone;
    char buffer;

    if((foo = open("foo.txt", O_RDWR)) < 0)
    {
        err_sys("error");
    }
    if((clone = open("clone1.txt", O_RDWR | O_CREAT | O_EXCL, FILE_MODE)) < 0)
    {
        err_sys("error");
    }

    if(foo != 1)
    {
        printf("foo.txt opened for read access\n");
        while ((read(foo, &buffer, 1) > 0))
        {
            write(clone, &buffer, 1);
        }
        printf("Copied contents of foo.txt to clone1.txt");
    }
    else
    {
        err_sys("error");
    }

    close(foo);
    close(clone);
    return 0;
}