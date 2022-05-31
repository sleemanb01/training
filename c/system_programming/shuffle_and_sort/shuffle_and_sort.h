#ifndef __SHUFFLE_AND_SORT_H__
#define __SHUFFLE_AND_SORT_H__

typedef int (* sorts_comp_ty)(const void *data1, const void *data2);

/*shuffle func*/
void Shuffle(char** array,size_t size);

int MTMergeSort(void **arr_to_sort, size_t num_elements, size_t elem_size, sorts_comp_ty compare_func, size_t num_of_threads); /* int for malloc */

int MTQuickSort(char** array,size_t size,size_t num_of_threads);

#endif
