#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /*STDIN_FILENO, STDOUT_FILENO*/
// task 1 reads in from standard input using the function read, 
// which reads to buffer then using write, write prints buffer to
// standard output which is the screen.
void err_sys(char *str)
{
    printf("%s", str);
    exit (1);
}
int main()
{
    int foo;
    char buffer;   

    while ((foo = read(STDIN_FILENO, &buffer, 1)) > 0)
        if ((write(STDOUT_FILENO, &buffer, 1)) < 0)
        {
            err_sys("error");
        }
    exit (0);
}