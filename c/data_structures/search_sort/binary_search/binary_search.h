#ifndef __BINARY_SEARCH_H__
#define __BINARY_SEARCH_H__

#include <stddef.h> /* size_t */

/* returns the index of "to_find" element in "arr" if founded,size otherwise.
   if arr is NULL - undefined behavior */
size_t IterativeBinarySearch(int arr[], size_t arr_size, int to_find);

/* returns the index of "to_find" element in "arr" if founded, size otherwise.
   if arr is NULL - undefined behavior */
size_t RecursiveBinarySearch(int arr[], size_t arr_size, int to_find);

#endif /* __BINARY_SEARCH_H__ */