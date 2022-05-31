/************************************************************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : SHUFFLE_AND_SORT
* REVIEWER NAME : IDAN
************************************************************************************************/

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#include "shuffle_and_sort.h"

/****************************** GLOBAL *************************************/

#define UNUSED(x) (void)x

void **g_array = NULL;
pthread_t *tid;

/****************************** TLS STRUCT *************************************/

typedef struct tls
{
    size_t offset;
    size_t end;
    size_t ea_size;
    void **base;
    
    sorts_comp_ty compare_func;

} tls_ty;


/****************************** FUNCS *************************************/

static void *MergeSort(void *tls);
static void MergeR(size_t begin, size_t end, size_t ea_size, sorts_comp_ty compare_func);
static void Merge(size_t begin, size_t mid, size_t end, size_t ea_size, sorts_comp_ty compare_func);
static void MTMerge(void **l_arr, void **r_arr, size_t l_size, size_t r_size, sorts_comp_ty comp_func, size_t begin);

static void *QSortImp(void *tls);
static int StrCmp(const void *a, const void *b);
static void Swap(void **a, void *b, size_t size);
static void QuickSort(void **base, size_t low, size_t high, size_t size, sorts_comp_ty comp_func);
static size_t partition (void *base, size_t low, size_t high, size_t size, sorts_comp_ty comp_func);

static int Random(const void *a, const void *b);
static void InitArr(tls_ty *sort_arr,size_t size, size_t ea_size, sorts_comp_ty compare_func, size_t num_of_threads);

/****************************** MAIN *************************************/

/******************************/
void Shuffle(char **array, size_t size)
{
    qsort(array, size, sizeof(void *), Random);
}

/******************************/
int MTMergeSort(void **arr_to_sort, size_t num_elements, size_t ea_size, sorts_comp_ty compare_func, size_t num_of_threads)
{
    tls_ty *tls = NULL;
    size_t i = 0;

    assert(NULL != arr_to_sort);
    assert(0 < num_elements);

    tid = malloc(sizeof(pthread_t) * num_of_threads);
    if (NULL == tid)
    {
        printf("*** MALLOC ERROR ***\n");
        return 1;
    }

    tls = malloc(sizeof(tls_ty) * num_of_threads);
    if (NULL == tls)
    {
        printf("*** MALLOC ERROR ***\n");
        return 1;
    }

    g_array = malloc(sizeof(void*) * num_elements);
    if (NULL == g_array)
    {
        printf("*** MALLOC ERROR ***\n");
        return 1;
    }

    for (i = 0; i < num_elements; ++i)
    {
        g_array[i] = arr_to_sort[i];
    }

    InitArr(tls, num_elements, ea_size, compare_func, num_of_threads);

    for (i = 0; i < num_of_threads; ++i)
    {
        if (pthread_create(&tid[i], NULL, MergeSort, &tls[i]))
        {
            printf("*** THREAD CREATION ERROR %lu ***", i);
            return 1;
        }
    }

    for (i = 0; i < num_of_threads; ++i)
    {
        pthread_join(tid[i], NULL);
    }

    for (i = 0; i < num_elements; ++i)
    {
        arr_to_sort[i] = g_array[i];
    }

    free(tid);
    free(tls);
    free(g_array);

    return 0;
}

/******************************/

int MTQuickSort(char **array, size_t size, size_t num_of_threads)
{
    tls_ty *tls = NULL;
    size_t i = 0;

    assert(NULL != array);
    assert(0 < num_of_threads);

    tid = malloc(sizeof(pthread_t) * num_of_threads);
    if (NULL == tid)
    {
        return 1;
    }

    tls = malloc(sizeof(tls_ty) * num_of_threads);
    if (NULL == tls)
    {
        return 1;
    }

    InitArr(tls, size, sizeof(void*), StrCmp, num_of_threads);

    for (i = 0; i < num_of_threads; ++i)
    {
        if (pthread_create(&tid[i], NULL, QSortImp, &tls[i]))
        {
            printf("*** THREAD CREATION ERROR %lu ***", i);
            return 1;
        }
    }
    for (i = 0; i < num_of_threads; ++i)
    {
        pthread_join(tid[i], NULL);
    }

    free(tls);
    
    return 0;
}

/****************************** FUNCS *************************************/
/******************************/
static void *MergeSort(void *tls)
{
    tls_ty *thread = NULL;

    thread = (tls_ty *)tls;

    MergeR(thread->offset, thread->end, thread->ea_size, thread->compare_func);

    return NULL;
}

/******************************/
static void MergeR(size_t begin, size_t end, size_t ea_size, sorts_comp_ty compare_func)
{
    size_t mid;

    if (end > begin)
    {
        mid = begin + ((end - begin) / 2);

        MergeR(begin, mid, ea_size, compare_func);

        MergeR(mid + 1, end, ea_size, compare_func);

        Merge(begin, mid, end, ea_size, compare_func);
    }
}

/******************************/

static void Merge(size_t begin, size_t mid, size_t end, size_t ea_size, sorts_comp_ty compare_func)
{
    size_t i = 0;

    size_t l_size = mid - begin;
    size_t r_size = end - mid;
    void **l_arr = NULL;
    void **r_arr = NULL;

    l_arr = malloc(ea_size * l_size);
    if (NULL == l_arr)
    {
         printf("*** MALLOC ERROR ***\n");
        return;
    }

    r_arr = malloc(ea_size * r_size);
    if (NULL == r_arr)
    {
         printf("*** MALLOC ERROR ***\n");
        free(l_arr);
        return;
    }

    for (i = 0; i < l_size; ++i)
    {
        l_arr[i] = g_array[begin + i];
    }

    for (i = 0; i < r_size; ++i)
    {
        r_arr[i] = g_array[mid + i];
    }

    MTMerge(l_arr, r_arr, l_size, r_size, compare_func, begin);

    free(l_arr);
    free(r_arr);
}

/******************************/
static void MTMerge(void **l_arr, void **r_arr, size_t l_size, size_t r_size, sorts_comp_ty compare_func, size_t begin)
{
    size_t i = 0;
    size_t j = 0;
    size_t k = begin;

    while ((i < l_size) && (j < r_size) && l_arr[i] && r_arr[j])
    {
        if (0 > compare_func(l_arr[i], r_arr[j]))
        {
            g_array[k] = l_arr[i];
            i += 1;
        }
        else
        {
            g_array[k] = r_arr[j];
            j += 1;
        }
        k += 1;
    }

    while (i < l_size)
    {
        g_array[k] = l_arr[i];
        k += 1;
        i += 1;
    }

    while (j < r_size)
    {
        g_array[k] = r_arr[j];
        k += 1;
        j += 1;
    }
}

/******************************/
static void *QSortImp(void *tls)
{
    tls_ty *thread_storage = NULL;

    assert(NULL != tls);

    thread_storage = (tls_ty *)tls;

    QuickSort(thread_storage->base, thread_storage->offset, thread_storage->end, thread_storage->ea_size, thread_storage->compare_func);

    return NULL;
}

/******************************/
static void QuickSort(void **base, size_t low, size_t high, size_t size, sorts_comp_ty comp_func)
{
    size_t pi;

    if(low < high)
    {
        pi = partition(base,low,high,size,comp_func);

        if(0 != pi)
        {
            QuickSort(base, low, (pi - 1), size, comp_func);
            QuickSort(base, (pi + 1), high, size, comp_func);
        }
    }
}

/******************************/
static void Swap(void **a, void *b, size_t size)
{
    char *tmp = NULL;

    tmp = malloc(size);
    if(NULL == tmp)
    {
        printf("*** MALLOC ERROR ***\n");
        return;
    }

    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);

    free(tmp);
}

/******************************/
static size_t partition (void *base, size_t low, size_t high, size_t size, sorts_comp_ty comp_func)
{
    size_t pivot, i ,j;
    void *pivot_index = NULL;
    void *begin = NULL;
    
    if(low < high)
    {
        return 0;
    }

    pivot = ((low + high)/2);

    i = 0;
    j = low;

    begin = ((char*)base + (low * size));
    pivot_index = ((char*)base + (pivot * size));

    Swap(begin, pivot_index, size);

    for(i = low + 1; i <= high; ++i)
    {
        if(0 < comp_func( (begin), ((char*)base + (i * size)) ))
        {
            ++j;
            Swap( (void*)((char*)base + (i * size)) , ((char*)base + (j * size)) , size);
        }
    }

     Swap(begin,((char*)base + (j * size)), size);

    return j;

}

/******************************/
static void InitArr(tls_ty *sort_arr, size_t size, size_t ea_size, sorts_comp_ty compare_func, size_t num_of_threads)
{
    size_t i = 0;
    size_t jump = 0;

    jump = size / num_of_threads;

    for (i = 0; i < num_of_threads; ++i)
    {
        sort_arr[i].base = g_array;
        sort_arr[i].compare_func = compare_func;
        sort_arr[i].offset = i * jump;
        sort_arr[i].end = i * jump + jump - 1;
        sort_arr[i].ea_size = ea_size;
    }

    sort_arr[i - 1].end = size - 1;
}

/******************************/
static int Random(const void *a, const void *b)
{
    UNUSED(a);
    UNUSED(b);
    return ((rand() % 3) - 1);
}

/******************************/
static int StrCmp(const void *a, const void *b)
{
    return (strcmp((char *)a, (char *)b));
}
