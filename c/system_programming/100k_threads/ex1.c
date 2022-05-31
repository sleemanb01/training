#include <pthread.h>
#include <stdio.h>   /* printf() */
#include <time.h>    /* time() */
#include <unistd.h>  /* sleep() */
#include <omp.h>     /* openMP */


#define NUM 1

pthread_t tid[NUM];
size_t arr[NUM];
size_t number = 1234567890;
size_t jump = 0;


void* doSomeThing(void *arg)
{
    int sum_of_divisors = 0;
    size_t i = 0;

    #pragma omp parallel for
    for (i = ((size_t)arg * jump) + 1; i <= (((size_t)arg + 1) * jump); ++i)
    {
        if (0 == number % i)
        {
            sum_of_divisors += 1;
        }
    }
   /*  total_sum += (size_t)sum_of_divisors; */

    return (void*)(size_t)sum_of_divisors;

}

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