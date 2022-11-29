#include <stdio.h>
#include <unistd.h>

int main()
{
    char buf[80];
    int n;
    while(n = read(0, buf, 80))
    {
        write(0, buf, n);
    }
    return 0;
}