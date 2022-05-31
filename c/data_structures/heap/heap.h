#ifndef __HEAP_H__
#define __HEAP_H__

/********* VERSION 1.3 *********/

#include <stddef.h>  /* size_t */

typedef struct heap heap_ty;

/*compare heap elements with data 
 return -1 or 1 for data < heap_elem, otherwise, respectively */
typedef int (*heap_comp_ty)(const void *data, const void *heap_elem, void *param);
typedef int (*is_match_ty)(const void *heap_elem, void* param);
/*
struct heap
{
	dvector_t *d_heap;
	heap_comp_ty compare_func;
	void *param;
};
*/

/************************************************************************************************
*  Name:            HeapCreate
*  Description:		Create an empty heap
*  Parameters:      heap_comp_ty, compare function
*  Return    :      Pointer to newly created heap structure
*  Complexity:      O(1)
************************************************************************************************/
heap_ty* HeapCreate(heap_comp_ty compare, void *param); 

/************************************************************************************************
*  Name:            HeapDestroy    
*  Description:		Destroys all heap node and structure 
*  Parameters:      heap_ty*, Pointer to heap
*  Return    :      void
*  Complexity:      O(1)
************************************************************************************************/
void HeapDestroy(heap_ty *this);

/************************************************************************************************
*  Name:            HeapPush   
*  Description:		Inserts a new node to heap 
*  Parameters:      heap_ty*, Pointer to heap
*					void *data, pointer to data
*  Return    :      int, 0 for success 1 otherwise
*  Complexity:      O(log n)
************************************************************************************************/
int HeapPush(heap_ty *this, void *data);

/************************************************************************************************
*  Name:            HeapPop   
*  Description:		Pop the root node from heap
*  Parameters:      heap_ty*, Pointer to heap
*  Return    :      void
*  Complexity:      O(log n)
************************************************************************************************/
void HeapPop(heap_ty *this);

/************************************************************************************************
*  Name:            HeapPeek   
*  Description:		Peek a data from root node
*  Parameters:      heap_ty*, Pointer to heap
*  Return    :      void*
*  Complexity:      O(1)
************************************************************************************************/
void *HeapPeek(const heap_ty *this);

/************************************************************************************************
*  Name:            HeapSize   
*  Description:		Peek a data from root node
*  Parameters:      heap_ty*, Pointer to heap
*  Return    :      return the size of the heap
*  Complexity:      O(1)
************************************************************************************************/
size_t HeapSize(const heap_ty *this);

/************************************************************************************************
*  Name:            HeapIsEmpty   
*  Description:		check if heap is empty
*  Parameters:      heap_ty*, Pointer to heap
*  Return    :      1/0 if empty or not
*  Complexity:      O(1)
************************************************************************************************/
int HeapIsEmpty(const heap_ty *this); 

/************************************************************************************************
*  Name:            HeapRemove   
*  Description:	  remove node/iter from heap
*  Parameters:      heap_ty*, Pointer to heap
*						  is_match_ty, func to compare the data
*						  void*,paramater from the user				
*  Return    :      void* pointer
*  Complexity:      O(n)
************************************************************************************************/
void *HeapRemove(heap_ty *this, is_match_ty is_match, void *param);

#endif

