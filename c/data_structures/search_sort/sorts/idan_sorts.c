#include <stddef.h>		/* size_t */
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "sorts.h"

static void SplitAndMerge(int *arr_to_sort, size_t begin, size_t end);
static void Merge(int *arr_to_sort, size_t begin, size_t mid, size_t end);
static void QSort(void *base, size_t Lindex,  size_t Rindex, size_t size, sorts_comp_ty func);
static void Swap(void *start, void *end, size_t size);
static size_t Partition(void *base, size_t Lindex, size_t Rindex, size_t size, sorts_comp_ty func);

int MergeSort(int *arr_to_sort, size_t num_elements)
{
    /*assert array*/
    assert(arr_to_sort);
    
    /*call split and merge func (arr, begin, end)*/
    SplitAndMerge(arr_to_sort, 0, num_elements - 1);
    
    return (0);
}

int QuickSort(void *base, size_t nmemb, size_t size, sorts_comp_ty comp_func)
{
    /*assert base and comp_func*/
    assert(base);
    assert(comp_func);
    /*if nmemb <= 1 or size < 1 return*/
    if (nmemb <= 1)
    {
        return 1;
    }
    /*call sort func (arr start point, range, elem_size, comp_func)*/
    QSort(base, 0, nmemb - 1, size, comp_func);
    return (0);
}


static void SplitAndMerge(int *arr_to_sort, size_t begin, size_t end)
{
    /*base: if size < 2 (no sub arr or sub arr of one) return*/
    if (1 <= (end - begin))
    {
        /*get mid point*/
        size_t mid = ((end + begin) / 2);
        
        /*split and merge first half*/
        SplitAndMerge(arr_to_sort, begin, mid);
        
        /*split and merge second half*/
        SplitAndMerge(arr_to_sort, mid + 1, end);
        
        /*merge the sub arrays*/
        Merge(arr_to_sort, begin, mid, end);
    }
    
}

static void Merge(int *arr_to_sort, size_t begin, size_t mid, size_t end)
{
    size_t i = 0, j = 0, k = 0;
    
    /*get tmp arrays sizes*/
    size_t LarrSize = mid - begin + 1;
    size_t RarrSize = end - mid;
    int *Larr = NULL;
    int *Rarr = NULL;
    
    /*allocate arrays and check alllocation*/
    Larr = malloc(sizeof(int) * LarrSize);
    if (!Larr)
    {
        return;
    }
    Rarr = malloc(sizeof(int) * RarrSize);
    if (!Rarr)
    {
        free(Larr);
        return;
    }

    /*copy left side of array to temp array*/
    for (i = 0; i < LarrSize; ++ i)
    {
        Larr[i] = arr_to_sort[begin + i];
    }

    /*copy right side of array to temp array*/
    for (i = 0; i < RarrSize; ++i)
    {
        Rarr[i] = arr_to_sort[mid + i + 1];
    }

    /*set runners to 0 and begin*/
    i = 0;
    j = 0;
    k = begin;
    
    /*copy tmp arrays content */
    while ((i < LarrSize) && (j < RarrSize))
    {
        if (Larr[i] < Rarr[j])
        {
            arr_to_sort[k] = Larr[i];
            i += 1;
        }
        else
        {
            arr_to_sort[k] = Rarr[j];
            j += 1;
        }
        k += 1;
    }

    /*empty left tmp array if needed*/
    while (i < LarrSize)
    {
        arr_to_sort[k] = Larr[i];
        k += 1;
        i += 1;
    }

    /*empty right tmp array if needed*/
    while (i < RarrSize)
    {
        arr_to_sort[k] = Rarr[j];
        k += 1;
        j += 1;
    }

    /*free tmp arrays*/
    free(Larr);
    free(Rarr);
}

static void QSort(void *base, size_t Lindex, size_t Rindex, size_t size, sorts_comp_ty func)
{
    if (Lindex < Rindex)
    {
        size_t pivot = Partition(base, Lindex, Rindex, size, func);
        if (0 != pivot)
        {
            QSort(base, Lindex, (pivot - 1), size, func);
            QSort(base, (pivot + 1), Rindex, size, func);
        }
    }

}

static void Swap(void *start, void *end, size_t size)
{
    char *tmp = NULL;
    tmp = malloc(size);
    if (!tmp)
    {
        return;
    }
    memcpy(tmp, start, size);
    memcpy(start, end, size);
    memcpy(end, tmp, size);
    free(tmp);
}

static size_t Partition(void *base, size_t Lindex, size_t Rindex, size_t size, sorts_comp_ty func)
{
    if (Rindex > Lindex)
    {
        size_t pivot = ((Rindex + Lindex) / 2), i = 0, j = 0;
        void *piv_point = NULL, *start = NULL, *runner = NULL, *runner2 = NULL;
        
        
        start = (((char *)base) + (Lindex * size));
        piv_point = (((char *)base) + (pivot * size));
        j = Lindex;
        Swap(start, piv_point, size);

        for (i = Lindex + 1; i <= Rindex; ++i)
        {
            runner = (((char *)base) + (i * size));
            if (func(start, runner) > 0)
            {
                ++j;
                runner2 = (((char *)base) + (j * size));
                Swap(runner, runner2, size);
            }
        }
        runner2 = (((char *)base) + (j * size));
        Swap(start, runner2, size);
        return (j);
    }
    return 0;
}

