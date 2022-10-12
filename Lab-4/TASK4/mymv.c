#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void err_sys(char *str)
{
    printf("%c", str);
    exit(1);
}

int main(int argc, char *argv[])
{
    int len1 = strlen(argv[1]);
    int len2 = strlen(argv[2]);

    struct stat buf;
    stat(argv[2], &buf);

    char path[(len1 + len2)];

    if(S_ISDIR(buf.st_mode))
    {
        sprintf(path, "%s", argv[2]);
        sprintf(path, "%s/%s", path, argv[1]);

        link(argv[1], path);
        unlink(argv[1]);
    }
    else
    {
        sprintf(path, "%s", argv[2]);
        sprintf(path, "%s/%s", path, argv[1]);
        mkdir(argv[2], 0777);

        link(argv[1], path);
        unlink(argv[1]);
    }
    return 0;
}