#include <stddef.h>	         /* size_t */ 

#include "tests.h"
#include "binary_search.h"

#define ARR_SIZE 10
#define TO_FIND 7

static void iterativeSearch(int arr[], int to_find, int expected);
static void recursiveSearch(int arr[], int to_find, int expected);

int main()
{
	int x, i;
	int arr[ARR_SIZE];
	int arr1[ARR_SIZE];
	int arr2[ARR_SIZE];
	int arr3[ARR_SIZE];
	int arr4[ARR_SIZE];

	i = 0;

	for(i = 0; i < ARR_SIZE ; ++i)
	{
		arr[i] = i;
		arr1[i] = i + 1;
		arr2[i] = i + 2;
		arr3[i] = i + 3;
		arr4[i] = ARR_SIZE - i;
	}

	x = TO_FIND;

	iterativeSearch(arr , x, x);
	iterativeSearch(arr1 , x, x-1);
	iterativeSearch(arr2 , x, x-2);
	iterativeSearch(arr3 , x, x-3);
	iterativeSearch(arr4 , x, x-4);

	recursiveSearch(arr , x, x);
	recursiveSearch(arr1 , x, x-1);
	recursiveSearch(arr2 , x, x-2);
	recursiveSearch(arr3 , x, x-3);

	PASS;

	return 0;
}	

static void iterativeSearch(int arr[], int to_find, int expected)
{
	TEST("IterativeBinarySearch()", (int)IterativeBinarySearch(arr, ARR_SIZE,to_find), expected);
}

static void recursiveSearch(int arr[], int to_find, int expected)
{
	TEST("IterativeBinarySearch()", (int)RecursiveBinarySearch(arr, ARR_SIZE,to_find), expected);
}