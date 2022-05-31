/***************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : FSA
* REVIEWER NAME : AMIHAI
*****************************************************/

#include <assert.h> /* for assert */

#include"fsa.h"

struct FSA_struct
{
  size_t *next;
  size_t size;
  size_t counter;
};

size_t align_block (size_t block_Size)
{
   size_t left = 0;

   left = block_Size % sizeof(void*);
   return (left == 0) ? block_Size : left + block_Size;
}

 
/********************************************************************************
*  Description:    compute the size of a MEM POOL considirng the struct 
*  Errors:          
*  Parameters:     block size, block number
*  Return value:   size of allocated memory(mem_size) + size of struct
  Complexity:      O(1)
********************************************************************************/
size_t FSASuggestSize(size_t block_size, size_t block_num)
{
  return (sizeof(FSA_t) + (align_block(block_size) * block_num));
}

/********************************************************************************
*  Description:    allocate initial memory for our Alloc() and Free() use
*  Errors:          
*  Parameters:     block pointer, pool size, block size
*  Return value:   FSA pointer
  Complexity:      O(1)
********************************************************************************/
FSA_t *FSAInit(void *mem, size_t pool_size, size_t block_size)
{
  FSA_t *new = NULL;
  size_t *iter = NULL, runner = 0;

  assert(NULL != mem);

  block_size = align_block(block_size);

  new = mem;
  new->size = (pool_size - sizeof(FSA_t))/(block_size);
  new->counter = 0;
  new->next = (size_t*)((char*)mem + sizeof(FSA_t));

  iter = new->next; 

  for(runner = 1;runner <= new->size; ++runner)
  {
    *iter = (size_t)(iter + block_size);
    iter = (size_t *)*iter;
  }
  
  *iter = 0;

  return new;
}

/********************************************************************************
*  Description:    allocate aligned(8) memory from initial allocated memory 
*  Errors:          
*  Parameters:     FSA pointer
*  Return value:   FSA pointer
  Complexity:      O(1)
********************************************************************************/
void *FSAAlloc(FSA_t *fsa)
{

  void* allocated = NULL;

  assert(NULL != fsa);

  allocated = fsa->next + sizeof(void*);

  fsa->next = (size_t*)*fsa->next;

  ++fsa->counter;

  return allocated;
}

/********************************************************************************
*  Description:    free allocated by Alloc() memory
*  Errors:          
*  Parameters:     FSA pointer, block (node) pointer
*  Return value:   
  Complexity:      O(1)
********************************************************************************/
void FSAFree(FSA_t *fsa, void *node)
{
  size_t *tmp = NULL;

  assert(NULL != fsa);
  assert(NULL != node);

  *(size_t *)node = (size_t)fsa->next;
  fsa->next = node;

  --fsa->counter;
}

/********************************************************************************
*  Description:    count remained free blocks
*  Errors:          
*  Parameters:     FSA pointer
*  Return value:   number of free blocks 
  Complexity:      O(1)
********************************************************************************/
size_t FSACountFree(FSA_t *fsa)
{
  return (fsa->size - fsa->counter);
}