#ifndef __CBUFFER_H__
#define __CBUFFER_H__

#include <stddef.h>    /*size_t*/
#include <sys/types.h> /*for ssize_t */

typedef struct cbuff cbuffer_t;

/*struct cbuff
{
    void* readptr;
    void* writeptr;
    void* buffstart;
    void* buffend;
    size_t count;
};*/


/**by pointer **
struct cbuff{
    void *end;
    void *current_write;
    void *current_read;
    char *buff;
};*/

/**by index[] **
struct cbuff{
    size_t capacity;
    size_t index;
    size_t size;
    char *buff;
};*/

/*malloc(sizeof(struct cbuff) + capacity*num_element)
cbuff->buff = (cbuff + sizeof(struct cbuff));*/

/*Create a new CBuffer of size buffer_size. Each element is of size element_size*/
cbuffer_t* CBCreate(size_t capacity);

/*Destroy CBuffer given */
void CBDestroy(cbuffer_t* buff); 

/*Returns the total of free bytes in the CBuffer*/
size_t CBFreeSpace(const cbuffer_t* buff);

/*Returns the total size of the buffer*/
size_t CBBufSize(const cbuffer_t* buff);

/*Read from a buffer in a place minus last write, reads from buff into data, 'read_size' bytes*/
ssize_t CBBufRead(cbuffer_t* buff, void *dest, size_t read_size);

/*Write to a buffer in a given place*/
ssize_t CBBufWrite(cbuffer_t* buff, const void *src, size_t write_size);

/*Check if CBuffer is empty, return 1 if it is, 0 otherwise*/
int CBBufIsEmpty(const cbuffer_t* buff);

#endif
