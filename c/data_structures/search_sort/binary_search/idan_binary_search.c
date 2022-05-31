#include <stddef.h> /* size_t */
#include <assert.h>

#include "binary_search.h"

static size_t GetMid(size_t begin, size_t end);
static size_t RSearch(int arr[], size_t begin, size_t end, int to_find);
/* returns the index of "to_find" element in "arr" if founded,size otherwise.
   if arr is NULL - undefined behavior */
size_t IterativeBinarySearch(int arr[], size_t arr_size, int to_find)
{
    size_t mid = 0, begin = 0, end = 0;
    /*assert arr*/
    assert(arr);
    /*check if size <= 1, if so, return arr_size*/
    /*check if to_find < arr[0] || to_find > arr[size - 1], if so, return size*/
    if ((arr_size <= 1) || to_find < (arr[0]) || to_find > (arr[arr_size - 1]))
    {
        return (arr_size);
    }
    
    /*begin = 0, end = size - 1*/
    begin = 0;
    end = arr_size - 1;
    
    /*while arr[begin] < arr[end]*/
    while (begin != end)
    {
       /*get middle point*/
        mid = GetMid(begin, end);
        /*if arr[middle] < to_find*/
        
        if (arr[mid] > to_find)    
        {
            /*end point = middle*/
            end = mid - 1;   
        }
        else
        {
            /*begin point = middle*/
            begin = mid;
        }
    }/*end while*/
    if (to_find == arr[begin])
    {
        /*return begin*/
        return (begin);
    }
        

    return (arr_size);
}

/* returns the index of "to_find" element in "arr" if founded, size otherwise.
   if arr is NULL - undefined behavior */
size_t RecursiveBinarySearch(int arr[], size_t arr_size, int to_find)
{
    size_t index = 0;
    /*assert arr*/
    assert(arr);
    /*check if size <= 1, if so, return arr_size*/
    /*check if to_find < arr[0] || to_find > arr[size - 1], if so, return size*/
    if ((arr_size <= 1) || to_find < (arr[0]) || to_find > (arr[arr_size - 1]))
    {
        return (arr_size);
    }
    /*call recursive b search(arr[], begin, end, to_find)*/
    index = RSearch(arr, 0, (arr_size - 1), to_find);
    if (arr[index] == to_find)
    {
        return (index);
    }
    return (arr_size);
}


static size_t RSearch(int arr[], size_t begin, size_t end, int to_find)
{
    size_t mid = 0, result = 0;
    /*base: if begin >= end*/
    if (begin >= end)
    {
        return (begin);/*return begin*/
    }
    /*get arr middle point*/
    mid = GetMid(begin, end);
    /*if middle > to_find*/
    if (arr[mid] > to_find)
    {
        /*call recursive b search(arr[], begin, end(middle - 1), to_find)*/
        result = RSearch(arr, begin, mid - 1, to_find);
    }
    else
    {
        /*call recursive b search(arr[], begin(middle), end, to_find)*/
        result = RSearch(arr, mid, end, to_find);
    }    
    return (result);   
}

static size_t GetMid(size_t begin, size_t end)
{
    /*if mid of odd number, add one*/
    if ((end + begin) % 2 != 0)
    {
        return (((end + begin) / 2) + 1);
    }
    return ((end + begin) / 2);
}