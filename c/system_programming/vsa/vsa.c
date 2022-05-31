/***************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : VSA
* REVIEWER NAME : SHAHAR
*****************************************************/

#include <assert.h> /* for assert */

#include"vsa.h"

struct VSA_struct
{
  size_t *next;
  size_t size;
  size_t counter;
};

/********************************************************************************
*  Description:    allocate initial memory for our Alloc() and Free() use
*  Errors:          
*  Parameters:     memory address, pool size
*  Return value:   VSA pointer
  Complexity:      O(1)
********************************************************************************/
/*VSA_t *VSAInit(void *mem, size_t pool_size);
{
  VSA_t *new = NULL;

  assert(NULL != mem);


  return new;
}*/

/********************************************************************************
*  Description:    allocate aligned to word size memory from initial allocated memory
*  Errors:          
*  Parameters:     VSA pointer , size
*  Return value:   VSA pointer
  Complexity:      O(n)
********************************************************************************/
/*void *VSAAlloc(VSA_t *vsa, size_t size);
{

  void* allocated = NULL;

  assert(NULL != fsa);


  return allocated;
}*/

/********************************************************************************
*  Description:    free block 
*  Errors:          
*  Parameters:     buffer pointer
*  Return value:   
  Complexity:      O(1)
********************************************************************************/
/*void VSAFree(void *buff);
{
  size_t *tmp = NULL;

  assert(NULL != buff);

}*/

/********************************************************************************
*  Description:    size of largest available memory chunk
*  Errors:          
*  Parameters:     VSA pointer
*  Return value:   size of memory block
  Complexity:      O(n)
********************************************************************************/
/*size_t LargestChunkAvailable(VSA_t *vsa)
{
  return 0;
}*/