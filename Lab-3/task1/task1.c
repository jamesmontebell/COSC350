#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /*STDIN_FILENO, STDOUT_FILENO*/

#define BUFFER_SIZE 2
void err_sys(char *str)
{
    printf("%s", str);
    exit (1);
}
int main()
{
    int foo;
    char buffer[BUFFER_SIZE];   
    while ((foo = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0)
        if (write(STDOUT_FILENO, buffer, foo) != foo)
            err_sys("Write Error");
    if (foo < 0)
        err_sys("read Error");
    exit (0);
}