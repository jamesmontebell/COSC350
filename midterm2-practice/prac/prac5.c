#include <stdlib.h>
#include <unistd.h>

int main()
{
    char buf[80];
    int nread;
    while(nread = read(1, buf, 80))
    {
        write(0, buf, nread);
    }
    return 0;
}