#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *firstThread(void *arg)
{
    int sum = 0;
    int n = atoi(arg);
    for(int i = 1; i <= n; i++)
    {
        sum += i;
    }
    printf("Sum of number's digits is %d\n", sum);
    pthread_exit(NULL);
}

void *secondThread(void *arg)
{
    int fac = 1;
    int n = atoi(arg);
    for(int i = 1; i <= n; i++)
    {
        fac *= i;
    }
    printf("The factorial of number is %d\n", fac);
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    pthread_t thread1;
    pthread_t thread2;

    int t1, t2;

    t1 = pthread_create(&thread1, NULL, firstThread, (void*)argv[1]);
    t2 = pthread_create(&thread2, NULL, secondThread, (void*)argv[1]);

    pthread_exit(NULL);

    exit(0);
}