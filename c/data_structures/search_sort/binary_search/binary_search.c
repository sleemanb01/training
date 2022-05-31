/************************************************************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : BINARY SEARCH
* REVIEWER NAME : 
************************************************************************************************/

#include <stddef.h>	         /* size_t */ 
#include <stdlib.h>          /* malloc */
#include <assert.h>          /* assert */

#include "binary_search.h"

/***********************************************************************************************
*                                            FUNCS                                             *
************************************************************************************************/

static size_t BSRecursive(int arr[], int min, int max, int to_find);

/************************************************************************************************
*                   BINARY SEARCH     
*  Parameters:      array, it's size, value to find
*  Return    :      the index of "to_find" element in "arr"
*  Complexity:      O(n)
************************************************************************************************/

size_t IterativeBinarySearch(int arr[], size_t arr_size, int to_find)
{
	size_t i = 0;
	int min, max;
	int is_ascending = 0;

	assert(NULL != arr);

	min = 0;
	max = arr_size -1;

	is_ascending = (arr[max] > arr[min]);

	while(min <= max)
	{
		i = (min + max) / 2;

		if(to_find == arr[i])
		{
			return i;
		}
		else if(to_find > arr[i])
		{
			if(is_ascending)
			{
				min = i + 1;
			}
			else
			{
				max = i - 1;
			}
		}
		else
		{
			if(is_ascending)
			{
				max = i - 1;
			}
			else
			{
				min = i + 1;
			}
		}
    }
 
    return -1;
}


/************************************************************************************************
*                   RECURSIVE BINARY SEARCH     
*  Parameters:      c array, it's size, value to find
*  Return    :      the index of "to_find" element in "arr"
*  Complexity:      O(n^2)
************************************************************************************************/

size_t RecursiveBinarySearch(int arr[], size_t arr_size, int to_find)
{

	int min,max;

	assert (NULL != arr);

	min = 0;
	max = arr_size - 1;

	return BSRecursive(arr,min,max,to_find);
}

/****************************** RECURSIVE SEARCH ********	****************************/

static size_t BSRecursive(int arr[], int min, int max, int to_find)
{
	int i;

	if(max >= min)
	{
		i = (max + min) / 2;

		if(to_find == arr[i])
		{
			return i;
		}

		if(to_find > arr[i])

		{
			return BSRecursive(arr, i + 1, max, to_find);
		}

		return BSRecursive(arr, min, i - 1, to_find);
	}

	return -1;
}