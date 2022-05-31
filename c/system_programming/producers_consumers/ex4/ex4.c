#include <pthread.h>   /* thread             */
#include <stdio.h>     /* printf()           */
#include <time.h>      /* time()             */
#include <unistd.h>    /* sleep()            */
#include <semaphore.h> /* semaphore          */
#include <fcntl.h>     /* For O_* constants  */
#include <sys/stat.h>  /* For mode constants */
#include <stdlib.h>   

#include "fsq.h"

#define THREADS_NUMBER 4
#define ITERATIONS 500
#define FSQ_SIZE 10
#define UNUSED(x) (void)x

void* Consumer(void *arg);
void* Producer(void *arg);

pthread_mutex_t lock;
sem_t semaphore1;
sem_t semaphore2;

int n;

queue_t *queue = NULL;

/****************************** MAIN *************************************/

int main()
{
    pthread_t tid[THREADS_NUMBER];
    unsigned int i;
    time_t t;

    srand((unsigned) time(&t));
     
    /*semaphore1 = sem_open(argv[1], O_CREAT, 0777, FSQ_SIZE);*/
    if (0 != sem_init(&semaphore1, 0, FSQ_SIZE))
    {
         printf("***SEMAPHORE ERROR***\n");
        return 1;
    }

    
     /*semaphore2 = sem_open(argv[2], O_CREAT, 0777, 0);*/
    if (0 != sem_init(&semaphore2, 0, 0))
    {
         printf("***SEMAPHORE ERROR***\n");
        return 1;
    }

    queue = QueueCreate(FSQ_SIZE);
    if(NULL == queue)
    {
        printf("***QUEUE CREATION FAILED***\n");
        return 1;
    }

    if ((pthread_mutex_init(&lock, NULL) != 0))
    {
        printf("***MUTEX INIT FAILED***\n");
        return 1;
    }

    for(i = 0; i < THREADS_NUMBER; ++i)
    {
        if((THREADS_NUMBER - 2) > i)
        {

            if(pthread_create(&(tid[i]), NULL, Producer, NULL))
            {
                printf("***THREAD CREATION ERROR *** %d\n", i);
                return 1;
            }
        }
        else
        {   
            if(pthread_create(&(tid[i]), NULL, Consumer, NULL))
            {
                printf("***THREAD CREATION ERROR *** %d\n", i);
                return 1;
            }
        }
    }

     for(i = 0; i < THREADS_NUMBER; ++i)
     {
         pthread_join(tid[i], NULL);
     }

    pthread_mutex_destroy(&lock);

    sem_destroy(&semaphore1);
    sem_destroy(&semaphore2);

    printf("\n");
    return 0;
}

/****************************** FUNCS ************************************/

void* Producer(void *arg)
{
    int i;
    UNUSED(arg);

    for(i = 0; i < ITERATIONS; ++i)
    {
        sem_wait(&semaphore1);
        pthread_mutex_lock(&lock);

        n = (rand() % 100);
        
        Enqueue(queue,n);
        sem_post(&semaphore2);

        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void* Consumer(void *arg)
{
    int i;
    UNUSED(arg);

   for(i = 0; i < ITERATIONS; ++i)
    {

        sem_wait(&semaphore2);
        pthread_mutex_lock(&lock);
        printf("%d ", (int)QueuePeek(queue));
        Dequeue(queue);
        sem_post(&semaphore1);
        
        pthread_mutex_unlock(&lock);

    }

    return NULL;
}