#ifndef __SORTS_H__
#define __SORTS_H__

#include <stddef.h>		/* size_t */

typedef int (* sorts_comp_ty)(const void *data1, const void *data2);

int MergeSort(int *arr_to_sort, size_t num_elements);

int QuickSort(void *base, size_t nmemb, size_t size, sorts_comp_ty comp_func);

#endif /* __SORTS_H__ */
