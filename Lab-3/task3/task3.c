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
    int foo, clone;
    char buffer[BUFFER_SIZE];
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP)

    foo = open("foo.txt", O_RDWR);
    clone = open("clone2.txt", O_RDWR | O_CREAT | O_EXCL, FILE_MODE);

    if (foo != -1)
    {
        printf("foo.txt opened for read access\n");
        while ((read(foo, buffer, 1) > 0))
        {
            write(clone, buffer, foo);
        }
        printf("Copied contents of foo.txt to clone2.txt");
    }
    else
    {
        err_sys("error");
    }
    close(foo);
    close(clone);
    return 0;
}