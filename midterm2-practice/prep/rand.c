#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    char *buf;
    char in[BUFSIZ];
    int len;
    read(0, in, BUFSIZ);
    sscanf(in, "%d", &len);
    buf = malloc(len);
    for(int i = 0; i < len; i++)
    {
        buf[i] = rand()%26 +'a';
    }
    write(0, buf, len);
    exit(0);
}