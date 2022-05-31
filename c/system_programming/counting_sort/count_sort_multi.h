#ifndef __COUNTING_SORT__
#define __COUNTING_SORT__

#include <stddef.h> /* for size_t */
#include <sys/types.h> /* for ssize_t*/

/********* VERSION 3 *********/

/* returns index for aux array */
typedef ssize_t(*get_index_ty)(const void *data); 

/* returns 0 for SUCCESS, 1 for FAIL */
int CountingSort(void *base, size_t nmemb, size_t size, get_index_ty get_index_func); 

#endif
