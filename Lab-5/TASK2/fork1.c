#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void err_sys(char *str)
{
    printf("%s", str);
    exit(1);
}

int Atoi(char *str)
{
    int i = 0;
    int res = 0;
    while (str[i] != '\0')
    {
        res = 10 * res + str[i] - '0';
        i++;
    }
    return res;
}

int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        err_sys("arg error");
    }

    int Nc = Atoi(argv[1]);
    int Np = Atoi(argv[2]);
    int Tc = Atoi(argv[3]);
    int Tp = Atoi(argv[4]);

    pid_t pid;
    char *message;
    int n;
    int time;
    printf("fork program starting\n");
    pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork failed");
        exit(1);
    case 0:
        message = "This is the child";
        n = Nc;
        time = Tc;
        break;
    default:
        message = "This is the parent";
        n = Np;
        time = Tp;
        break;
    }
    for (; n > 0; n--)
    {
        puts(message);
        sleep(time);
    }
    exit(0);
}