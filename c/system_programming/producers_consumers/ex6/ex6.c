#include <pthread.h>   /* thread             */
#include <stdio.h>     /* printf()           */
#include <time.h>      /* time()             */
#include <unistd.h>    /* sleep()            */
#include <semaphore.h> /* semaphore          */
#include <fcntl.h>     /* For O_* constants  */
#include <sys/stat.h>  /* For mode constants */
#include <stdlib.h>   

#define THREADS_NUMBER 4
#define PRODUCERS 1
#define FSQ_SIZE 100
#define ITERATIONS 9
#define UNUSED(x) (void)x

void* Consumer(void *arg);
void* Producer(void *arg);

pthread_mutex_t lock;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

sem_t *semaphore = NULL;

int n = 0;

/****************************** MAIN *************************************/

int main(int argc, char *argv[])
{
    pthread_t tid[THREADS_NUMBER];
    unsigned int i;
    time_t t;

    srand((unsigned) time(&t));

    (void)argc;
    semaphore = sem_open(argv[1], O_CREAT, 0777, 0); /*************************************************/
    if (NULL == semaphore)
    {
         printf("***SEMAPHORE ERROR***\n");
        return 1;
    }

    if ((pthread_mutex_init(&lock, NULL) != 0))
    {
        printf("***MUTEX INIT FAILED***\n");
        return 1;
    }

    for(i = 0; i < THREADS_NUMBER; ++i)
    {
        if(PRODUCERS > i)
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
    sem_unlink(argv[1]);

    printf("\n");
    return 0;
}

/****************************** FUNCS *****************************1*******/

void* Producer(void *arg)
{
    int prod_i;
    UNUSED(arg);

    for(prod_i = 0 ; prod_i < ITERATIONS; ++prod_i)
    {
        int i;

        for(i = 0; i < (THREADS_NUMBER - 1); ++i)
        {
            sem_wait(semaphore);
        }

        pthread_mutex_lock(&lock);
        
        n = (rand() % 100);

        while(pthread_cond_broadcast(&cond) != 0);

        pthread_mutex_unlock(&lock);    
    }
    return NULL;
}

void* Consumer(void *arg)
{
    int con_i;
    UNUSED(arg);

    for(con_i = 0 ; con_i < ITERATIONS; ++con_i)
    {
        pthread_mutex_lock(&lock);

        sem_post(semaphore);
        while(pthread_cond_wait(&cond, &lock) != 0);

        printf("TID - %ld > %d\n",pthread_self(), n);

        pthread_mutex_unlock(&lock);
    }

    return NULL;
}