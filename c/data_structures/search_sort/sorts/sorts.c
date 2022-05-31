/************************************************************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : MERGE,QUICK SORT
* REVIEWER NAME : THEODOR
************************************************************************************************/

#include <stddef.h>	         /* size_t */ 
#include <stdlib.h>          /* malloc */
#include <assert.h>          /* assert */
#include <string.h>          /* memcpy */

#include "sorts.h"

/***********************************************************************************************
*                                            FUNCS                                             *
************************************************************************************************/

static void merge(int *arr, size_t start, size_t mid, size_t end);
static void mergeSort(int *arr, size_t start, size_t end);

static void quickSort(void *base, size_t min, size_t max, size_t size, sorts_comp_ty comp_func);
static size_t partition (void *base, size_t min, size_t max, size_t size, sorts_comp_ty comp_func);
static void swap(void* a, void* b, size_t size);

/************************************************************************************************
*                   MERGE SORT    
*  Parameters:      array, it's size
*  Return    :      
*  Complexity:      O(n)
************************************************************************************************/

int MergeSort(int *arr_to_sort, size_t num_elements)
{
     mergeSort(arr_to_sort, 0, num_elements - 1);

     return 0;
}

/************************************************************************************************
*                   QUICK SORT     
*  Parameters:      
*  Return    :      
*  Complexity:      O(n)
************************************************************************************************/

int QuickSort(void *base, size_t nmemb, size_t size, sorts_comp_ty comp_func)
{
    assert(NULL != base);

    quickSort(base, 0, nmemb - 1, size, comp_func);
    
    return 0;
}

/***********************************************************************************************
*                                            FUNCS                                             *
************************************************************************************************/

/****************************** MERGE ***********************************/
static void merge(int *arr, size_t start, size_t mid, size_t end)
{
    int *temp = NULL;
	size_t i = start, j = mid+1, k = 0;

    temp = (int*)malloc((end - start + 1) * sizeof(int));
    if(NULL == temp)
    {
        return;
    }

	while(i <= mid && j <= end) 
    {
		if(arr[i] <= arr[j])
        {
			temp[k] = arr[i];
			++k;
            ++i;
		}
		else 
        {
			temp[k] = arr[j];
			++k;
            ++i;
		}
	}

	while(i <= mid) 
    {
		temp[k] = arr[i];
		++k;
        ++i;
	}

	while(j <= end) {
		temp[k] = arr[j];
		++k;
        ++j;
	}

	for(i = start; i <= end; ++i) 
    {
		arr[i] = temp[i - start];
	}

    free(temp);
}

/****************************** MERGE SORT ***********************************/
static void mergeSort(int *arr, size_t start, size_t end)
{
    int i;
    if(start < end) 
    {
		i = (start + end) / 2;
		mergeSort(arr, start, i);
		mergeSort(arr, i+1, end);
		merge(arr, start, i, end);
	}
}

/****************************** PARTITION ***********************************/
static size_t partition (void *base, size_t low, size_t high, size_t size, sorts_comp_ty comp_func)
{
    size_t pivot, i ,j;
    void *pivot_index = NULL;
    void *begin = NULL;
    
    if(low > high)
    {
        return 0;
    }

    pivot = ((low + high)/2);

    i = 0;
    j = low;

    begin = (char*)base + (low * size);
    pivot_index = (char*)base + (pivot * size);

    swap(begin, pivot_index, size);

    for(i = low + 1; i <= high; ++i)
    {
        if(0 < comp_func( (begin), ((char*)base + (i * size))) )
        {
            ++j;
            swap( ((char*)base + (i * size)) , ((char*)base + (j * size)) , size);
        }
    }

     swap(begin,((char*)base + (j * size)), size);

    return j;

}

/****************************** QUICKSORT RECURSIVE **************************/
void quickSort(void *base, size_t low, size_t high, size_t size, sorts_comp_ty comp_func)
{
    size_t pi;

    if(low < high)
    {
        pi = partition(base,low,high,size,comp_func);

        if(0 != pi)
        {
            quickSort(base, low, (pi - 1), size, comp_func);
            quickSort(base, (pi + 1), high, size, comp_func);
        }
    }
}

/****************************** SWAP **************************/
static void swap(void *a, void *b, size_t size)
{
    char *tmp = NULL;

    tmp = malloc(size);
    if(NULL == tmp)
    {
        return;
    }

    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);

}