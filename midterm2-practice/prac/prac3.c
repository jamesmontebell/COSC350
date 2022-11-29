#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void *Bye(void* arg)
{
    printf("bye one\n");
    pthread_cancel((pthread_t)arg);
    pthread_exit(NULL);
}
void *Bye1()
{
   printf("end of prog\n");
   pthread_exit(NULL);
}

void* thread1(void* arg)
{
    pthread_cleanup_push(Bye, (void*)arg);
    while(1)
    {
        printf("im the first\n");
        sleep(1);
        pthread_testcancel();
    }
    pthread_cleanup_pop(0);
}

void* thread2(void* arg)
{
    int counter = 0;
    while(1)
    {
        if (counter == 10)
        {
            pthread_cancel((pthread_t)arg);
        }
        printf("second thread\n");
        sleep(1);
        counter++;
    }
}

int main()
{
    pthread_t thread[2];
    pthread_t self = pthread_self();

    int rc;

    rc = pthread_create(&thread[0], NULL, thread1, (void*)self);
    rc = pthread_create(&thread[1], NULL, thread2, (void*)thread[0]);
    pthread_cleanup_push(Bye1, NULL);
    while(1)
    {
        printf("og thread\n");
        sleep(1);
        pthread_testcancel();
    }
    pthread_cleanup_pop(0);
    exit(0);
}
