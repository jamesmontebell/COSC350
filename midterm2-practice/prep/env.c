#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main()
{
    char **p = environ;
    while(*p != NULL)
    {
        printf("%s (%p)\n", *p);
        *p++;
    }
    return 0;
}