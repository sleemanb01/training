#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tests.h"
#include "sorts.h"

#define MAX_NUMBER 100
#define ARRAY_SIZE 10

void arrayInit(int *arr);
void test(int *arr, char func_name[]);

int compare(const void *data1, const void *data2)
{
	int input, to_compare, res = 0;

	input = *(int*)data1;
	to_compare = *(int*)data2;

	if(input > to_compare)
	{
		res = 1;
	}
	else if(input < to_compare)
	{
		res = -1;
	}

	return res;
}

int main()
{
	int *arr = NULL;

	arr = (int*)malloc(ARRAY_SIZE * sizeof(int));

	if(NULL == arr)
	{
		printf("MALLOC ERROE LINE %d\n", __LINE__);
		return 1;
	}

	arrayInit(arr);
	MergeSort(arr, ARRAY_SIZE);
	test(arr , "MergeSort()");

	arrayInit(arr);
	QuickSort((void*)arr, ARRAY_SIZE, sizeof(int), &compare);
	test(arr, "QuickSort()");

	free(arr);

	PASS;

	return 0;
}

void arrayInit(int *arr)
{
	size_t i;
	/* Intializes random number generator */
	/*srand((unsigned) time(NULL));*/

	for( i = 0 ; i < ARRAY_SIZE ; i++) 
	{
		/*arr[i] = rand() % MAX_NUMBER;*/
		arr[i] = i;
		
	}

	arr[5] = 4;
	arr[4] = 5;
}

void test(int *arr, char func_name[])
{
	size_t i;
	unsigned int unsorted = 0;

	for(i = 1 ; i < ARRAY_SIZE ; i++) 
	{
		if(arr[i-1] > arr[i])
		{
			++unsorted;
		}
	}

	TEST(func_name,unsorted ,0);

}