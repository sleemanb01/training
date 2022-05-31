#include <stddef.h>		/* size_t */
#include<string.h>      /*strcmp */

#include"circular_buffer.h"
#include"tests.h"

void createDestroy();
void readWrite();
void freeCap();

struct cbuff{
    size_t capacity;
    size_t write;
    size_t read;
    size_t size;
    char *buff;
};

int main()
{
	createDestroy();
	readWrite();
	freeCap();

	PASS;

	return 0;
}

void createDestroy()
{
	size_t size = 10;
	int status = 0;
	cbuffer_t *new_buff = CBCreate(size);
	status = CBBufIsEmpty(new_buff);
	
	TEST("IsEmptyTest()", status, 1);
	CBDestroy(new_buff);

}

void readWrite()
{
	size_t size = 10, write = 9, read = 9;
	ssize_t ret_val = 0, *ret_val_ptr = &ret_val;
	char arr[10] = "abcdefghi";
	char ret_arr[10];
	int status = 0;
	cbuffer_t *new_buff = CBCreate(size);
	
	*ret_val_ptr = CBBufWrite(new_buff, arr, write);
	TEST("WriteTest()", ret_val, (ssize_t)write);
	
	status = CBBufIsEmpty(new_buff);
	TEST("IsEmptyTest()", status, 0);
	
	*ret_val_ptr = CBBufRead(new_buff, ret_arr, read);
	TEST("ReadTest()", ret_val, (ssize_t)read);

	*ret_val_ptr = CBBufWrite(new_buff, arr, write);
	TEST("WriteTest()", ret_val, (ssize_t)write);
	*ret_val_ptr = CBBufRead(new_buff, ret_arr, read);
	TEST("ReadTest()", ret_val, (ssize_t)read);
	
	*ret_val_ptr = CBBufWrite(new_buff, arr, write);
	TEST("WriteTest()", ret_val, (ssize_t)write);
	*ret_val_ptr = CBBufRead(new_buff, ret_arr, read);
	TEST("ReadTest()", ret_val, (ssize_t)read);
	
	*ret_val_ptr = CBBufWrite(new_buff, arr, write);
	TEST("WriteTest()", ret_val, (ssize_t)write);
	*ret_val_ptr = CBBufRead(new_buff, ret_arr, read);
	TEST("ReadTest()", ret_val, (ssize_t)read);
	
	*ret_val_ptr = CBBufWrite(new_buff, arr, write);
	TEST("WriteTest()", ret_val, (ssize_t)write);
	*ret_val_ptr = CBBufRead(new_buff, ret_arr, read);
	TEST("ReadTest()", ret_val, (ssize_t)read);
	
	*ret_val_ptr = CBBufWrite(new_buff, arr, write);
	TEST("WriteTest()", ret_val, (ssize_t)write);
	*ret_val_ptr = CBBufRead(new_buff, ret_arr, read);
	TEST("ReadTest()", ret_val, (ssize_t)read);
	
	*ret_val_ptr = CBBufWrite(new_buff, arr, write);
	TEST("WriteTest()", ret_val, (ssize_t)write);
	*ret_val_ptr = CBBufRead(new_buff, ret_arr, read);
	TEST("ReadTest()", ret_val, (ssize_t)read);
	
	*ret_val_ptr = CBBufWrite(new_buff, arr, write);
	TEST("WriteTest()", ret_val, (ssize_t)write);
	*ret_val_ptr = CBBufRead(new_buff, ret_arr, read);
	TEST("ReadTest()", ret_val, (ssize_t)read);
	
	*ret_val_ptr = CBBufWrite(new_buff, arr, write);
	TEST("WriteTest()", ret_val, (ssize_t)write);
	*ret_val_ptr = CBBufRead(new_buff, ret_arr, read);
	TEST("ReadTest()", ret_val, (ssize_t)read);
	

	
	status = strcmp(arr, ret_arr);
	TEST("ReadTest()", status, 0);
	
	CBDestroy(new_buff);

}

void freeCap()
{
	size_t size = 10, write = 7, cap = 0, free_space = 0;
	ssize_t ret_val = 0, *ret_val_ptr = &ret_val;
	const char *arr = "abcdef";
	cbuffer_t *new_buff = CBCreate(size);
	
	cap = CBBufSize(new_buff);
	TEST("SizeTest()", cap, size);
	free_space = CBFreeSpace(new_buff);
	TEST("FreeSpaceTest()", free_space, size);
	
	*ret_val_ptr = CBBufWrite(new_buff, arr, write);
	
	cap = CBBufSize(new_buff);
	TEST("SizeTest()", cap, size);
	free_space = CBFreeSpace(new_buff);
	TEST("FreeSpaceTest()", free_space, (size - ret_val));
	
	CBDestroy(new_buff);

}

