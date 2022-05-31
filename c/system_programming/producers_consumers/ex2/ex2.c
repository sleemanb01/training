#include <pthread.h> /* thread   */
#include <stdio.h>   /* printf() */
#include <time.h>    /* time()   */
#include <unistd.h>  /* sleep()  */
#include <stdlib.h>   

#include "dlist.h"

#define THREADS_NUMBER 16
#define UNUSED(x) (void)x

void* Consumer(void *arg);
void* Producer(void *arg);

pthread_mutex_t lock;

dlist_t *list = NULL;

/****************************** MAIN *************************************/

int main()
{
    pthread_t tid[THREADS_NUMBER];
    unsigned int i;
    time_t t;
    list = DlistCreate();

    if(NULL == list)
    {
        printf("***LIST CREATION FAILED***\n");
        return 1;
    }

    if ((pthread_mutex_init(&lock, NULL) != 0))
    {
        printf("***MUTEX INIT FAILED***\n");
        return 1;
    }
    srand((unsigned) time(&t));

    for(i = 0; i < THREADS_NUMBER; ++i)
    {
        if(10 > i)
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
    DlistDestroy(list);

    printf("\n");
    return 0;
}

/****************************** FUNCS ************************************/

void* Producer(void *arg)
{

    UNUSED(arg);

    while(1)
    {
        int n;
        
        n = (rand() % 100);

        sleep(1); /* due to use of time in random */
        
        pthread_mutex_lock(&lock);
        DlistPushFront(list,&n);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void* Consumer(void *arg)
{
    UNUSED(arg);

    while(1)
    {
        pthread_mutex_lock(&lock);
        fflush(stdout);

        while (!DlistIsEmpty(list))
        {
            int *n = (int*)(DlistPopBack(list));
            if(NULL != n)
            {
                printf("%d ", *n);
            }
        } 

        pthread_mutex_unlock(&lock);
    }

    return NULL;
}