#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Atoi(char *num)
{
    int res = 0;
    int sign = 1;
    int i = 0;

    if (num[0] == "-")
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
    if (argc < 2)
    {
        printf("You need at least one integer.\n");
        return -1;
    }

    int sum = 0;
    int nums[argc];

    for (int i = 1; i < argc; i++)
    {
        nums[i] = Atoi(argv[i]);
        printf("%d\n", nums[i]);
    }
    for(int i = 0; i < argc ; i++)
    {
        sum += nums[i];
    }

    printf("%d", sum);

    return 0;
}