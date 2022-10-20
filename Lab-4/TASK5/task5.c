#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void err_sys(char *str)
{
    printf("%s", str);
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        err_sys("arg arror");
    }

    int in, a, n, o, c;
    char buf;

    if((in = open(argv[1],O_RDONLY )) < 0)
    {
        err_sys("file in error");
    }
    if((a = open(argv[2],O_RDWR | O_CREAT, 0777 )) < 0)
    {
        err_sys("file a error");
    }
    if((n = open(argv[3],O_RDWR | O_CREAT, 0777 )) < 0)
    {
        err_sys("file n error");
    }
    if((o = open(argv[4],O_RDWR | O_CREAT, 0777 )) < 0)
    {
        err_sys("file o error");
    }
    if((c = open(argv[5],O_RDWR | O_CREAT, 0777 )) < 0)
    {
        err_sys("file c error");
    }

    

    while((read(in, &buf, 1)) > 0)
    {
        if((int)buf == 10)
        {
            write(a, &buf, 1);
            write(n, &buf, 1);
            write(o, &buf, 1);
        }
        // if((int)buf == 32)
        // {
        //     write(a, &buf, 1);
        //     write(n, &buf, 1);
        //     write(o, &buf, 1);
        // }
        if((int)buf >= 97 && (int)buf <= 122 || (int)buf >= 65 && (int)buf <= 90)
        {
            write(a, &buf, 1);
        }
        else
        {
            write(a, " ", 1);
        }
        if((int)buf >= 48 && (int)buf <= 57)
        {
            write(n, &buf, 1);
        }
        else
        {
            write(n, " ", 1);
        }
        if((int)buf >= 33 && (int)buf <= 47 || (int)buf >= 58 && (int)buf <= 64 || (int)buf >= 91 && (int)buf <= 96 || (int)buf >= 123 && (int)buf <= 127)
        {
            write(o, &buf, 1);
        }
        else
        {
            write(o, " ", 1);
        }
    }
    
    // if((lseek(a, 0, SEEK_SET)) < 0)
    // {
    //     err_sys("lseek error");
    // }

    // while((read(a, &buf, 1)) > 0)
    // {
    //     write(c, &buf, 1);
    // }
    // if((lseek(n, 0, SEEK_SET)) < 0)
    // {
    //     err_sys("lseek error");
    // }
    // while((read(n, &buf, 1)) > 0)
    // {
    //     write(c, &buf, 1);
    // }

    close(in);
    close(a);
    close(n);
    close(o);
    close(c);

    return 0;

}