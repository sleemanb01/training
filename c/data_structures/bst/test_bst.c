#include <stdlib.h>	/*malloc, free*/

#include "tests.h"
#include "bst.h"

#define TEST_SIZE 11

#define UNUSED(x) (void)x;

static void	SpecialCreateTree(bst_ty *bst, size_t *arr);

static int CompareFunc(const void *data, const void *to_compare, const void* param);

static int ActionFuncAdd(void * dara, void *params);

void TestBSTCreateDestroy(size_t *arr);

void TestBSTSizeIsEmpty(size_t *arr);

void TestBSTInsertRemovePrevNext(size_t *arr);

void TestBSTNextPrev(size_t *arr);

void TestBSTBeginEnd(size_t *arr);

void TestBSTFindGetData(size_t *arr);

void TestBSTForEach(size_t *arr);

int main()
{

	size_t arr[TEST_SIZE];
	size_t runner = 0;
	
	/*arr = malloc(sizeof(size_t) * TEST_SIZE);
	*/
	for(runner = 0; TEST_SIZE > runner; ++runner )
	{
		arr[runner] = runner;
	}
	
	TestBSTCreateDestroy(arr);
	TestBSTFindGetData(arr);
	
	
	
	
	TestBSTInsertRemovePrevNext(arr);
	
	
	TestBSTBeginEnd(arr);
	
	TestBSTSizeIsEmpty(arr);
	TestBSTNextPrev(arr);
	TestBSTForEach(arr);
	
	
	/*free(arr);
	*/
	PASS;
	return 0;
}

static void	SpecialCreateTree(bst_ty *bst, size_t *arr)
{
	BSTInsert(bst, arr+5);
	BSTInsert(bst, arr+8);
	BSTInsert(bst, arr+6);
	BSTInsert(bst, arr+7);
	BSTInsert(bst, arr+10);
	BSTInsert(bst, arr+9);
	BSTInsert(bst, arr+2);
	BSTInsert(bst, arr+4);
	BSTInsert(bst, arr+3);
	BSTInsert(bst, arr+0);
	BSTInsert(bst, arr+1);
}

static int CompareFunc(const void *data, const void *to_compare, const void* param)
{
	size_t size_t_data = 0, size_t_to_compare = 0;
	size_t_data = *(size_t *)data;
	size_t_to_compare = *(size_t *)to_compare;
	
	UNUSED(param);
	
	if(size_t_data > size_t_to_compare)
	{
		return 1;
	}
	if(size_t_data < size_t_to_compare)
	{
		return -1;
	}
	return 0;
	
}

static int ActionFuncAdd(void *data, void *params)
{
	*(size_t *)data += *(size_t *)params;
	return 0;
}

void TestBSTCreateDestroy(size_t *arr)
{
	bst_ty *bst;
	
	bst = BSTCreate(CompareFunc, NULL);
	
	TEST_NOT_EQUAL("BSTCreate", NULL, bst);
	
	SpecialCreateTree(bst, arr);
	
	BSTDestroy(bst);
}


void TestBSTSizeIsEmpty(size_t *arr)
{
	bst_ty *bst;
	size_t runner = 0;
	bst_iter_ty iter = NULL;
	
	bst = BSTCreate(CompareFunc, NULL);

	TEST_EQUAL("BSTIsEmpty", BSTIsEmpty(bst), 1);
	
	for(runner = 0; runner < TEST_SIZE; ++runner)
	{
		TEST_EQUAL("BSTSize", BSTSize(bst), runner);
		BSTInsert(bst, arr+runner);
		TEST_EQUAL("BSTIsEmpty", BSTIsEmpty(bst), 0);
	}
	
	for(runner = TEST_SIZE-1; runner < TEST_SIZE; --runner)
	{
		iter = BSTFind(bst, arr+runner);
		BSTRemove(iter);
		TEST_EQUAL("BSTSize", BSTSize(bst), runner);
		if(runner == 0)
		{
			break;
		}
	}
		
	TEST_EQUAL("BSTIsEmpty", BSTIsEmpty(bst), 1);
			
	BSTDestroy(bst);
}

static size_t IsOrderd(bst_ty *bst)
{
    bst_iter_ty iter = NULL;
    bst_iter_ty prev = NULL;

    iter = BSTBegin(bst);

    while(!BSTIterIsEqual(BSTNext(iter), BSTEnd(bst)))
    {
        prev = iter;
        iter = BSTNext(iter);

        if(1 == CompareFunc(prev, iter, NULL))
        {
            return 0;
        }
    }
    return 1;
}


void TestBSTInsertRemovePrevNext(size_t *arr)
{
	bst_ty *bst;
	
	bst = BSTCreate(CompareFunc, NULL);
	SpecialCreateTree(bst, arr);
	
	TEST_EQUAL("TestInsert", IsOrderd(bst), 1);
	
	BSTRemove(BSTFind(bst, arr+10));
	TEST_EQUAL("TestBSTRemove", IsOrderd(bst), 1);
	BSTDestroy(bst);
	
	bst = BSTCreate(CompareFunc, NULL);
	SpecialCreateTree(bst, arr);
	BSTRemove(BSTFind(bst, arr+9));
	TEST_EQUAL("TestBSTRemove", IsOrderd(bst), 1);
	BSTDestroy(bst);
	
	bst = BSTCreate(CompareFunc, NULL);
	SpecialCreateTree(bst, arr);
	BSTRemove(BSTFind(bst, arr+8));
	TEST_EQUAL("TestBSTRemove", IsOrderd(bst), 1);
	BSTDestroy(bst);
	
	bst = BSTCreate(CompareFunc, NULL);
	SpecialCreateTree(bst, arr);
	BSTRemove(BSTFind(bst, arr+5));
	TEST_EQUAL("TestBSTRemove", IsOrderd(bst), 1);
	BSTRemove(BSTFind(bst, arr+4));
	TEST_EQUAL("TestBSTRemove", IsOrderd(bst), 1);
	BSTDestroy(bst);
	
	bst = BSTCreate(CompareFunc, NULL);
	SpecialCreateTree(bst, arr);
	BSTRemove(BSTFind(bst, arr+4));
	TEST_EQUAL("TestBSTRemove", IsOrderd(bst), 1);
	BSTRemove(BSTFind(bst, arr+3));
	TEST_EQUAL("TestBSTRemove", IsOrderd(bst), 1);
	BSTDestroy(bst);
	
	bst = BSTCreate(CompareFunc, NULL);
	SpecialCreateTree(bst, arr);
	BSTRemove(BSTFind(bst, arr+4));
	TEST_EQUAL("TestBSTRemove", IsOrderd(bst), 1);
	BSTDestroy(bst);
	
	bst = BSTCreate(CompareFunc, NULL);
	SpecialCreateTree(bst, arr);
	BSTRemove(BSTFind(bst, arr+4));
	TEST_EQUAL("TestBSTRemove", IsOrderd(bst), 1);
	BSTDestroy(bst);
	
}

void TestBSTNextPrev(size_t *arr)
{
	bst_ty *bst;
	bst_iter_ty iter = NULL;
	size_t runner = 0;
	
	bst = BSTCreate(CompareFunc, NULL);
	SpecialCreateTree(bst, arr);
	
	iter = BSTBegin(bst);
	
	for(runner = 0; runner < TEST_SIZE-1; ++runner)
	{
		TEST_EQUAL("TestBSTFindGetData", *(size_t*)BSTGetData(iter), runner);
		iter = BSTNext(iter);
	}
	for(runner = TEST_SIZE-1; runner > 0; --runner)
	{
		TEST_EQUAL("TestBSTFindGetData", *(size_t*)BSTGetData(iter), runner);
		iter = BSTPrev(iter);
	}
	
	BSTDestroy(bst);
}

void TestBSTBeginEnd(size_t *arr)
{
	bst_ty *bst;
	bst_iter_ty iter = NULL;
	size_t runner = 0;
	
	bst = BSTCreate(CompareFunc, NULL);
	SpecialCreateTree(bst, arr);
	
	iter = BSTBegin(bst);

	for(runner = 0; runner < TEST_SIZE-1; ++runner)
	{
		TEST_EQUAL("TestBSTFindGetData", *(size_t*)BSTGetData(iter), runner);
		BSTRemove(iter);
		iter = BSTBegin(bst);
	}
	BSTDestroy(bst);
	
	bst = BSTCreate(CompareFunc, NULL);
	SpecialCreateTree(bst, arr);
	iter = BSTPrev(BSTEnd(bst));
			
	for(runner = TEST_SIZE-1; runner > 0; --runner)
	{
		TEST_EQUAL("TestBSTFindGetData", *(size_t*)BSTGetData(iter), runner);
		BSTRemove(iter);
		iter = BSTPrev(BSTEnd(bst));
	}
	
	BSTDestroy(bst);
}



void TestBSTFindGetData(size_t *arr)
{
	bst_ty *bst;
	size_t runner = 0;
	bst_iter_ty iter = NULL;
	
	bst = BSTCreate(CompareFunc, NULL);	
	SpecialCreateTree(bst, arr);
	
	for(runner = 0; runner < TEST_SIZE; ++runner)
	{
			iter = BSTFind(bst, arr+runner);
			TEST_EQUAL("TestBSTFindGetData", *(size_t*)BSTGetData(iter), runner);
			iter = BSTNext(iter);
	}

	BSTDestroy(bst);
}

void TestBSTForEach(size_t *arr)
{
	bst_ty *bst;
	bst_iter_ty iter = NULL;
	int params = 0;
	size_t runner = 0;
	
	bst = BSTCreate(CompareFunc, NULL);
	SpecialCreateTree(bst, arr);
	
	params = 1;
	BSTForEach( BSTBegin(bst), BSTEnd(bst), &ActionFuncAdd, &params);

	for(runner = 0; runner < TEST_SIZE; ++runner)
	{
			iter = BSTFind(bst, arr+runner);
			TEST_EQUAL("TestBSTForEach", *(size_t*)BSTGetData(iter), runner+1);
			iter = BSTNext(iter);
	}
	
	BSTDestroy(bst);
}
