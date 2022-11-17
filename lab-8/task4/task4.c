#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *command;
    int size = 0;
    for(int i = 0; i < argc; i++)
    {
        size += strlen(argv[i]);
    }

    command = malloc(size*sizeof(char));

    for(int i = 1; i < argc; i++)
    {
        sprintf(command, "%s %s", command, argv[i]);
    }

    FILE *ptr;

    char buf[BUFSIZ];

    if((ptr = popen(command, "r")) != NULL)
    {
        while(fgets(buf, BUFSIZ, ptr) != NULL)
        {
            (void) printf("%s", buf);
        }
    }

    pclose(ptr);
    exit(0);
}