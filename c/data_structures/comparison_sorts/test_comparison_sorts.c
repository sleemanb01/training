#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tests.h"
#include "comparison_sorts.h"

#define MAX_NUMBER 100
#define ARRAY_SIZE 5000

void arrayInit(int *arr);
void test(int *arr, char func_name[]);

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
	BubbleSort(arr, ARRAY_SIZE);
	test(arr , "bubbleSort()");

	arrayInit(arr);
	SelectionSort(arr, ARRAY_SIZE);
	test(arr, "selectionSort()");

	arrayInit(arr);
	InsertionSort(arr, ARRAY_SIZE);
	test(arr, "insertionSort()");

	free(arr);

	PASS;

	return 0;
}

void arrayInit(int *arr)
{
	size_t i;
	/* Intializes random number generator */
	srand((unsigned) time(NULL));

	for( i = 0 ; i < ARRAY_SIZE ; i++) 
	{
		arr[i] = rand() % MAX_NUMBER;
	}
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