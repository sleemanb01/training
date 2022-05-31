/************************************************************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : COUNTING_SORT_MUL
* REVIEWER NAME : ALON
************************************************************************************************/

#include <stddef.h>         /* size_t  */ 
#include <stdlib.h>         /* malloc  */
#include <assert.h>         /* assert  */
#include <pthread.h>        /* threads */
#include <string.h>         /* memcpy  */
#include <unistd.h>
#include <stdio.h>

#include "count_sort_multi.h"

/****************************** GLOBAL *************************************/

#define THREADS 8

unsigned int *count_arr = NULL;
size_t range;
void *sorted_arr;
pthread_t threads[THREADS];
pthread_mutex_t mutex;

/****************************** TLS STRUCT *************************************/

typedef struct tls
{
    get_index_ty func;
    size_t jump;
    size_t ea_size;
    size_t offset;
    size_t begin;
    size_t negative;
    unsigned int *count_arr;
    void *arr;

}tls_ty;

/****************************** FUNCS *************************************/

void *Sort(void *count);
void *Count(void *count);
void *UpdateOriginal(void *count);

static ssize_t GetMax(void *arr, size_t size, size_t ea_size, get_index_ty func);
static ssize_t GetMin(void *arr, size_t size, size_t ea_size, get_index_ty func);

static void GetRange(void *arr, size_t size, size_t ea_size, get_index_ty func, size_t *negative);
static void InitTls(tls_ty *tls_arr, size_t size, size_t ea_size, void *arr, get_index_ty func, size_t negative);

/****************************** MAIN *************************************/

int CountingSort(void *base, size_t nmemb, size_t size, get_index_ty get_index_func)
{
	size_t i = 0;
    size_t negative = 0;
    tls_ty tls_arr[THREADS];
	
    assert(NULL != base);
    if (size <= 1)
	{
		return 1;
	}

    pthread_mutex_init(&mutex, NULL);
	
    GetRange(base, nmemb, size, get_index_func, &negative);
	
	count_arr = calloc(range, sizeof(unsigned int));
	if (NULL == count_arr)
	{
		return 1;
	}

	sorted_arr = calloc(nmemb, size);
	if (NULL == sorted_arr)
	{
		free(count_arr);
        return 1;
    }

    InitTls(tls_arr, nmemb, size, base, get_index_func, negative);

    for (i = 0; i < THREADS; ++i)
	{	
        if(pthread_create(&threads[i], NULL, Count, &tls_arr[i]))
        {
            printf("***THREAD CREATE ERROR %lu", i);
            return 1;
        }
	}
    for (i = 0; i < THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }

	for (i = 1; i < range; ++i)
	{	
		count_arr[i] += count_arr[i - 1];
	}
     
    for (i = 0; i < THREADS; ++i)
	{	
        if(pthread_create(&threads[i], NULL, Sort, &tls_arr[i]))
        {
            printf("***THREAD CREATE ERROR %lu", i);
            return 1;
        }
	}
    for (i = 0; i < THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }

	for (i = 0; i < THREADS; ++i)
	{	
        if(pthread_create(&threads[i], NULL, UpdateOriginal, &tls_arr[i]))
        {
            printf("***THREAD CREATE ERROR %lu", i);
            return 1;
        }
	}
    for (i = 0; i < THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }
	
    for (i = 0; i < THREADS; ++i)
    {
        free(tls_arr[i].count_arr);
    }

	free(count_arr);
	free(sorted_arr);
    pthread_mutex_destroy(&mutex);

    return 0;
}

/****************************** FUNCS *************************************/

static void InitTls(tls_ty *tls_arr, size_t size, size_t ea_size, void *arr, get_index_ty func, size_t negative)
{
    size_t i = 0;
    size_t jump = 0;

    jump = size / THREADS;

    for (i = 0; i < THREADS; ++i)
	{	
        tls_arr[i].arr = arr;
        tls_arr[i].negative = negative;
        tls_arr[i].offset = i * jump;
        tls_arr[i].jump = jump;
        tls_arr[i].ea_size = ea_size;
        tls_arr[i].func = func;
        tls_arr[i].count_arr = NULL;

        tls_arr[i].count_arr = calloc(range, sizeof(int));
        if(!tls_arr[i].count_arr)
        {
            printf("*** CALLOC ERROR ***\n");
            return;
        }
	}
    
    tls_arr[i - 1].jump = size - tls_arr[i - 1].offset;
}

/******************************/
static ssize_t GetMax(void *arr, size_t size, size_t ea_size, get_index_ty func)
{
	size_t i = 0;
	ssize_t max = 0, tmp = 0;
	
	for (i = 0; i < size; ++i)
	{
		tmp = func((char*)arr + (i * ea_size));
        if (tmp > max)
		{
			max = tmp;
		}
	}

	return max;
}
/******************************/
static ssize_t GetMin(void *arr, size_t size, size_t ea_size, get_index_ty func)
{
	size_t i = 0;
    ssize_t tmp = 0, min = 0;;
	
	for (i = 0; i < size; ++i)
	{
		tmp = func((char*)arr + (i * ea_size));
        if (tmp < min)
		{
			min = tmp;
		}
	}

	return min;
}

/******************************/
static void GetRange(void *arr, size_t size, size_t ea_size, get_index_ty func, size_t *negative)
{
    ssize_t min = 0, max = 0; 
    
    min = GetMin(arr, size, ea_size, func);
	max = GetMax(arr, size, ea_size, func);
	
	if (0 > min)
	{
		min *= -1;
        *negative = min;
		range = min + max;
	}
	else 
	{
		range = max - min;
	}
    range += 1;
}

/******************************/
void *Count(void *count)
{
    tls_ty *thread = (tls_ty*)count;
    size_t i = 0, size = 0;
    int index = 0;

    i = thread->offset;
    size = i + thread->jump;
    
    for (; i < size; ++i)
	{
        index = (thread->func((char*)thread->arr + (i * thread->ea_size)) + thread->negative);
        thread->count_arr[index] += 1;
	}
    
    pthread_mutex_lock(&mutex);
    for(i = 0; i < range; ++i)
    {
        count_arr[i] += thread->count_arr[i];
    }
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

/******************************/
void *Sort(void *count)
{
    tls_ty *thread = (tls_ty*)count;
    size_t i = 0, size = 0;
    int index = 0;
    void *src = NULL;
    void *dest = NULL;

    i = thread->offset;
    size = (i + thread->jump);

    for (; i < size; ++i)
	{	
        src = (char*)thread->arr + (i * thread->ea_size);
        index = thread->func(src) + thread->negative;
        
        dest = (char*)sorted_arr + (((__sync_fetch_and_sub(&count_arr[index], 1) - 1)) * thread->ea_size);

        memcpy(dest, src, thread->ea_size);
	}

    return NULL;
}

/******************************/
void *UpdateOriginal(void *count)
{
    tls_ty *thread = (tls_ty*)count;
    size_t i = 0, size = 0;
    void *src = NULL;
    void *dest = NULL;

    i = thread->offset;
    size = i + thread->jump;
    
    for (; i < size; ++i)
	{	
        src = ((char*)sorted_arr + (i * thread->ea_size));
        dest = ((char*)thread->arr + (i * thread->ea_size));
        memcpy(dest, src, thread->ea_size);
	}

    return NULL;
}