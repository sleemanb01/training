/***************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : DV
* REVIEWER NAME : 
*****************************************************/

#include<stdio.h>	         /* printכ */
#include<stddef.h>	         /* size_t */ 
#include<stdlib.h>           /* malloc */
#include<string.h>           /* memmove */
#include <assert.h>          /* assert */

#include"dynamic_vector.h"

#define GROWTH_FACTOR 1.5

struct dynamic_vector 
{
	size_t capacity;
	size_t len;
	void **arr;
};

/*
*  Description:  Create a Dynamic Vector data structure
*  Errors: 		 Malloc can fail and return NULL
*  Parameters:   initial_capacity - amount of initial elements of void* type to store 
*  Return value: Pointer to dynamic_vector_t struct
*  Complexity:   O(1)
*/
dynamic_vector_t *DVectorCreate(size_t initial_capacity)
{
	dynamic_vector_t *DV = NULL;
	size_t len = (initial_capacity * sizeof(dynamic_vector_t));

	DV = (void*)malloc(len);
	DV->arr = (void*)malloc(len);
	
	assert(NULL != DV->arr);
	assert(NULL != DV);
	
	DV->len = 0;
	DV->capacity = initial_capacity;

	return DV;

}

/*
*  Description:  Destroy the vector data structure
*  Errors:   	 None
*  Parameters:   Pointer to dynamic_vector_t struct
*  Return value: None
*  Complexity:   O(1)
*/
void DVectorDestroy(dynamic_vector_t *v)
{
	free(v->arr);
	free(v);

	printf("\n*** DYNAMIC VECTOR DESTROYED ***\n");
}

/*
*  Description:  Returns the amount of items stored in the vector
*  Errors: 		 None
*  Parameters: 	 Pointer to dynamic_vector_t struct
*  Return value: amount of items stored in the vector in size_t 
*  Complexity: 	 O(1)
*/
size_t DVectorSize(const dynamic_vector_t *v)
{
	return v->len;
}

/*
*  Description:  Returns the amount of items stored in the vector
*  Errors: 		 None
*  Parameters: 	 Pointer to dynamic_vector_t struct
*  Return value: amount of items stored in the vector in size_t 
*  Complexity: 	 O(1)
*/
size_t DVectorCapacity(const dynamic_vector_t *v)
{
	return (v->capacity - v->len);
}

/*
*  Description:  Remove an item for the end of the vector
*  Errors: 		 Malloc can fail and return NULL
*  Parameters:   Pointer to dynamic_vector_t struct
*  Return value: None
*  Complexity:   O(1) (amortized)
*/
void DVectorPopBack(dynamic_vector_t *v)
{
	if(0 < (v->len))
	{
		--v->len;
	}
	if(v->capacity > (2 * (v->len)))
	{
		DVectorShrinkToFit(v);
	}
}

/* 
*  Description:  Set vector_arr at index to the value of item
*  Errors: 		 None
*  Parameters:   Pointer to dynamic_vector_t struct
				 index - index of vector_arr to set
				 item - void pointer to a value to set  
*  Return value: None
*  Complexity:   O(1)
*/
void DVectorSetItem(dynamic_vector_t *v, size_t index, void *item)
{
	(v->arr)[index] = item;
}

/*
*  Description:  Add item to the end of vector_arr
*  Errors: 		 Malloc can fail and return NULL
*  Parameters: 	 Pointer to vector_t struct
			  	 item - void pointer to a value to add
*  Return value: None
*  Complexity:   O(1) (amoortized)
*/
int DVectorPushBack(dynamic_vector_t *v, void *item)
{
	if((v->len) == (v->capacity))
	{
		DVectorReserve(v, (v->capacity * GROWTH_FACTOR)); 
		v->capacity *= GROWTH_FACTOR;
	}
	v->len++;
	DVectorSetItem(v, v->len, item);

	return 0;

}

/* 
*  Description:  Peek at the item at index
*  Errors: 		 Can return NULL if the index is larger than the size
				 Undifined behavior if there is no item in that index
*  Parameters: 	 Pointer to vector_t struct
				 index - index of vector_arr
*  Return value: void pointer to the item at index
*  Complexity: 	 O(1)
*/
void *DVectorGetElement(dynamic_vector_t *v, size_t index)
{
	if((index < v->len - 1) && (NULL != v))
	{
		return (v->arr)[index];
	}
	else
	{
		return NULL;
	}
}

/* 
*  Description:  Resize the vector
*  Errors: 		 Malloc can fail and return NULL
				 data will definitely lost if vector is shrinked to a smaller size than 				 dynamic_vectorSize
*  Parameters: 	 Pointer to vector_t struct
				 amount - amount of initial elements to store
*  Return value: None
*  Complexity:   O(n)
*/
int DVectorReserve(dynamic_vector_t *v, size_t amount)
{
	v->arr = realloc(v->arr, amount * sizeof(void*));

	if(NULL != v->arr)
	{
		/*v->arr = tmp;*/
		return 0;
	}
	else
	{
		return 1;
	}
}

/* 
*  Description:  Shrink the vector to fit
*  Errors: 		 Malloc can fail and return NULL
				 data will definitely lost if vector is shrinked to a smaller size than 				 dynamic_vectorSize
*  Parameters: 	 Pointer to vector_t struct
				 amount - amount elements to store
*  Return value: None
*  Complexity:   O(n)
*/
int DVectorShrinkToFit(dynamic_vector_t *v)
{
	v->arr = realloc(v->arr, v->len * sizeof(void*));

	if(NULL != v->arr)
	{
		/*v->arr = tmp;*/
		return 0;
	}
	else
	{
		return 1;
	}
}