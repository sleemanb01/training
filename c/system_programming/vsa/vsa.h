#ifndef __VSA_H__
#define __VSA_H__

#include <stddef.h> /* for size_t */ 

typedef struct VSA_struct VSA_t;

/* allocate initial memory for our Alloc() and Free() use */
VSA_t *VSAInit(void *mem, size_t pool_size);

/* allocate aligned to word size memory from initial allocated memory */
void *VSAAlloc(VSA_t *vsa, size_t size);

/* free block in O(1) complexity */
void VSAFree(void *buff);

/* size of largest available memory chunk */
size_t LargestChunkAvailable(VSA_t *vsa);

#endif

