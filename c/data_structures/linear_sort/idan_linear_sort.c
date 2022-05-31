#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

#include "linear_sort.h"

int GetMax(int *arr, size_t size)
{
	int max = 0;
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	return (max);
}

int GetMin(int *arr, size_t size)
{
	int min = 0;
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		if (arr[i] < min)
		{
			min = arr[i];
		}
	}
	return (min);
}


void CountingSort(int *arr, size_t size)
{
	int i = 0, min = 0, max = 0, zero = 0, *sort_arr = NULL, *sorted = NULL;
	size_t range = 0;
	assert(NULL != arr);
	
	if ((size <= 1) || (NULL == arr))
	{
		return;
	}
	
	min = GetMin(arr, size);
	max = GetMax(arr, size);
	
	if (0 > min)
	{
		min = 1 + (~min);
		zero = min;
		range =(size_t)(min + max);
	}
	else 
	{
		range = max;
	}
	range += 1;
	
	sort_arr = calloc(range, sizeof(int));
	if (NULL == sort_arr)
	{
		return;
	}
	sorted = malloc(sizeof(int) * size);
	if (NULL == sorted)
	{
		return;
	}
	
	for (i = 0; i < (int)size; ++i)
	{	
		sort_arr[arr[i] + zero] += 1;
	}
	
	for (i = 1; i < (int)range; ++i)
	{	
		sort_arr[i] += sort_arr[i - 1];
	}
	
	for (i = (int)(size - 1); i >= 0; --i)
	{	
		sorted[sort_arr[arr[i] + zero] - 1] = arr[i];
		sort_arr[arr[i] + zero] -= 1;
	}
	for (i = 0; i < (int)size; ++i)
	{
		arr[i] = sorted[i];
	}
	free(sort_arr);
	free(sorted);
}

static void RadixCountSort(int *arr, size_t size, int max, size_t exponent)
{
	int *sort_arr = NULL, *sorted = NULL, i = 0;
	assert(NULL != arr);
	
	max += 1;
	
	sort_arr = calloc(max, sizeof(int));
	if (NULL == sort_arr)
	{
		return;
	}
	sorted = malloc(sizeof(int) * size);
	if (NULL == sorted)
	{
		return;
	}
	
	for (i = 0; i < (int)size; ++i)
	{	
		sort_arr[(size_t)arr[i] % exponent] += 1;
	}
	
	for (i = 1; i < max; ++i)
	{	
		sort_arr[i] += sort_arr[i - 1];
	}
	
	for (i = (int)(size - 1); i >= 0; --i)
	{	
		sorted[sort_arr[(size_t)arr[i] % exponent] - 1] = arr[i];
		sort_arr[(size_t)arr[i] % exponent] -= 1;
	}
	for (i = 0; i < (int)size; ++i)
	{
		arr[i] = sorted[i];
	}
	free(sort_arr);
	free(sorted);
}

static size_t GetDigitCount(int max)
{
	size_t counter = 0;
	while (max > 0)
	{
		max /= 10;
		counter += 1;
	}
	return (counter);
}

void RadixSort(int *arr, size_t size)
{
	int max = 0, i = 0;
	size_t digits = 0, exponent = 1;
	
	assert(NULL != arr);
	
	if ((size <= 1) || (NULL == arr))
	{
		return;
	}
	
	max = GetMax(arr, size);
	digits = GetDigitCount(max);
	
	for(i = 0; i < (int)digits; ++i)
	{
		exponent *= 10;
		RadixCountSort(arr, size, max, exponent);
	}
}

