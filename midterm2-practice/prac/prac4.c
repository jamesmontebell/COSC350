#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    char buf[80];
    int num1, num2;

    FILE *ptr = popen("./yuh", "r");
    while(fgets(buf, 80, ptr))
    {
        if(sscanf(buf, "%d %d", &num1, &num2) == 2)
        {
            printf("%d\n", num1+num2);
        }
        else
        {
            printf("error\n");
        }
    }
    exit(0);    
}