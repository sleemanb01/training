#ifndef __FSA_H__
#define __FSA_H__

#include <stddef.h> /* for size_t */ 

typedef struct FSA_struct FSA_t;

/* return size of allocated memory(mem_size) + size of struct */  
size_t FSASuggestSize(size_t block_size, size_t block_num);

/* allocate initial memory for our Alloc() and Free() use */
FSA_t *FSAInit(void *mem, size_t pool_size, size_t block_size);

/* allocate aligned(8) memory from initial allocated memory */
void *FSAAlloc(FSA_t *fsa);

/* free allocated by Alloc() memory */
void FSAFree(FSA_t *fsa, void *node);

/* count remained free blocks */
size_t FSACountFree(FSA_t *fsa);

#endif

