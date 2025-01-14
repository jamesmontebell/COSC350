#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void Bye1(void* arg)
{
    printf("bye 1");
}

void *Thread1(void *arg)
{
    int count = 1;
    printf("enter first thread\n");
    while(count != 10)
    {
        printf("%d\n", count);
        sleep(1);
        count++; 
    }
    pthread_t tid = (pthread_t)arg;
    printf("trying to cancel thread2\n");
    pthread_cancel(tid);
}

void *Thread2(void *arg)
{
    printf("enter second thread\n");
    pthread_cleanup_push(Bye1, NULL);
    while(1)
    {
        pthread_testcancel();
        printf("second thread\n");
        sleep(1);
    }
    pthread_cleanup_pop(0);
    printf("exit second thread\n");
}

int main()
{
    pthread_t threads[2];
    void *t1, *t2;
    t2 = pthread_create(&threads[1], NULL, Thread2, NULL);
    t1 = pthread_create(&threads[0], NULL, Thread1, (void*)t2);
    pthread_join(threads[0], &t1);
    pthread_join(threads[1], &t2);
    return 0;
}