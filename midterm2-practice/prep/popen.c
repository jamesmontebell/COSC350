#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char buf[80];
    int n1 , n2;
    FILE *ptr = popen("./io", "r");
    while(fgets(buf, 80, ptr))
    {
        if(sscanf(buf, "%d %d", &n1, &n2) == 2)
        {
            printf("%d\n", n1+n2);
        }
        else
        {
            printf("bad input\n");
        }
    }
    exit(0);
}