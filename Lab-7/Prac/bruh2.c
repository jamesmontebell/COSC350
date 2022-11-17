#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void cleanup(void* arg)
{
    pthread_t tid = (pthread_t)arg;
    int rc;
    printf("first job done");
    rc = pthread_cancel(tid);
}

void stopOG(void* arg)
{
    printf("og done");
}

void *firstThread(void* arg)
{
    pthread_t id = (pthread_t)arg;
    pthread_cleanup_push(cleanup, (void *)id);
    while(1)
    {
        printf("first thread");
        pthread_testcancel();
        sleep(1);
    }    
    pthread_cleanup_pop(0);
}

void *secondThread(void* thread1)
{
    pthread_t id = (pthread_t)thread1;
    for(int i = 0; i < 10 ; i++)
    {
        printf("this is ssecond");
        sleep(1);
    }
    pthread_cancel(id);
    printf("second done");
    return NULL;
}

int main()
{
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    int t1, t2;

    thread3 = pthread_self();

    pthread_cleanup_push(stopOG, NULL);
    t1 = pthread_create(&thread2, NULL, firstThread, (void *)thread3);
    t2 = pthread_create(&thread1, NULL, secondThread, (void *)thread2);
    
    while(1)
    {
        printf("this is og");
        pthread_testcancel();
        sleep(1);
    }
    pthread_cleanup_pop(0);
    return 0 ;
}