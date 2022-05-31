/***************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : CIRCULAR BUFFER
* REVIEWER NAME : ANTON
*****************************************************/

#include<stdlib.h>
#include<stddef.h>
#include<string.h>

#include"circular_buffer.h"

/**by index[]  ADD MAGIC NOUMBER **/
struct cbuff{
    size_t capacity;
    size_t read;
    size_t write;
    size_t size;
    char *buff;
};

/*Create a new CBuffer of size buffer_size. Each element is of size element_size*/
cbuffer_t* CBCreate(size_t capacity)
{
	char *str;
	cbuffer_t *new;
	size_t size = (sizeof(char) * capacity);

	str = malloc(size);
	new = malloc(sizeof(cbuffer_t) + size);

	if(NULL == new)
	{
		return NULL;
	}

	new->capacity = capacity;
	new->read = 0;
	new->write = 0;
	new->size = 0;
	new->buff = str;

	return new;

}

/*Destroy CBuffer given */
void CBDestroy(cbuffer_t* buff)
{
	if(NULL == buff)
	{
		return;
	}

	free(buff->buff);
	free(buff);
	buff = NULL;
}

/*Returns the total of free bytes in the CBuffer*/
size_t CBFreeSpace(const cbuffer_t* buff)
{

	return (buff->capacity - buff->size);
}

/*Returns the total size of the buffer*/
size_t CBBufSize(const cbuffer_t* buff)
{
	return buff->capacity;
}

/*Read from a buffer in a place minus last write, reads from buff into data, 'read_size' bytes*/
ssize_t CBBufRead(cbuffer_t* buff, void *dest, size_t read_size)
{
	size_t i = 0;
	char *dst = (char*)dest;
	for(; (i < read_size) && !CBBufIsEmpty(buff); ++i, ++buff->read, --buff->size)
	{
		if(buff->read == (buff->capacity)) /* consider reading untill EOA */
		{
			buff->read =0;
		}

		dst[i] = buff->buff[buff->read];
	}

	return (ssize_t)i;
}

/*Write to a buffer in a given place*/
ssize_t CBBufWrite(cbuffer_t* buff, const void *src, size_t write_size)
{
	size_t i = 0;
	const char *sr = src;
	for(; (i < write_size) && (CBFreeSpace(buff) > 0); ++i , ++buff->write, ++buff->size)
	{
		if(buff->write == (buff->capacity))
		{
			buff->write =0;
		}

		buff->buff[buff->write] = sr[i];
	}

	return (ssize_t)i;
}

/*Check if CBuffer is empty, return 1 if it is, 0 otherwise*/
int CBBufIsEmpty(const cbuffer_t* buff)
{
	return (0 == buff->size);
}
