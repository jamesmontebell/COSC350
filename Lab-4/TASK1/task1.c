#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <string.h>

int convIntToStr(char *str, int x)
{
    sprintf(str, "%d", x);
    return (strlen(str));
}

int Atoi(char *str, int size)
{
    int ret = 0, i = 0;
    for (; i < size; i++)
    {
        ret = (ret * 10) + (str[i] - 48);
    }
    return ret;
}

int main(int argc, char *argv[])
{
    int in = open(argv[1], O_RDONLY);
    char str[80], buf;
    int i = 0;

    while (read(in, &buf, 1))
    {
        if ((int)buf >= 48 && (int)buf <= 57)
        {
            str[i] = buf;
            i++;
        }
    }

    close(in);
    int num = Atoi(str, i);
    num += 10;
    convIntToStr(str, num);
    write(1, str, i);
    return 0;
}