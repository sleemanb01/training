#include <stdio.h>  /* printf() */
#include <stdlib.h> /* atoi()   */
#include <string.h> /* strcmp() */
#include <pthread.h>/* pthreads */
#include <signal.h> /* atomic   */
#include <unistd.h> /* sleep    */

#define THREADS_NUMBER 2
#define BUFFER_SIZE 10

void FillArr();
void ReadArr();
void* Consumer(void *arg);
void* Producer(void *arg);

int buffer[BUFFER_SIZE];
sig_atomic_t flag = 0;    /* 0 - write, 1 - read */


/****************************** MAIN *************************************/

int main(int argc, char *argv[])
{
    pthread_t tid[THREADS_NUMBER];
    unsigned int i;
    time_t t;

    srand((unsigned) time(&t));

    for(i = 0; i < THREADS_NUMBER; ++i)
    {
        if(0 == (i%2))
        {
            if(pthread_create(&(tid[i]), NULL, Producer, NULL))
            {
                printf("***THREAD CREATION ERROR %d\n", i);
            }
        }
        else
        {   
            if(pthread_create(&(tid[i]), NULL, Consumer, NULL))
            {
                printf("***THREAD CREATION ERROR %d\n", i);
            }
        }
    }

   pthread_join(tid[0], NULL);
   pthread_join(tid[1], NULL);

    return 0;
}

/****************************** FUNCS ************************************/
void FillArr()
{   
    int i;
  

    for(i = 0; i < BUFFER_SIZE; ++i)
    {
       buffer[i] = rand() % 100;
    }
}

void ReadArr()
{
    int i;

    printf("\n");

    for(i = 0; i < BUFFER_SIZE; ++i)
    {
       printf("%d ",buffer[i]);
    }

    printf("\n");
}

void* Producer(void *arg)
{
    while(1)
    {
        if(0 == flag)
        {
            FillArr();
            sleep(2);
            flag =1;
        }
    }

    return NULL;
}

void* Consumer(void *arg)
{
    while(1)
    {
        if(1 == flag)
        {
            ReadArr();
            flag = 0; 
        }
    }

    return NULL;
}
