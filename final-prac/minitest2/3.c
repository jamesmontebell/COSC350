#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int Atoi(char *num)
{
    int res = 0;
    int sign = 1;
    int i = 0;

    if (num[0] == '-')
    {
        sign = -1;
        i++;
    }

    for (; num[i] != '\0'; ++i)
    {
        res = res * 10 + num[i] - '0';
    }

    return sign * res;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("error");
        exit(1);
    }
    int sum[argc-1];
    int sum1;
    for (int i = 0; i < argc - 1; i++)
    {
        if (Atoi(argv[i+1]) % 2 == 0)
        {
            sum[i] = Atoi(argv[i+1]);
            printf("%d\n", sum[i]);
        }
    }
    for (int i = 0; i < argc; i++)
    {
        sum1 += sum[i];
    }
    printf("%d\n", sum1);
    exit(0);
}