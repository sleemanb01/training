/***************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : SORT ALGORITHIM
* REVIEWER NAME : 
*****************************************************/

#include <assert.h> /* for NULL   */
#include <stddef.h> /* for size_t */
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


#define ARRAY_SIZE 5000


int getMax(int array[], size_t n) 
{
  size_t i = 0;
  size_t max = array[0];
  for (i = 1; i < n; i++)
  {
    if (array[i] > (int)max)
    {
      max = array[i];
    }
  }

  return max;
}

int getMin(int array[], size_t n) 
{
  size_t i = 0;
  size_t min = array[0];
  for (i = 1; i < n; i++)
  {
    if (array[i] < (int)min)
    {
      min = array[i];
    }
  }

  return min;
}

void countingSort(int array[], int size, int place) 
{
  int i;
  int *count = NULL;
  int output[ARRAY_SIZE + 1];
  int max = (array[0] / place) % 10;

  for (i = 1; i < size; i++) 
  {
    if (((array[i] / place) % 10) > max)
      max = array[i];
  }

  count = malloc((max + 1) * sizeof(int));
  if(NULL == count)
  {
    return;
  }

  for (i = 0; i < max; ++i)
    count[i] = 0;

  for (i = 0; i < size; i++)
    count[(array[i] / place) % 10]++;
    
  for (i = 1; i < 10; i++)
    count[i] += count[i - 1];

  for (i = size - 1; i >= 0; i--) {
    output[count[(array[i] / place) % 10] - 1] = array[i];
    count[(array[i] / place) % 10]--;
  }

  for (i = 0; i < size; i++)
    array[i] = output[i];

  free(count);
}

/************************************************
*  Description:     sort array by linear sort
*  Errors:          
*  Parameters:      array of integers, size of array
*  Return value:    NONE
*  Complexity:      O(n^2)
************************************************/
void CountingSort(int *arr, size_t size)
{
  int *count = NULL;
  int *temp = NULL;
  size_t i = 0;
  int output = 0;
  int min = 0;
  size_t count_size = 0;
  
  assert(NULL != arr);
  
  min = getMin(arr, size);
  
  min *= -1;
    
  count_size = getMax(arr, size)+1 + min;

  count = calloc(sizeof(size_t), count_size);
  
  for(i = 0; i < size ; ++i)
  {
    ++count[arr[i] + min];
  }
  
  for(i = 1; i < count_size ; ++i)
  {
    count[i] += count[i-1];

  }
  
  temp = malloc(size * sizeof(int));
  
  for(i = size-1; i < size ; --i)
  {
    output = arr[i];
    --count[output + min];
    temp[count[output  + min]] = output;
  }
  
  memcpy(arr, temp, sizeof(int) * size);
    
  free(count);
  free(temp);

}

/************************************************
*  Description:     sort array by linear sort
*  Errors:          
*  Parameters:      array of integers, size of array
*  Return value:    NONE
*  Complexity:      O(n^2)
************************************************/

void RadixSort(int *arr, size_t size)
{
  int max, place;

  max = getMax(arr, size);

  for (place = 1; max / place > 0; place *= 10)
    countingSort(arr, size, place);

}
