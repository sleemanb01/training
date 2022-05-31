#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define NITER 1000000

int cnt = 0;
sem_t sem;

void *Count(void * a)
{
    int i, tmp;
    for(i = 0; i < NITER; i++)
    {
    	sem_wait(&sem);

        tmp = cnt;  
        tmp = tmp + 1;  
        cnt = tmp;  

        sem_post(&sem);
    }
}

int main(int argc, char * argv[])
{
 	sem_init(&sem, 0 , 1);

    pthread_t tid1, tid2;

    if(pthread_create(&tid1, NULL, Count, NULL))
    {
      printf("\n ERROR creating thread 1");
      exit(1);
    }

    if(pthread_create(&tid2, NULL, Count, NULL))
    {
      printf("\n ERROR creating thread 2");
      exit(1);
    }

    if(pthread_join(tid1, NULL))	/* wait for the thread 1 to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    if(pthread_join(tid2, NULL))        /* wait for the thread 2 to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    if (cnt < 2 * NITER) 
        printf("\n BOOM! cnt is [%d], should be %d\n", cnt, 2*NITER);
    else
        printf("\n OK! cnt is [%d]\n", cnt);
  
    sem_destroy(&sem);
    return 0;
}