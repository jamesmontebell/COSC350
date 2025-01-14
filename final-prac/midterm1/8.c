#include <stdio.h>
#include <stdlib.h>
int st_to_int(char *);
void main(int argc, char *argv[])
{
    int i, sum;
    sum = 0;
    if (argc <= 1) // argument must be at least two or more
    {
        printf("argument number error \n");
        exit(1);
    }
    for (i = 1; i < argc; i++)
    {
        if (st_to_int(argv[i]) % 2 == 1)
            continue;
        sum = sum + st_to_int(argv[i]);
    }
    printf("The sum of argument is %d\n", sum);
    return;
}

int st_to_int(char *str)
{
    int num = 0;
    int i = 0;
    while (str[i] != '\0')
    {
        num = 10 * num + (str[i] - '0');
        i++;
    }
    return num;
}