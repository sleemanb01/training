#include <stddef.h> /*size_t*/
#include <assert.h>

#include "comparison_sorts.h"

static void Swap(int *arr, int x, int y)
{
	int tmp = 0;
	tmp = arr[x];
	arr[x] = arr[y];
	arr[y] = tmp;
}

void BubbleSort(int *array, size_t size)
{
	size_t i = 0;
	int swapped = 1;
	assert(NULL != array);
	
	if ((size <= 1) || (NULL == array))
	{
		return;
	}
	
	while (swapped == 1)
	{
		swapped = 0;
		for (i = 1; i < size; ++i)
		{
			if (array[i - 1] > array[i])
			{
				Swap(array, i, (i - 1));
				swapped = 1;
			}
		}
		size = size - 1;
	}
}

void SelectionSort(int *array, size_t size)
{
	size_t i = 0, j = 1, k = 0;
	assert(NULL != array);
	
	if ((size <= 1) || (NULL == array))
	{
		return;
	}

	for (i = 0, j = 1; i < size; ++i, k = i, j = i + 1)
	{
		while (j < size)
		{
			if (array[j] < array[k])
			{
				k = j;
			}
			j = j + 1;
		}
		
		if (i != k)
		{
			Swap(array, i, k);
		}
	}
}
void InsertionSort(int *array, size_t size)
{
	size_t i = 0, j = 1;
	int tmp = 0;
	assert(NULL != array);
	
	if ((size <= 1) || (NULL == array))
	{
		return;
	}
	
	for (i = 0, j = 1; j < size; ++i, ++j)
	{
		if (array[i] > array[j])
		{
			tmp = array[j];
			while ((0 != j) && (array[i] > tmp))
			{
				Swap(array, i, j);
				i = i - 1;
				j = j - 1;
			}
			array[j] = tmp;
		}
	}
}
