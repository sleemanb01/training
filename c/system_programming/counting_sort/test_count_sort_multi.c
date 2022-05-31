#define _POSIX_C_SOURCE 200809L

#include <stddef.h> /* for size_t */
#include <time.h> /* for rand */
#include <stdlib.h> /* for malloc */
#include <string.h> /* for strcpy */
#include <stdio.h> /* for getline */

#include "count_sort_multi.h"
#include "tests.h"

#define MAX_STR 80
#define DICTIONARY_SIZE 102401
#define WORD_SIZE 8
#define ARR_SIZE 5000


int g_i = 0;

void InitArray(int *arr, size_t size, size_t limit);
void InitArrayNeg(int *arr, size_t size, size_t limit);
void CountingTest(void);
void CountingNegativeTest(void);
void CountingDictTest(char **arr);
ssize_t GetData(const void *data);
static void GetDict(char **arr);
ssize_t GetFirstChar(const void *data);

int main()
{
	char **dict = NULL;
	int i = 0;
	/* CountingTest();
	CountingNegativeTest();
	 */
	dict = calloc(DICTIONARY_SIZE * sizeof(void *), 3);
    if (!dict)
    {
        return (0);
    }

	GetDict(dict);
	GetDict(dict);
	GetDict(dict);
	
	CountingSort(dict, DICTIONARY_SIZE * 3, WORD_SIZE, GetFirstChar);
	for (i = 0; i < 100; i++)
	{
		printf(" %s\n", dict[i]);
	}
	
	for (i = 0; i <(DICTIONARY_SIZE * 3); ++i)
	{
		free(dict[i]);
	}
	free(dict);
	PASS;
	return (0);
}

void InitArray(int *arr, size_t size, size_t limit)
{
	size_t i = 0;
	srand(time(NULL));
	
	for (i = 0; i < size; ++i)
	{
		arr[i] = (rand() % limit);
	}
}

void InitArrayNeg(int *arr, size_t size, size_t limit)
{
	size_t i = 0;
	srand(time(NULL));
	
	for (i = 0; i < size; ++i)
	{
		arr[i] = ((rand() % limit) - 50);
	}
}

void CountingTest()
{
	int i = 0, *random_arr = NULL;
	int elem_size = 4;
	random_arr = malloc(sizeof(int) * ARR_SIZE);
	if (NULL == random_arr)
	{
		return;
	}
	InitArray(random_arr, ARR_SIZE, 101);
	CountingSort(random_arr, ARR_SIZE, elem_size, GetData);
	for (i = 1; i < ARR_SIZE; ++i)
	{
		TEST_SEQ("CountingSort()", random_arr[i - 1], random_arr[i]);
	}
	free(random_arr);
}

void CountingNegativeTest()
{
	int i = 0, *random_arr = NULL;
	random_arr = malloc(sizeof(int) * ARR_SIZE);
	if (NULL == random_arr)
	{
		return;
	}
	InitArrayNeg(random_arr, ARR_SIZE, 101);
	CountingSort(random_arr, ARR_SIZE, 4, GetData);
	for (i = 1; i < ARR_SIZE; ++i)
	{
		TEST_SEQ("CountingSort()", random_arr+(i - 1), random_arr+i);
	}
	free(random_arr);
}
ssize_t GetData(const void *data)
{
	ssize_t ret = *(int*)data;
	return (ret);
}

static void GetDict(char **arr)
{
    char dict_word[MAX_STR];
	FILE *dict = NULL;

    if (NULL == (dict = fopen("/usr/share/dict/words", "r")))
    {
        return;
    }
    
	fseek(dict, 0, SEEK_SET);

    while (fgets(dict_word, MAX_STR, dict)/*  getline(&dict_word, &word_len, dict) */)
	{
		char *new_word = NULL;
		new_word = malloc(strlen(dict_word));
		if(!new_word)
		{
			return;
		}
		dict_word[strlen(dict_word) - 1] = '\0';
		strcpy(new_word, dict_word);
		arr[g_i] = new_word;
		++g_i;
	}
    fclose(dict);
}


ssize_t GetFirstChar(const void *data)
{
	char *c = NULL;
	ssize_t val = 0;
	c = *(char **)data;
	val = *c;
	return (val);
}
