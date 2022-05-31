#include <pthread.h>
#include <stdio.h>   /* printf() */
#include <time.h>    /* time() */
#include <unistd.h>  /* sleep() */
#include <omp.h>     /* openMP */



int main(void)
{
    int res = 1, err;
    size_t total_sum = 0, i = 0;
    pthread_attr_t attr;
    int tmp = 1;
    void *add = &tmp;

     jump = number / NUM;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    while(i < NUM)
    {
        do
        {
            err = pthread_create(&(tid[i]), NULL, doSomeThing, (void*)i);
        }
         while(err != 0);
        i++;
    }

     for (i = 0; i < NUM; ++i)
    {
        while(pthread_join(tid[i], &add));
        total_sum += (size_t)add;
    }


    /*printf("threads created\n");

    sleep(10);

    for(i = 0; i < NUM; ++i)
    {
    	if(arr[i] != i)
    	{
    		res = 0;
    		break;
    	}
    }

    if(res)
    {
    	printf("DONE!\n");
    }
    else
    {
    	printf("ERROR\n");
    }*/

     printf("%ld\n", total_sum);

    return 0;
}