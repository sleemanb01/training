#ifndef __COMPARISON_SORTS__
#define __COMPARISON_SORTS__

#include <stddef.h> /*size_t*/

/************************************************
*  Description:     sort array by bubble sort
*  Errors:          
*  Parameters:      array of integers, size of array
*  Return value:    NONE
*  Complexity:      O(n^2)
************************************************/
void BubbleSort(int *array, size_t size);

/************************************************
*  Description:     sort array by selection sort
*  Errors:          
*  Parameters:      array of integers, size of array
*  Return value:    NONE
*  Complexity:      O(n^2)
************************************************/
void SelectionSort(int *array, size_t size);

/************************************************
*  Description:     sort array by insertion sort
*  Errors:          
*  Parameters:      array of integers, size of array
*  Return value:    NONE
*  Complexity:      O(n^2)
************************************************/
void InsertionSort(int *array, size_t size);

#endif
