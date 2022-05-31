/************************************************************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : HEAP
* REVIEWER NAME : ANTON
************************************************************************************************/

#include <stddef.h>	         /* size_t */ 
#include <stdlib.h>          /* malloc */
#include <assert.h>          /* assert */
#include <string.h>          /* memcpy */
#include <stdio.h>

#include "heap.h"
#include "dynamic_vector.h"

/***********************************************************************************************
*                                      STRCUCTS/CONSTS                                          *
************************************************************************************************/

struct dynamic_vector
{
	size_t capacity;
	size_t len;
	void **arr;
};

struct heap
{
    dynamic_vector_t *d_heap;
    heap_comp_ty compare_func;
    void *param;
};

#define INIT_SIZE 10

/***********************************************************************************************
*                                            EXTRA FUNCS                                       *
************************************************************************************************/

static void swap(void* a, void* b);

static void HeapifyUp(heap_ty *this, size_t index);
static void HeapifyDown(heap_ty *this, size_t index);

static size_t GetParent(size_t index);
static size_t GetLeft(size_t index);
static size_t GetRight(size_t index);

/************************************************************************************************
*  Name:            HeapCreate
*  Description:     Create an empty heap
*  Parameters:      heap_comp_ty, compare function
*  Return    :      Pointer to newly created heap structure
*  Complexity:      O(1)
************************************************************************************************/
heap_ty* HeapCreate(heap_comp_ty compare, void *param)
{
    heap_ty *new = NULL;
    dynamic_vector_t *vec = NULL;

    assert(NULL != compare);

    do
    {

        new = (heap_ty*)malloc(sizeof(struct heap));
        if(NULL == new)
        {
            break;
        }

        vec = DVectorCreate(INIT_SIZE);
        if(NULL == vec)
        {
            break;
        }

        new->compare_func = compare;
        new->param = param;
        new->d_heap = vec;

        return new;

    }while(0);
    
    free(new);
    free(vec);

    return NULL;
}

/************************************************************************************************
*  Name:            HeapDestroy    
*  Description:     Destroys all heap node and structure 
*  Parameters:      heap_ty*, Pointer to heap
*  Return    :      void
*  Complexity:      O(1)
************************************************************************************************/
void HeapDestroy(heap_ty *this)
{
    assert(NULL != this);

    DVectorDestroy(this->d_heap);
    free(this);
}

/************************************************************************************************
*  Name:            HeapPush   
*  Description:     Inserts a new node to heap 
*  Parameters:      heap_ty*, Pointer to heap
*                   void *data, pointer to data
*  Return    :      int, 0 for success 1 otherwise
*  Complexity:      O(log n)
************************************************************************************************/
int HeapPush(heap_ty *this, void *data)
{
    dynamic_vector_t *vec = NULL;
    size_t index;

    assert(NULL != this && NULL != data);

    vec = this->d_heap;
    index = vec->len - 1;

    if(DVectorPushBack(vec,data))
    {
        HeapifyUp(this, index);
        return 0;
    }

    return 1;
}

/************************************************************************************************
*  Name:            HeapPop   
*  Description:     Pop the root node from heap
*  Parameters:      heap_ty*, Pointer to heap
*  Return    :      void
*  Complexity:      O(log n)
************************************************************************************************/
void HeapPop(heap_ty *this)
{
     dynamic_vector_t *vec = NULL;
     void *last, *root;

    assert(NULL != this);

    vec = this->d_heap;
    last = DVectorGetElement(vec,vec->len - 1);
    root = DVectorGetElement(vec,0);

    swap(last, root);

    DVectorPopBack(vec);
    HeapifyDown(this, 0);
}

/************************************************************************************************
*  Name:            HeapPeek   
*  Description:     Peek a data from root node
*  Parameters:      heap_ty*, Pointer to heap
*  Return    :      void*
*  Complexity:      O(1)
************************************************************************************************/
void *HeapPeek(const heap_ty *this)
{
    dynamic_vector_t *vec = NULL;
    size_t peek_index;

    assert(NULL != this);

    vec = this->d_heap;
    peek_index = vec->len - 1;

    return(DVectorGetElement(vec,peek_index - 1));
}

/************************************************************************************************
*  Name:            HeapSize   
*  Description:     Peek a data from root node
*  Parameters:      heap_ty*, Pointer to heap
*  Return    :      return the size of the heap
*  Complexity:      O(1)
************************************************************************************************/
size_t HeapSize(const heap_ty *this)
{
    dynamic_vector_t *vec = NULL;

    assert(NULL != this);

    vec = this->d_heap;
    
    return(vec->len);
}

/************************************************************************************************
*  Name:            HeapIsEmpty   
*  Description:     check if heap is empty
*  Parameters:      heap_ty*, Pointer to heap
*  Return    :      1/0 if empty or not
*  Complexity:      O(1)
************************************************************************************************/
int HeapIsEmpty(const heap_ty *this)
{
     assert(NULL != this);

     return (0 == HeapSize(this));
}

/************************************************************************************************
*  Name:            HeapRemove   
*  Description:     remove node/iter from heap
*  Parameters:      heap iter
*  Return    :      void
*  Complexity:      O(n)
************************************************************************************************/
void *HeapRemove(heap_ty *this, is_match_ty is_match, void* param)
{
    dynamic_vector_t *vec = NULL;
    size_t target_index, peek_index;
    void *target = NULL;
    void *peek = NULL;

    assert(NULL != this);

    vec = this->d_heap;
    peek_index = vec->len - 1;

    for(target_index = 0; target_index < peek_index ; ++target_index)
    {
        if(is_match(param,DVectorGetElement(vec,target_index)))
        {
            break;
        }
    }

    target = DVectorGetElement(vec,target_index);
    peek = DVectorGetElement(vec,peek_index);
    swap(target, peek);
    HeapPop(this);

    HeapifyDown(this, target_index);

    return peek;

}

/***********************************************************************************************
*                                            EXTRA FUNCS                                       *
************************************************************************************************/

/*********************************** SWAP ************************************/
static void swap(void* a, void* b)
{
    char *tmp = NULL;
    size_t size = sizeof(void*);

    tmp = malloc(size);
    if(NULL == tmp)
    {
        return;
    }

    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

/****************************** MaxHeapify ************************************/
static void HeapifyUp(heap_ty *this, size_t index)
{
    dynamic_vector_t *v = this->d_heap;
    void *child, *parent;
    size_t parent_index = GetParent(index);

    child = DVectorGetElement(v,index);
    parent = DVectorGetElement(v,parent_index);

    if (index && this->compare_func(child, parent, this->param))
    {
        swap(child, parent);

        HeapifyUp(this,parent_index);
    }
}

/****************************** MinHeapify ************************************/
static void HeapifyDown(heap_ty *this, size_t index)
{
        dynamic_vector_t *v = this->d_heap;
        size_t left = GetLeft(index);
        size_t right = GetRight(index);
        size_t largest = index;
 
        if (this->compare_func(DVectorGetElement(v, left),DVectorGetElement(v, largest), this->param)) 
        {
            largest = left;
        }
 
        if (this->compare_func(DVectorGetElement(v,right),DVectorGetElement(v,largest), this->param)) 
        {
            largest = right;
        }
 
        if (largest != index)
        {
            swap(DVectorGetElement(v,index),DVectorGetElement(v,largest));
            HeapifyDown(this,largest);
        }
}

/****************************** MinHeapify ************************************/
static size_t GetParent(size_t index)
{
    return (index - 1) / 2;
}

/****************************** MinHeapify ************************************/
static size_t GetLeft(size_t index)
{
    return (2*index + 1);
}

/****************************** MinHeapify ************************************/
static size_t GetRight(size_t index)
{
    return (2*index + 2);
}