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

int main()
{
    mkdir("/Users/jamesmontebell/Github/COSC350/Lab-4/task3/home/separk", 0777);
    mkdir("/Users/jamesmontebell/Github/COSC350/Lab-4/task3/home/separk/Dir1", 0777);
    mkdir("/Users/jamesmontebell/Github/COSC350/Lab-4/task3/home/separk/Dir2", 0777);
    mkdir("/Users/jamesmontebell/Github/COSC350/Lab-4/task3/home/separk/Dir2/Dir21", 0777);

    int in, out;
    char buf;

    if((in = open("hello", O_RDONLY)) < 0)
    {
        err_sys("error1");
    }

    if((out = open("/Users/jamesmontebell/Github/COSC350/Lab-4/task3/home/separk/Dir2/Dir21/hello", O_CREAT | O_EXCL | O_WRONLY, 0777)) < 0)
    {
        err_sys("error2");
    }

    if(in != -1)
    {
        while((read(in, &buf, 1)) > 0)
        {
            write(out, &buf, 1);
        }
    }

    int sym, sym2;
    if((sym = symlink("/Users/jamesmontebell/Github/COSC350/Lab-4/task3/home/separk/Dir2/Dir21", "/Users/jamesmontebell/Github/COSC350/Lab-4/task3/home/separk/Dir1/toDir21")) < 0)
    {
        err_sys("error3");
    }

    if((sym2 = symlink("/Users/jamesmontebell/Github/COSC350/Lab-4/task3/home/separk/Dir2/Dir21/hello", "/Users/jamesmontebell/Github/COSC350/Lab-4/task3/home/separk/Dir1/toHello")) < 0)
    {
        err_sys("error4");
    }

    close(in);
    close(out);
    return 0;
}