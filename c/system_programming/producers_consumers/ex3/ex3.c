#include <pthread.h>         /* thread   */
#include <stdio.h>           /* printf() */
#include <time.h>            /* time()   */
#include <unistd.h>          /* sleep()  */
#include <stdlib.h>   
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

#include "dlist.h"

#define THREADS_NUMBER 4
#define UNUSED(x) (void)x

void Release();
void* Consumer(void *arg);
void* Producer(void *arg);

pthread_mutex_t lock;
sem_t *semaphore = NULL;

dlist_t *list = NULL;

/****************************** MAIN *************************************/

int main(int argc, char *argv[])
{
    pthread_t tid[THREADS_NUMBER];
    unsigned int i;
    time_t t;
    list = DlistCreate();

    srand((unsigned) time(&t));

    (void)argc;

    if(NULL == list)
    {
        printf("***LIST CREATION FAILED***\n");
        Release()
        return 1;
    }

    semaphore = sem_open(argv[1], O_CREAT, 0777, 0);
    if (NULL == semaphore)
    {
         printf("***SEMAPHORE ERROR***\n");
         Release()
        return 1;
    }

    if ((pthread_mutex_init(&lock, NULL) != 0))
    {
        printf("***MUTEX INIT FAILED***\n");
        Release()
        return 1;
    }

    for(i = 0; i < THREADS_NUMBER; ++i)
    {
        if(2 > i)
        {

            if(pthread_create(&(tid[i]), NULL, Producer, NULL))
            {
                printf("***THREAD CREATION ERROR *** %d\n", i);
                Release()
                return 1;
            }
        }
        else
        {   
            if(pthread_create(&(tid[i]), NULL, Consumer, NULL))
            {
                printf("***THREAD CREATION ERROR *** %d\n", i);
                Release()
                return 1;
            }
        }
    }

     for(i = 0; i < THREADS_NUMBER; ++i)
     {
         pthread_join(tid[i], NULL);
     }

    Release();

    return 0;
}

/****************************** FUNCS ************************************/

void Release()
{
    pthread_mutex_destroy(&lock);
    sem_unlink(argv[1]);
    DlistDestroy(list);
    printf("\n");
}

void* Producer(void *arg)
{
    UNUSED(arg);

    while(1)
    {
        int n = (rand() % 100);
        sleep(1); /* due to use of time in random */
        
        pthread_mutex_lock(&lock);
        DlistPushFront(list,&n);
        sem_post(semaphore); 
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

void* Consumer(void *arg)
{
    UNUSED(arg);

    while(1)
    {
        fflush(stdout);
        sem_wait(semaphore);
        printf("%d ", *(int*)(DlistPopBack(list)));
    }

    return NULL;
}