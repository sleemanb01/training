#define _POSIX_C_SOURCE 200809L

#include <stddef.h> /* for size_t */
#include <time.h> /* for rand */
#include <stdlib.h> /* for malloc */
#include <string.h> /* for strcpy */
#include <stdio.h> /* for getline */

#include "shuffle_and_sort.h"
#include "tests.h"

#define MAX_WORD 24
#define DICTIONARY_SIZE 102401
#define WORD_SIZE 8
#define DICT_MULTI 8
#define ARR_SIZE (DICTIONARY_SIZE * DICT_MULTI)
#define UNUSED(x) (void)x
#define THREADS 8

enum { NS_PER_SECOND = 1000000000 };

void sub_timespec(struct timespec t1, struct timespec t2, struct timespec *td);
static void GetDict(void **arr);
int StrCmp(const void *word1, const void *word2);

int main()
{
    struct timespec start[THREADS + 1], end[THREADS + 1], delta[THREADS + 1];
    void **dict = NULL;
	int i = 0;
	 
	dict = calloc(DICTIONARY_SIZE * sizeof(void *), DICT_MULTI);
    if (!dict)
    {
        return (0);
    }

	GetDict(dict);
    srand(time(NULL));

    for (i = 0; i < DICTIONARY_SIZE; ++i)
    {
        dict[i + DICTIONARY_SIZE] = dict[i];
        dict[i + (DICTIONARY_SIZE * 2)] = dict[i];
        dict[i + (DICTIONARY_SIZE * 3)] = dict[i];
        dict[i + (DICTIONARY_SIZE * 4)] = dict[i];
        dict[i + (DICTIONARY_SIZE * 5)] = dict[i];
        dict[i + (DICTIONARY_SIZE * 6)] = dict[i];
        dict[i + (DICTIONARY_SIZE * 7)] = dict[i];
    }
	
    MTQuickSort((char**)dict, ARR_SIZE, THREADS);

    for (i = 1; i < ARR_SIZE; ++i)
	{
	 	int res = strcmp((char*)dict[i - 1], (char*)dict[i]);
        TEST_SEQ("CountingSort()",res , 0);
        if (res > 0)
        {
            printf("prev - %s\n",dict[i-1]);
            printf("curr - %s\n",dict[i]);
            printf("prev index - %d\n",i-1);
            printf("curr index - %d\n",i);

        }
	}
    for (i = 0; i < ARR_SIZE; i += DICT_MULTI)
	{
		free(dict[i]);
        dict[i] = NULL;
	}

	free(dict);
	PASS;
	return (0);
}


static void GetDict(void **arr)
{
    char dict_word[80];
	FILE *dict = NULL;
    size_t i = 0;

    if (NULL == (dict = fopen("/usr/share/dict/words", "r")))
    {
        return;
    }
    
	fseek(dict, 0, SEEK_SET);

    while (fgets(dict_word, 80, dict))
	{
		char *new_word = NULL;
		new_word = malloc(strlen(dict_word));
		if(!new_word)
		{
			return;
		}
		dict_word[strlen(dict_word) - 1] = '\0';
		strcpy(new_word, dict_word);
		arr[i] = new_word;
		++i;
	}
    fclose(dict);
}



int StrCmp(const void *word1, const void *word2)
{
    return (strcmp((char *)word1, (char *)word2));
}

void sub_timespec(struct timespec t1, struct timespec t2, struct timespec *td)
{
    td->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    td->tv_sec  = t2.tv_sec - t1.tv_sec;
    if (td->tv_sec > 0 && td->tv_nsec < 0)
    {
        td->tv_nsec += NS_PER_SECOND;
        td->tv_sec--;
    }
    else if (td->tv_sec < 0 && td->tv_nsec > 0)
    {
        td->tv_nsec -= NS_PER_SECOND;
        td->tv_sec++;
    }
}
