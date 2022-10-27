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
    if (argc != 3)
    {
        err_sys("arg error");
    }

    int Nc = Atoi(argv[1]);
    int Tc = Atoi(argv[2]);
    int n = Nc;

    pid_t pid = getpid();
    char *message = argv[0];

    for (; n > 0; n--)
    {
        puts(message);
        sleep(Tc);
    }
    exit(37);
}