#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>

#include "../include/etests.h"
#include "recursion.h" 

#define STR_SIZE 20
#define COUNT 20


static int IsStackSorted(stack_t *stk)
{
	int tmp;
	int res = 0;

	
	while (1 < StackSize(stk))
	{
		tmp = *(int*)StackPeek(stk);
		StackPop(stk);

		if (tmp > *(int*)StackPeek(stk))
		{
			return 1;
		}
	}
	return res;
}

void TestFlipList()
{
	int res = 0;
	size_t i = 0;
	int arr[COUNT];
	slist_t *list = SlistCreate();
	slist_iter_t head = SlistBegin(list);

	for (i = 0; i < COUNT; i++)
	{
		arr[i] = i;
	}

	for (i = 0; i < COUNT; i++)
	{
		SlistInsert(SlistBegin(list), &arr[i]);
	}
	
	head = FlipList(head);

	for (i = 0; i < COUNT; i++, head = SlistNext(head))
	{
		if (arr[(COUNT - 1) - i] != *(int*)SlistGetData(head) )
		{
			res = 1;
		}
	}
	
	TEST_EQUAL("test fliped list", res, 0);
}


void TestStackSort()
{
	size_t i = 0;
	int res = 0;
	int arr[] = {20, 1, 12, 14, 7, 5, 11, 3, 9, 6, 17, 4, 18, 16, 2, 15, 19, 8, 10, 13};
	stack_t	*stk = NULL;

	stk = StackCreate(sizeof(int), COUNT);

	assert(NULL != stk);
	for (i = 0; i < COUNT; i++)
	{
		StackPush(stk, &arr[i]);
	}

	SortStack(stk);
	res = IsStackSorted(stk);
	TEST_EQUAL("test stack sort", res, 0);

	StackDestroy(stk);
}

void TestStrings()
{
	char *s1 = "this is not a test";
	char *s2 = "this is A test";
	char s3[STR_SIZE] = { 0 };
	char s4[STR_SIZE] = { 0 };
	char *s41;
	char *s42;

	StrCpy(s4, "maybe");

	TEST_EQUAL("test string length", StrLen(s1), strlen(s1));
	TEST_EQUAL("test string compare", StrCmp(s1, s2), strcmp(s1, s2));

	s41 = StrCpy(s3, s2 + 7);
	s42 = strcpy(s4, s2 + 7);
	TEST_EQUAL("test string copy", strcmp(s3,s4), 0);

 	s41 = StrCat(s4, s2);
	s42 = StrCat(s4, s2);
	TEST_EQUALS("test string concat",s41, s42);
	TEST_EQUAL("test string string", StrStr(s1, "is"), strstr(s1, "is"));
	TEST_EQUAL("test string string", StrStr(s1, "iS"), strstr(s1, "iS"));
}



int main(int argc, char* argv[], char* env[]) 
{  
	(void)argc; 
	(void)argv; 
	(void)env; 

	/*TestFlipList();*/
	/*TestStackSort();*/
	/*TestStrings();*/

	PASS;
	return 0; 
}
