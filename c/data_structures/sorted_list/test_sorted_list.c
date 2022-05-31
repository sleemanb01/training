#include <stddef.h>
#include <stdio.h>

#include "sorted_list.h"
#include "tests.h"

#define UNUSED(x) (void)(x)

int action_func(void *data, void *params);
int match_func(void *data, void *to_match);
int compare_func(void *data, void *to_compare);
void SortedListCreateDestroyTest(void);
void SortedListBeginEndTest(void);
void SortedListNextPrevTest(void);
void SortedListGetTest(void);
void SortedListIterIsEqualTest(void);
void SortedListSizeIsEmptyTest(void);
void SortedListInsertRemoveTest(void);
void SortedListPopFrontBackTest(void);
void SortedListFindFindIfTest(void);
void SortedListForEachTest(void);
void SortedListMergeTest(void);

int main()
{
	SortedListCreateDestroyTest();
	SortedListBeginEndTest();
	SortedListNextPrevTest();
	SortedListGetTest();
	SortedListIterIsEqualTest();
	SortedListSizeIsEmptyTest();
	SortedListInsertRemoveTest();
	SortedListPopFrontBackTest();
	SortedListFindFindIfTest();
	SortedListForEachTest();
	SortedListMergeTest();
	
	PASS;
	return (0);
}

int compare_func(void *data, void *to_compare)
{
	int result = 0;
	size_t new_data = *(size_t *)data, list_data = *(size_t *)to_compare;
	
	if (new_data < list_data)
	{
		result = (-1);
	}
	else if (new_data > list_data)
	{
		result = 1;
	}
	
	
	return (result);
}

void SortedListCreateDestroyTest(void)
{
	sort_list_t *new_list = SortedListCreate(*compare_func);
	SortedListDestroy(new_list);
}

void SortedListBeginEndTest(void)
{
	sort_list_t *new_list = SortedListCreate(compare_func);
	sort_list_iter_t begin = SortedListBegin(new_list);
	sort_list_iter_t end = SortedListEnd(new_list);
	TEST("SortListBeginEnd()", end.iter, begin.iter);
	
	SortedListDestroy(new_list);
}

void SortedListNextPrevTest(void)
{
	sort_list_t *new_list = SortedListCreate(compare_func);
	sort_list_iter_t iter1 = SortedListBegin(new_list);
	sort_list_iter_t iter2 = SortedListEnd(new_list);
	size_t num = 10, num2 = 9, test = 0, test2 = 0;
	
	iter1 = SortedListInsert(new_list, &num);
	test = *(size_t *)SortedListGetData(iter1);
	TEST("SortListPrev()", SortedListGetData(iter1), SortedListGetData(SortedListPrev(iter2)));

	iter1 = SortedListInsert(new_list, &num2);
	iter2 = SortedListEnd(new_list);
	iter1 = SortedListBegin(new_list);
	test = *(size_t *)SortedListGetData(SortedListPrev(iter2));
	test2 = *(size_t *)SortedListGetData(SortedListNext(iter1));
	TEST("SortListNext()",test2 , test);
	
	SortedListDestroy(new_list);
}

void SortedListGetTest(void)
{
	sort_list_t *new_list = SortedListCreate(*compare_func);
	sort_list_iter_t iter;
	size_t num = 10, *num_ptr = &num, num2 = 15, *num2_ptr = &num2;
	
	iter = SortedListInsert(new_list, num_ptr);
	iter = SortedListInsert(new_list, num2_ptr);
	
	iter = SortedListBegin(new_list);
	TEST("SortListGetData()", *(size_t *)SortedListGetData(iter), num2);
	iter = SortedListNext(iter);
	TEST("SortListGetData()", *(size_t *)SortedListGetData(iter), num);
	
	SortedListDestroy(new_list);
}

void SortedListIterIsEqualTest(void)
{
	sort_list_t *new_list = SortedListCreate(compare_func);
	sort_list_iter_t iter1 = SortedListBegin(new_list);
	sort_list_iter_t iter2 = SortedListEnd(new_list);
	size_t i = 0;
	
	TEST("SortListIterIsEqual()", SortedListIterIsEqual(iter1, iter2), 1);
	for (i = 0; i < 10; ++i)
	{
		iter1 = SortedListInsert(new_list, &i);
	}
	
	for (i = 0; i < 5; ++i)
	{
		iter2 = SortedListPrev(iter2);
	}
	iter1 = SortedListBegin(new_list);
	TEST("SortListIterIsEqual()", SortedListIterIsEqual(iter1, iter2), 0);
	
	for (i = 0; i < 5; ++i)
	{
		iter1 = SortedListNext(iter1);
	}
	
	TEST("SortListIterIsEqual()", SortedListIterIsEqual(iter1, iter2), 1);
	
	SortedListDestroy(new_list);
}

void SortedListSizeIsEmptyTest(void)
{
	sort_list_t *new_list = SortedListCreate(compare_func);
	sort_list_iter_t iter1 = SortedListBegin(new_list);
	size_t i = 0;
	
	TEST("SortListIsEmpty()", SortedListIsEmpty(new_list), 1);
	TEST("SortListSize()", SortedListSize(new_list), 0);
	
	for (i = 0; i < 10; ++i)
	{
		iter1 = SortedListInsert(new_list, &i);
	}
	UNUSED(iter1);
	TEST("SortListIsEmpty()", SortedListIsEmpty(new_list), 0);
	TEST("SortListIsSize()", SortedListSize(new_list), 10);
	
	SortedListDestroy(new_list);
}

void SortedListInsertRemoveTest(void)
{
	sort_list_t *new_list = SortedListCreate(compare_func);
	sort_list_iter_t iter1 = SortedListBegin(new_list);
	
	size_t i = 0;
	
	TEST("SortListSize()", SortedListSize(new_list), 0);
	for (i = 0; i < 10; ++i)
	{
		TEST("SortListSize()", SortedListSize(new_list), i);
		iter1 = SortedListInsert(new_list, &i);
	}
	
	iter1 = SortedListBegin(new_list);
	for (i = 10; i > 0; --i)
	{
		TEST("SortListSize()", SortedListSize(new_list), i);
		iter1 = SortedListRemove(iter1);
	}
	TEST("SortListSize()", SortedListSize(new_list), 0);
	SortedListDestroy(new_list);
}

void SortedListPopFrontBackTest(void)
{
	sort_list_t *new_list = SortedListCreate(compare_func);
	sort_list_iter_t iter1 = SortedListBegin(new_list);
	
	size_t i = 0, num = 555, head = 123, tail = 678, poped_back = 0, poped_front = 0;
	
	iter1 = SortedListInsert(new_list, &head);
	for (i = 0; i < 10; ++i)
	{
		iter1 = SortedListInsert(new_list, &num);
	}
	iter1 = SortedListInsert(new_list, &tail);
	UNUSED(iter1);
	poped_back = *(size_t *)SortedListPopBack(new_list);
	poped_front = *(size_t *)SortedListPopFront(new_list);
	
	TEST("SortListPopBack()", poped_back, head);
	TEST("SortListPopFront()", poped_front, tail);
	
	SortedListDestroy(new_list);
}

int match_func(void *data, void *to_match)
{
	int result = 0;
	if (0 ==(*(size_t *)data % *(size_t *)to_match))
	{
		result = 1;
	}
	return (result);
}

void SortedListFindFindIfTest(void)
{
	sort_list_t *new_list = SortedListCreate(compare_func);
	sort_list_iter_t iter1 = SortedListBegin(new_list);
	sort_list_iter_t iter2;
	size_t i = 0, num = 5, *num_ptr = &num, num2 = 10, *num2_ptr = &num2, num3 = 15, match_modulu = 2, *match = &match_modulu;
	
	for (i = 0; i < 5; ++i)
	{
		iter1 = SortedListInsert(new_list, num_ptr);
	}
	iter1 = SortedListInsert(new_list, num2_ptr);
	for (i = 0; i < 5; ++i)
	{
		iter1 = SortedListInsert(new_list, &num3);
	}
	
	
	iter1 = SortedListBegin(new_list);
	iter2 = SortedListEnd(new_list);
	iter1 = SortedListFind(iter1, iter2, new_list, num2_ptr);
	
	
	iter2 = SortedListBegin(new_list);
	for (i = 0; i < 5; ++i)
	{
		iter2 = SortedListNext(iter2);
	}
	
	TEST("SortListIterIsEqual()", SortedListIterIsEqual(iter1, iter2), 1);
	TEST("SortListFind()", *(size_t *)SortedListGetData(iter1), *(size_t *)SortedListGetData(iter2));
	
	
	iter1 = SortedListBegin(new_list);
	iter2 = SortedListEnd(new_list);
	iter1 =	SortedListFindIf(iter1, iter2, match_func, match);
	
	iter2 = SortedListBegin(new_list);
	for (i = 0; i < 5; ++i)
	{
		iter2 = SortedListNext(iter2);
	}
	TEST("SortListIterIsEqual()", SortedListIterIsEqual(iter1, iter2), 1);
	TEST("SortListFind()", *(size_t *)SortedListGetData(iter1), *(size_t *)SortedListGetData(iter2));
	SortedListDestroy(new_list);
}

int TimesParam(void *data, void *params)
{
	*(size_t *)data *= *(size_t *)params;
	return (0);
}
void SortedListForEachTest(void)
{
	sort_list_t *new_list = SortedListCreate(compare_func);
	sort_list_iter_t iter1 = SortedListBegin(new_list);
	sort_list_iter_t start_iter, end_iter;
	size_t i = 0, data = 1, params = 10, *params_ptr = &params;
	size_t arr[10];
	for (i = 0; i < 10; ++i)
	{
		arr[i] = data;
		iter1 = SortedListInsert(new_list, &arr[i]);
		data += 1;
	}
	start_iter = SortedListBegin(new_list);
	end_iter = SortedListEnd(new_list);
	iter1 = SortedListForeach(start_iter, end_iter, TimesParam, params_ptr);
	end_iter = SortedListPrev(end_iter);
	for (i = 0; i < 10; ++i)
	{
		data = *(size_t *)SortedListGetData(end_iter);
		end_iter = SortedListPrev(end_iter);
		TEST("SortListForEach()", data, *params_ptr);
		*params_ptr += 10;
	}
	UNUSED(iter1);
	SortedListDestroy(new_list);
}
void SortedListMergeTest(void)
{
	sort_list_t *new_list = SortedListCreate(compare_func);
	sort_list_t *new_list2 = SortedListCreate(compare_func);
	sort_list_iter_t target_iter = SortedListBegin(new_list);
	sort_list_iter_t start_iter = SortedListBegin(new_list2);
	sort_list_iter_t end_iter = SortedListBegin(new_list2);
	size_t zero = 0,one = 1, two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8, nine = 9;
	
	target_iter = SortedListInsert(new_list, &zero);
	target_iter = SortedListInsert(new_list, &one);
	target_iter = SortedListInsert(new_list, &two);
	start_iter = SortedListInsert(new_list2, &three);
	start_iter = SortedListInsert(new_list2, &four);
	start_iter = SortedListInsert(new_list2, &five);	
	target_iter = SortedListInsert(new_list, &six);
	target_iter = SortedListInsert(new_list, &seven);
	target_iter = SortedListInsert(new_list, &eight);
	start_iter = SortedListInsert(new_list2, &nine);
	
	
	start_iter = SortedListBegin(new_list2);
	end_iter = SortedListEnd(new_list2);
	
	SortedListMerge(new_list, new_list2);
	TEST("SortListSize()", SortedListSize(new_list2), 0);
	TEST("SortListSize()", SortedListSize(new_list), 10);
	
	UNUSED(target_iter);
	UNUSED(start_iter);
	UNUSED(end_iter);
	SortedListDestroy(new_list);
	SortedListDestroy(new_list2);
}
