/***************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : SORT ALGORITHIM
* REVIEWER NAME : 
*****************************************************/

#include <assert.h> /* for NULL   */
#include <stddef.h> /* for size_t */
#include <stdio.h>

/************************************************
*             BUBBLE SORT     
*  Parameters:      array of integers, size of array
*  Complexity:      O(n^2)
************************************************/
void BubbleSort(int *array, size_t size)
{
	unsigned int another_round = 0;
	size_t i;
	int tmp = 0;

	assert (NULL != array);

	do
	{
		another_round = 0;
		for(i = 1 ; i < size ; ++i)
		{
			if(array[i-1] > array[i])
			{
				tmp = array[i-1];
				array[i-1] = array[i];
				array[i] = tmp;
				another_round = 1;
			}
		}
	}while(another_round);
}

/************************************************
*             SELECTION SORT     
*  Parameters:      array of integers, size of array
*  Complexity:      O(n^2)
************************************************/
void SelectionSort(int *array, size_t size)
{
	size_t i,j;
	int min_index = 0;
	int tmp = 0;

	assert(NULL != array);
	assert(0 < size);

	for(i = 0; i < size -1; ++i)
	{
		min_index = i;
		for(j = i+1; j < size; ++j)
		{
			if(array[min_index] > array[j])
			{
				min_index = j;
			}
		}

		tmp = array[min_index];
		array[min_index] = array[i];
		array[i] = tmp;
	}
}

/************************************************
*             INSERTION SORT     
*  Parameters:      array of integers, size of array
*  Complexity:      O(n^2)
************************************************/
void InsertionSort(int *array, size_t size)
{
	int i,j;
	int tmp = 0;

	assert(NULL != array);
	assert(0 < size);

	for(i = 1; i < (int)size; ++i)
	{
		tmp = array[i];
		j = i -1;
		 while (j >= 0 && array[j] > tmp) 
		 {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = tmp;
	}
}

