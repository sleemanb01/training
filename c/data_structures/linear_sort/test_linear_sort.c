#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tests.h"
#include "linear_sort.h"

#define ARRAY_SIZE 10
#define MAX_NUMBER 10

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
	CountingSort(arr, ARRAY_SIZE);
	test(arr , "CountingSort()");

	arrayInit(arr);
	RadixSort(arr, ARRAY_SIZE);
	test(arr , "RadixCountSort()");

	free(arr);

	PASS;

	return 0;
}

void arrayInit(int *arr)
{
	size_t i;
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