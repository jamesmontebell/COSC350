#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void* Bye1()
{
    printf("end of prog");
    pthread_exit(NULL);
}

void* Bye(void* arg)
{
    pthread_cancel((pthread_t)arg);
    printf("cya1");
    pthread_exit(NULL);
}

void* firstThread(void* arg)
{
    pthread_cleanup_push(Bye, (void*)arg );
    while(1)
    {
        pthread_testcancel();
        printf("first thread");
        sleep(1);
    }
    pthread_cleanup_pop(0);
}

void* secondThread(void* arg)
{
    int counter = 0;
    while(1)
    {
        if(counter == 10)
        {
            pthread_cancel((pthread_t) arg);
        }
        printf("second thread");
        sleep(1);
        counter++;
    }
}

int main()
{
    pthread_t t1;
    pthread_t t2;

    pthread_t self = pthread_self();
    pthread_create(&t1, NULL, firstThread, (void*)self);
    pthread_create(&t2, NULL, secondThread, (void*)t1);

    pthread_cleanup_push(Bye1, NULL);
    while(1)
    {
        pthread_testcancel();
        printf("og thread");
        sleep(1);
    }
    pthread_cleanup_pop(0);
    exit(0);
}