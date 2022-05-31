#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "dlist.h"
#include "tests.h"

void CreateDestroyDlistTest();
void BeginEndDlistTest();
void NextPrevDlistTest();
void GetSetDataDlistTest();
void InsertRemoveDlistTest();
void PushPopBackDlistTest();
void PushPopFrontkDlistTest();
void FindCountDlistTest();
void ForEachDlistTest();
void IsEmptyDlistTest();
void IsSameIterDlistTest();
void SpliceDlistTest();
void MultiFindDlistTest();

int is_match(const void *data, const void *to_match);
int AddOne(void *data, void *params);

int main()
{
	CreateDestroyDlistTest();
	BeginEndDlistTest();
	NextPrevDlistTest();
	GetSetDataDlistTest();
	InsertRemoveDlistTest();
	PushPopBackDlistTest();
	PushPopFrontkDlistTest();
	FindCountDlistTest();
	ForEachDlistTest();
	IsEmptyDlistTest();
	IsSameIterDlistTest();
	SpliceDlistTest();
	MultiFindDlistTest();
	
	PASS;
	return (0);
}

void CreateDestroyDlistTest()
{
	dlist_t *new_list = DlistCreate();
	DlistDestroy(new_list);
}
void BeginEndDlistTest()
{
	dlist_t *new_list = DlistCreate();
	dlist_iter_t first = DlistBegin(new_list);
	dlist_iter_t last = DlistEnd(new_list);
	int status = (first == last);
	
	TEST("DlistBeginEnd()", status, 1);
	DlistDestroy(new_list);
}
void NextPrevDlistTest()
{
	dlist_t *new_list = DlistCreate();
	dlist_iter_t last = NULL, tmp = NULL, test = NULL;
	int status = 0;
	size_t num = 1234, *num_ptr = &num, data = 0, data2 = 0;
	
	tmp = DlistEnd(new_list);
	status = DlistInsert(tmp, num_ptr);
	TEST("DlistInsert()", status, 0);
	last = DlistEnd(new_list);
	tmp = DlistBegin(new_list);
	test = DlistPrev(last);
	
	data = *(size_t*)DlistGetData(test);
	data2 = *(size_t*)DlistGetData(tmp);
	
	TEST("DlistNext()", data, data2);
	
	DlistDestroy(new_list);
}
void GetSetDataDlistTest()
{
	dlist_t *linked_list = DlistCreate();
	dlist_iter_t tmp = NULL;
	int status = 0;
	size_t num = 1234, *num_ptr = &num, num2 = 5678, *num_ptr2 = &num2, *test = NULL;
	
	tmp = DlistBegin(linked_list);
	status = DlistInsert(tmp, num_ptr);
	
	DlistSetData(tmp, num_ptr2);
	assert(0 == status);
	test = (size_t *)DlistGetData(tmp);
	TEST("DlistGetData()", *test, *num_ptr2);
	
	DlistSetData(tmp, num_ptr);
	assert(0 == status);
	test = (size_t *)DlistGetData(tmp);
	TEST("DlistGetData()", *test, *num_ptr);
	
	DlistDestroy(linked_list);
}
void InsertRemoveDlistTest()
{
	dlist_t *linked_list = DlistCreate();
	dlist_iter_t tmp = NULL, first = NULL, last = NULL;
	int status = 0;
	size_t num = 1234, *num_ptr = &num;
	
	tmp = DlistBegin(linked_list);
	status = DlistInsert(tmp, num_ptr);
	tmp = DlistBegin(linked_list);
	status = DlistInsert(tmp, num_ptr);
	status = DlistInsert(tmp, num_ptr);
	
	tmp = DlistBegin(linked_list);
	DlistRemove(tmp);
	tmp = DlistBegin(linked_list);
	DlistRemove(tmp);
	tmp = DlistBegin(linked_list);
	DlistRemove(tmp);
	
	first = DlistBegin(linked_list);
	last = DlistEnd(linked_list);
	status = (first == last);
	TEST("DlistInsertRemove()", status, 1);
	
	DlistDestroy(linked_list);
}
void PushPopBackDlistTest()
{
	dlist_t *linked_list = DlistCreate();
	dlist_iter_t tmp = NULL, first = NULL, last = NULL;
	int status = 0;
	size_t num = 1234, *num_ptr = &num, res = 0, num2 = 5678, *num2_ptr = &num2;
	
	status = DlistPushBack(linked_list, num_ptr);
	TEST("DlistPushBack()", status, 0);
	tmp = DlistBegin(linked_list);
	res = *(size_t *)DlistGetData(tmp);
	TEST("DlistPushBack()", res, num);
	
	status = DlistPushBack(linked_list, num2_ptr);
	res = *(size_t *)DlistPopBack(linked_list);
	TEST("DlistPopBack()", res, num2);
	res = *(size_t *)DlistPopBack(linked_list);
	TEST("DlistPopBack()", res, num);
	
	
	first = DlistBegin(linked_list);
	last = DlistEnd(linked_list);
	status = (last == first);
	TEST("DlistPushPopBack()", status, 1);
	
	DlistDestroy(linked_list);
}

void PushPopFrontkDlistTest()
{
	dlist_t *linked_list = DlistCreate();
	dlist_iter_t tmp = NULL;
	int status = 0;
	size_t num = 1234, *num_ptr = &num, res = 0, num2 = 5678, *num2_ptr = &num2;
	
	status = DlistPushFront(linked_list, num_ptr);
	TEST("DlistPushFront()", status, 0);
	tmp = DlistBegin(linked_list);
	res = *(size_t *)DlistGetData(tmp);
	TEST("DlistPushFront()", res, num);
	
	status = DlistPushFront(linked_list, num2_ptr);
	tmp = DlistBegin(linked_list);
	res = *(size_t *)DlistGetData(tmp);
	TEST("DlistPushFront()", res, num2);
	
	res = *(size_t *)DlistPopFront(linked_list);
	TEST("DlistPopFront()", res, num2);
	res = *(size_t *)DlistPopFront(linked_list);
	TEST("DlistPopFront()", res, num);
	
	
	DlistDestroy(linked_list);
}

int is_match(const void *data, const void *to_match)
{
	size_t size = sizeof(*(size_t *)data);
	int result = memcmp(data, to_match, size);
	return (result == 0);
}

void FindCountDlistTest()
{
	dlist_t *linked_list = DlistCreate();
	dlist_iter_t tmp = NULL, test = NULL;
	int status = 0;
	size_t num = 1234, *num_ptr = &num, num2 = 5678, max = 10, i = 0, size = 0;
	
	for (i = 0; i < max; ++i)
	{
		status = DlistPushFront(linked_list, num_ptr);
		TEST("DlistPushFront()", status, 0);
	}	
	
	size = DlistSize(linked_list);
	TEST("DlistSize()", size, max);
	status = DlistPushFront(linked_list, &num2);
	TEST("DlistPushFront()", status, 0);
	tmp = DlistBegin(linked_list);
	
	for (i = 0; i < max; ++i)
	{
		status = DlistPushFront(linked_list, num_ptr);
		TEST("DlistPushFront()", status, 0);
	}	
	
	size = DlistSize(linked_list);
	TEST("DlistSize()", size, 21);
	
	test = DlistFind(DlistBegin(linked_list), DlistEnd(linked_list), &num2, is_match);
	
	TEST("DlistFind()", tmp, test);
	
	DlistDestroy(linked_list);
}

int AddOne(void *data, void *params)
{
	size_t *tmp = (size_t *)data, param = *(size_t *)params;
	*tmp += param;
	return (0);	
}

void ForEachDlistTest()
{
	dlist_t *linked_list = DlistCreate();
	dlist_iter_t tmp = NULL;
	int status = 0;
	size_t num = 1, num2 = 2, num3 = 3, num4 = 4,  num5 = 5, num6 = 6, test = 0, actual = 6, i = 0, n = 2, param = 1;
	size_t *num_ptr = &num, *num_ptr2 = &num2, *num_ptr3 = &num3, *num_ptr4 = &num4, *num_ptr5 = &num5, *num_ptr6 = &num6, *param_ptr = &param;
	
	status = DlistPushBack(linked_list, num_ptr);
	status = DlistPushBack(linked_list, num_ptr2);
	status = DlistPushBack(linked_list, num_ptr3);
	status = DlistPushBack(linked_list, num_ptr4);
	status = DlistPushBack(linked_list, num_ptr5);
	status = DlistPushBack(linked_list, num_ptr6);
	
	assert(status == 0);
	
	
	
	tmp = DlistForEach(DlistBegin(linked_list), DlistEnd(linked_list), AddOne, param_ptr);
	tmp = DlistBegin(linked_list);
	
	for (i = 0; i < actual; ++i)
	{
		test = *(size_t *)DlistGetData(tmp);
		TEST("DlistForEach()", n, test);
		n +=1;
		tmp = DlistNext(tmp);
	}
	
	DlistDestroy(linked_list);
}
void IsEmptyDlistTest()
{
	dlist_t *linked_list = DlistCreate();
	int status = 0;
	size_t num = 1234, *num_ptr = &num, max = 5, i = 0, res = 0;
	
	status = DlistIsEmpty(linked_list);
	
	TEST("DlistIsEmpty()", status, 1);
	
	for (i = 0; i < max; ++i)
	{
		status = DlistPushBack(linked_list, num_ptr);
	}
	status = DlistIsEmpty(linked_list);
	TEST("DlistIsEmpty()", status, 0);
	
	for (i = 0; i < max; ++i)
	{
		res = *(size_t *)DlistPopBack(linked_list);
	}
	
	TEST("DlistPopFront()", res, num);
	
	status = DlistIsEmpty(linked_list);
	TEST("DlistIsEmpty()", status, 1);
	
	DlistDestroy(linked_list);
}
void IsSameIterDlistTest()
{
	dlist_t *linked_list = DlistCreate();
	dlist_iter_t first = NULL, last = NULL;
	int status = 0;
	size_t num = 1234, *num_ptr = &num, res = 0;
	
	first = DlistBegin(linked_list);
	last = DlistEnd(linked_list);
	
	status = DlistIsSameIter(first, last);
	TEST("DlistIsSameIter()", status, 1);
	
	status = DlistPushBack(linked_list, num_ptr);
	first = DlistBegin(linked_list);
	status = DlistIsSameIter(first, last);
	TEST("DlistIsSameIter()", status, 0);
	res = *(size_t *)DlistPopBack(linked_list);
	TEST("DlistPopFront()", res, num);
	first = DlistBegin(linked_list);
	status = DlistIsSameIter(first, last);
	TEST("DlistIsSameIter()", status, 1);
		
	DlistDestroy(linked_list);
}
void SpliceDlistTest()
{
	dlist_t *linked_list = DlistCreate();
	dlist_t *linked_list2 = DlistCreate();
	dlist_iter_t first = NULL, last = NULL, target = NULL;
	int status = 0;
	size_t num = 1234, *num_ptr = &num, max = 5, i = 0, res = 0;
	
	target = DlistBegin(linked_list2);
	for (i = 0; i < max; ++i)
	{
		status = DlistPushBack(linked_list, num_ptr);
	}
	
	first = DlistBegin(linked_list);
	last = DlistEnd(linked_list);
	
	res = DlistSize(linked_list);
	TEST("DlistSize()", res, max);
	status = DlistIsEmpty(linked_list2);
	TEST("DlistIsEmpty()", status, 1);
	
	DlistSplice(target, first, last);
	res = DlistSize(linked_list2);
	TEST("DlistSize()", res, max);
	status = DlistIsEmpty(linked_list);
	TEST("DlistIsEmpty()", status, 1);
	
	DlistDestroy(linked_list);
	DlistDestroy(linked_list2);
}
void MultiFindDlistTest()
{
	dlist_t *linked_list = DlistCreate();
	dlist_t *linked_list2 = DlistCreate();
	dlist_iter_t first = NULL, last = NULL;
	int status = 0;
	size_t num = 1234, *num_ptr = &num, num2 = 5678, *num2_ptr = &num2, max = 5, i = 0, res = 0;
	
	for (i = 0; i < max; ++i)
	{
		status = DlistPushBack(linked_list, num_ptr);
		status = DlistPushBack(linked_list, num2_ptr);
	}
	
	first = DlistBegin(linked_list);
	last = DlistEnd(linked_list);
	
	res = DlistSize(linked_list);
	TEST("DlistSize()", res, (max * 2));
	res = DlistSize(linked_list2);
	TEST("DlistSize()", res, 0);
	
	status = DlistMultiFind(first, last, num2_ptr, is_match, linked_list2);
	assert(status == 0);
	
	res = DlistSize(linked_list2);
	TEST("DlistSize()", res, max);
	
	DlistDestroy(linked_list);
	DlistDestroy(linked_list2);
}
