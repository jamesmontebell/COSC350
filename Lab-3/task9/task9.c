#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

void error_sys(char *str)
{
    printf("%s", str);
    exit(1);
}

int Atoi(char *num)
{
    int res = 0;
    int i = 0;

    for (; num[i] != '\0'; ++i)
    {
        res = res * 10 + num[i] - '0';
    }

    return res;
}

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        error_sys("Error1");
    }

    int in, out, new;
    char buf[1];
    char buf2[4];


    if((in = open(argv[1], O_RDONLY)) < 0)
    {
        error_sys("Error2");
    }
    if((out = open(argv[2], O_CREAT | O_EXCL | O_WRONLY, FILE_MODE)) < 0)
    {
        error_sys("Error3");
    }
    if((new = dup2(out, 1)) < 0)
    {
        error_sys("error");
    }
    if(in != -1)
    {
        int i = 0;
        while((read(in, &buf, 1)) > 0)
        {
            if(buf[0] == ' ')
            {
                buf2[i] = '\0';
                int res = Atoi(buf2);
                char num = res;
                printf("%c", num);
                i = 0;
            }
            else if (buf[0] == '\n')
            {
                printf("%c", '\n');
            }
            else
            {
                buf2[i] = buf[0];
                i++;
            }
        }
    }
    else
    {
        error_sys("error");
    }
    close(in);
    close(out); 
    return 0;
}
