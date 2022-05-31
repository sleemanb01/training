#define  _GNU_SOURCE
#include <stdio.h>     /* printf */
#include <string.h>    /* strlen */ 
#include <stdlib.h>    /* malloc */
#include <ctype.h>     /* tolower */


#include "tests.h"
#include "hash.h"

/***********************************************************************************************
*                                         EXTRA FUNCS                                          *
************************************************************************************************/

size_t getHash(const void *data);
int toLower(void *data, void *params);
int is_match(const void *data, const void *to_match);
void createTable(hash_func_ty func, is_match_ty compare_func);

/***********************************************************************************************
*                                         TEST FUNCS                                           *
************************************************************************************************/

void InsertTest();
void RemoveSizeIsEmpty();
void FindTest();
void ForEachTest();

/***********************************************************************************************
*                                         STRUCTS                                              *
************************************************************************************************/

struct hash
{
    dlist_t **hash_table;
    size_t size;
    size_t capacity;
    is_match_ty compare_func;
    hash_func_ty func;
};

struct dlist_node
{
    void *data;
    dlist_node_t *next;
    dlist_node_t *prev;
};

struct dlist
{
    dlist_node_t head;
    dlist_node_t tail;
};

/***********************************************************************************************
*                                           CONSTS                                             *
************************************************************************************************/

#define INPUTS 102401
#define TABLESIZE 10240
#define BUFFSIZE 255
#define DICT_PATH "/usr/share/dict/words"
hash_ty *dictionary = NULL;


/***********************************************************************************************
*                                         MAIN                                                 *
************************************************************************************************/

int main()
{

	dictionary = HashCreate(TABLESIZE, &getHash, &is_match);

	InsertTest();
	RemoveSizeIsEmpty();
	FindTest();
	ForEachTest();

	HashDestroy(dictionary);
	
	PASS;
	return 0;
}

/***********************************************************************************************
*                                         TEST FUNCS                                           *
************************************************************************************************/

/************************************* INSERT *****************************/
void InsertTest()
{

	/*FILE* file;
	char *buffer = NULL;

	buffer = malloc(BUFFSIZE);
	if(NULL != buffer)
	{
		file = fopen(DICT_PATH, "r");

		while(fgets(buffer, BUFFSIZE, file)) 
		{
			if(HashInsert(dictionary,buffer))
			{
				printf("*** INSERT ERROR %d ***\n",__LINE__);
			}
		}

		fclose(file);
	}
	else
	{
		printf("*** MALLOC ERROR %d ***\n",__LINE__);
	}*/

    size_t len = 0, count = 0;
    FILE *file = NULL;
    char *line = NULL;

    file = fopen(DICT_PATH, "r");

    while (-1 != getline(&line, &len, file))
    {
        char *new_line = malloc(sizeof(char) * len);
        strcpy(new_line, line);
        new_line[strlen(new_line) - 1] = '\0';
        HashInsert(dictionary, new_line);
		free(new_line);
        ++count;
    }

    
    fclose(file);
    TEST("size after fill", HashSize(dictionary), INPUTS);
}

/**************************** REMOVE/SIZE/ISEMPTY *************************/
void RemoveSizeIsEmpty()
{
	size_t table_size = 0;
	int is_empty = 1;
	char random_word = 'A';
	void *data;

	data = (void*)&random_word;

	table_size = HashSize(dictionary);
	is_empty = HashIsEmpty(dictionary);

	TEST_EQUAL("HashSize()", table_size, INPUTS);
	TEST_EQUAL("HashIsEmpty()", is_empty, 0);

	HashRemove(dictionary, data);
	TEST_EQUAL("HashSize()", HashSize(dictionary), (table_size - 1));
}

/****************************** FIND ***************************************/
void FindTest()
{
	char random_word[] = "whelp";
	void *data;

	data = (void*)&random_word;

	TEST_EQUAL("HashFind()",*(char*)HashFind(dictionary, data),*(char*)data);
}

/****************************** FOREACH ************************************/
void ForEachTest()
{
	char random_word[] = "Abbas";
	void *data;
	int mode = 1;

	HashForEach(dictionary,toLower,&mode);

	data = (void*)&random_word;

	TEST_EQUAL("HashForEach()",(char*)HashFind(dictionary, data),NULL);
}

/***********************************************************************************************
*                                         EXTRA FUNCS                                          *
************************************************************************************************/

/****************************** GET HASH ************************************/
size_t getHash(const void *data)
{
	const int p = 31;
    long p_pow = 1;
	char *str;
    size_t hash = 0;

    for(str = (char*)data ;('\0' != *str ) && ('\n' != *str ); ++str) 
	{
        hash += (((tolower(*str) - 'a') * p_pow));
        p_pow = (p_pow * p);
    }

    return (hash % TABLESIZE);
}

/****************************** ADD ONE ************************************/
int toLower(void *data, void *params)
{
	char *tmp = NULL;

	tmp = (char*)data;

	if(1 == *(int*)params)
	{
		while('\0' != *tmp)
		{
			*tmp = tolower(*tmp);
			++tmp;
		}
	}
	return 0;	
}

/****************************** IS MATCH ************************************/
int is_match(const void *data, const void *to_match)
{
	char *data_key = NULL;
	char *compare_key = NULL;

    data_key = (char*)data;
    compare_key = (char*)to_match;

	if(NULL == data_key || NULL == compare_key)
	{
		return 1;
	}

    return (0 == strcmp(data_key,compare_key));
}
