#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "fsa.h"
#include "tests.h"

#define BLOCK_SIZE 12
#define BLOCKS 20


size_t FSASuggestSizeTest();

struct test
{
	unsigned int age;
	float grade;
	char name[4];
};

typedef struct test test_t;

int main()
{
	size_t sug_size = 0, i = 0;
	test_t *arr[BLOCKS];
	FSA_t *new_fsa = NULL;
	void *new = NULL;
	
	sug_size = FSASuggestSizeTest();
	new = malloc(sug_size);
	if (NULL == new)
	{
		return (1);
	}
	
	new_fsa = FSAInit(new , sug_size, BLOCK_SIZE);

	for (i = 0; i < BLOCKS; ++i)
	{
		TEST("AllocTest()", FSACountFree(new_fsa), (BLOCKS - i));
		arr[i] = (test_t *)FSAAlloc(new_fsa);
	}
	
	for (i = 0; i < BLOCKS; ++i)
	{
		arr[i]->age = 10;
		arr[i]->grade = 4.5;
		arr[i]->name[0] = 'A';
		arr[i]->name[1] = 'v';
		arr[i]->name[2] = 'i';
	}
	
	
	
	TEST("AllocTest()", FSACountFree(new_fsa), 0);

	for (i = 0; i < BLOCKS; ++i)
	{
		TEST("FreeTest()", FSACountFree(new_fsa), i);
		FSAFree(new_fsa, arr[i]);
	}

	free(new);
	
	PASS;
	return (0);
}

size_t FSASuggestSizeTest()
{
	size_t size = FSASuggestSize(BLOCK_SIZE, BLOCKS);
	TEST("SizeTest()", size, 336);
	return (size);
}
