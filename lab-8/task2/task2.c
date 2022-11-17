#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int *arr;
int size = 0;

void *t1(void* arg)
{
    int test[20];
	int score, nread, i;
	char buffer[BUFSIZ];

	printf("Enter a test score\n");
	while(size < 20 && (nread=read(0, &buffer, BUFSIZ))>0)
	{
		sscanf(buffer, "%d", &score);
		test[size] = score;
		size++;
		printf("Enter a test score\n");
	}

	arr = (int*)malloc(size*sizeof(int));

	for(i = 0; i< size; i++)
		arr[i] = test[i];

	pthread_exit(NULL);
}

void *t2(void* arg)
{
    int sum = 0;
    for(int i = 0 ; i < size; i++)
    {
        sum += arr[i];
    }
    float average = sum/size;
    printf("Average: %.2f\n", average);

    float median;
    int *temp = (int*) malloc(size*sizeof(int));
    for(int i = 0; i < size; i++)
    {
        temp[i] = arr[i];
    }

	for(int j = 0; j < size; j++)
	{
		for(int k = j+1; k < size ; k++)
		{
			if(temp[k] < temp[j])
			{
				int t = temp[j];
				temp[j] = temp[k];
				temp[k] = t;
			}
		}
	}

    if(size % 2 == 0)
    {
        median = (float)(temp[(size / 2) - 1] + temp[(size / 2)]) / 2;
    }
    else
    {
        median = (float)(temp[(size / 2)]);
    }

    printf("Median: %.2f\n", median);

    free(temp);
    pthread_exit(NULL);
}

void *t3(void* arg)
{
    int max = 0;
    int min = arr[0];

    for(int i = 0 ; i < size; i++)
    {
        if(arr[i] > max)
            max = arr[i];
    }
    for(int i = 0 ; i < size; i++)
    {
        if(arr[i] < min)
            min = arr[i];
    }

    printf("Max: %d\n", max);
    printf("Min: %d\n", min);

    pthread_exit(NULL);
}

void *t4(void* arg)
{
    for(int i = 0; i < size; i++)
    {
        arr[i] = 0;
		printf("%d\n", arr[i]);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;

    int rc;
    void *wait;

    rc = pthread_create(&thread1, NULL, t1, NULL);
    if(rc != 0)
	{
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(1);
	}

    rc = pthread_join(thread1, &wait);
    if(rc != 0)
	{
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(1);
	}

    rc = pthread_create(&thread2, NULL, t2, NULL);
    if(rc != 0)
	{
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(1);
	}

    rc = pthread_create(&thread3, NULL, t3, NULL);
    if(rc != 0)
	{
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(1);
	}

    rc = pthread_join(thread2, &wait);
    if(rc != 0)
	{
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(1);
	}

    rc = pthread_join(thread3, &wait);
    if(rc != 0)
	{
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(1);
	}

    rc = pthread_create(&thread4, NULL, t4, NULL);
    if(rc != 0)
	{
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(1);
	}

    pthread_exit(NULL);
    free(arr);
    return 0;
}