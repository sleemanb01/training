#include <stdio.h>		/* print to */
#include <stddef.h>		/* size_t */ 
#include <assert.h>
#include <string.h>     /* memcm */
#include"slist.h"
#include"tests.h"

void createDestroy();
void insertSetGet();
void beginEnd();
void next();
void insertRemove();
void findCount();
void forEach();
void isEmpty();
void isSameIter();
void flipTest();
void hasLoopTest();
void intersectionTest();

int match_func(void *data, void *to_match);
int action_func(void *data, void *params);

struct slist_node
{
	void *data;
	slist_node_t *next;
};

struct slist
{
	slist_node_t *head;
	slist_node_t *tail;
};

struct node
{
	void *data;
	struct node *next;
};

int main()
{
	createDestroy();
	insertSetGet();
	beginEnd();
	next();
	insertRemove();
	findCount();
	forEach();
	isEmpty();
	isSameIter();
	flipTest();
	hasLoopTest();
	intersectionTest();

	PASS;

	return 0;
}

void createDestroy()
{
	size_t status = 0;
	slist_t *list = SlistCreate();

	status = (NULL != list->head) ? 1 : 0;
	TEST_EQUAL("SlistCreate()", status, 1);

	SlistDestroy(list);
}

void insertSetGet()
{
	slist_t *linked_list = SlistCreate();
	slist_iter_t tmp = NULL;
	int status = 0;
	size_t num = 1234, *num_ptr = &num, num2 = 5678, *num_ptr2 = &num2, *test = NULL;
	
	tmp = SlistBegin(linked_list);
	status = SlistInsert(tmp, num_ptr);
	
	SlistSetData(tmp, num_ptr2);
	assert(0 == status);
	test = (size_t *)SlistGetData(tmp);
	TEST_EQUAL("SlistGetData()", *test, *num_ptr2);
	
	SlistSetData(tmp, num_ptr);
	assert(0 == status);
	test = (size_t *)SlistGetData(tmp);
	TEST_EQUAL("SlistGetData()", *test, *num_ptr);
	
	SlistDestroy(linked_list);

}

void beginEnd()
{
	slist_t *linked_list = SlistCreate();
	slist_iter_t first = SlistBegin(linked_list);
	slist_iter_t last = SlistEnd(linked_list);
	int status = (first == last);
	
	TEST_EQUAL("beginEnd()", status, 1);
	SlistDestroy(linked_list);
}

void next()
{
	slist_t *linked_list = SlistCreate();
	
	slist_iter_t last = NULL, tmp = NULL, test = NULL;
	int status = 0;
	size_t num = 1234, *num_ptr = &num, data = 0, data2 = 0;
	
	tmp = SlistBegin(linked_list);
	status = SlistInsert(tmp, num_ptr);
	TEST_EQUAL("SlistInsert()", status, 0);
	last = SlistEnd(linked_list);
	tmp = SlistBegin(linked_list);
	test = SlistNext(tmp);
	
	data = *(size_t*)SlistGetData(test);
	data2 = *(size_t*)SlistGetData(last);
	
	TEST_EQUAL("SlistNext()", data, data2);
	
	SlistDestroy(linked_list);
}

int is_match(void *data, void *to_match)
{
	size_t size = sizeof(*(size_t *)data);
	int result = memcmp(data, to_match, size);
	return (result == 0);
}

void insertRemove()
{
	slist_t *linked_list = SlistCreate();
	slist_iter_t tmp = NULL, first = NULL, last = NULL;
	int status = 0;
	size_t num = 1234, *num_ptr = &num;
	
	tmp = SlistBegin(linked_list);
	status = SlistInsert(tmp, num_ptr);
	status = SlistInsert(tmp, num_ptr);
	status = SlistInsert(tmp, num_ptr);
	
	tmp = SlistBegin(linked_list);
	SlistRemove(tmp);
	tmp = SlistBegin(linked_list);
	SlistRemove(tmp);
	tmp = SlistBegin(linked_list);
	SlistRemove(tmp);
	
	first = SlistBegin(linked_list);
	last = SlistEnd(linked_list);
	status = (first == last);
	TEST_EQUAL("SlistInsertRemove()", status, 1);
	
	SlistDestroy(linked_list);
}

void findCount()
{
	slist_t *linked_list = SlistCreate();
	slist_iter_t tmp = NULL, first = NULL, last = NULL;
	int status = 0;
	size_t num = 1, num2 = 2, num3 = 3, num4 = 4,  num5 = 5, num6 = 6, test = 0, actual = 6;
	size_t *num_ptr = &num, *num_ptr2 = &num2, *num_ptr3 = &num3, *num_ptr4 = &num4, *num_ptr5 = &num5, *num_ptr6 = &num6;
	
	first = SlistBegin(linked_list);
	status = SlistInsert(first, num_ptr);
	tmp = SlistNext(first);
	status = SlistInsert(tmp, num_ptr2);
	tmp = SlistNext(tmp);
	status = SlistInsert(tmp, num_ptr3);
	tmp = SlistNext(tmp);
	status = SlistInsert(tmp, num_ptr4);
	tmp = SlistNext(tmp);
	status = SlistInsert(tmp, num_ptr5);
	tmp = SlistNext(tmp);
	status = SlistInsert(tmp, num_ptr6);
	tmp = SlistNext(tmp);
	
	
	first = SlistBegin(linked_list);
	last = SlistEnd(linked_list);
	
	
	assert(0 == status);
	test = SlistCount(linked_list);
	TEST_EQUAL("SlistCount()", actual, test);

	tmp = SlistFind(first, last, num_ptr6, is_match);
	test = *(size_t *)SlistGetData(tmp);
	actual = *num_ptr6;
	
	TEST_EQUAL("SlistFind()", test, actual);
	
	SlistDestroy(linked_list);
}

int AddOne(void *data, void *params)
{
	size_t *tmp = (size_t *)data, param = *(size_t *)params;
	*tmp += param;
	return (0);	
}
void forEach()
{
	slist_t *linked_list = SlistCreate();
	slist_iter_t tmp = NULL, first = NULL, last = NULL;
	int status = 0;
	size_t num = 1, num2 = 2, num3 = 3, num4 = 4,  num5 = 5, num6 = 6, test = 0, actual = 6, i = 0, n = 2, param = 1;
	size_t *num_ptr = &num, *num_ptr2 = &num2, *num_ptr3 = &num3, *num_ptr4 = &num4, *num_ptr5 = &num5, *num_ptr6 = &num6, *param_ptr = &param;
	
	first = SlistBegin(linked_list);
	status = SlistInsert(first, num_ptr);
	tmp = SlistNext(first);
	status = SlistInsert(tmp, num_ptr2);
	tmp = SlistNext(tmp);
	status = SlistInsert(tmp, num_ptr3);
	tmp = SlistNext(tmp);
	status = SlistInsert(tmp, num_ptr4);
	tmp = SlistNext(tmp);
	status = SlistInsert(tmp, num_ptr5);
	tmp = SlistNext(tmp);
	status = SlistInsert(tmp, num_ptr6);
	tmp = SlistNext(tmp);
	
	assert(status == 0);
	
	first = SlistBegin(linked_list);
	last = SlistEnd(linked_list);
	
	tmp = SlistForEach(first, last, AddOne, param_ptr);
	tmp = SlistBegin(linked_list);
	
	for (i = 0; i < actual; ++i)
	{
		test = *(size_t *)SlistGetData(tmp);
		TEST_EQUAL("SlistCount()", n, test);
		n +=1;
		tmp = SlistNext(tmp);
	}
	
	SlistDestroy(linked_list);
}
void isEmpty()
{
	slist_t *linked_list = SlistCreate();
	slist_iter_t tmp = NULL, first = NULL, last = NULL;
	int status = 0;
	size_t num = 1234, *num_ptr = &num;
	
	first = SlistBegin(linked_list);
	last = SlistEnd(linked_list);
	status = (first == last);
	TEST_EQUAL("SlistIsEmpty()", status, 1);
	
	tmp = SlistBegin(linked_list);
	status = SlistInsert(tmp, num_ptr);
	status = SlistInsert(tmp, num_ptr);
	status = SlistInsert(tmp, num_ptr);
	
	tmp = SlistBegin(linked_list);
	SlistRemove(tmp);
	tmp = SlistBegin(linked_list);
	SlistRemove(tmp);
	tmp = SlistBegin(linked_list);
	SlistRemove(tmp);
	
	first = SlistBegin(linked_list);
	last = SlistEnd(linked_list);
	status = (first == last);
	
	TEST_EQUAL("SlistIsEmpty()", status, 1);
	
	SlistDestroy(linked_list);
}
void isSameIter()
{
	slist_t *linked_list = SlistCreate();
	slist_iter_t tmp = NULL, first = NULL, last = NULL;
	size_t num = 1234, *num_ptr = &num;
	int status = 0;
	
	first = SlistBegin(linked_list);
	last = SlistEnd(linked_list);
	status = SlistIsSameIter(first, last);
	TEST_EQUAL("SlistIsEmpty()", status, 0);
	
	tmp = SlistBegin(linked_list);
	status = SlistInsert(tmp, num_ptr);
	status = SlistIsSameIter(tmp, last);
	
	SlistDestroy(linked_list);
}

/* Reverse the order of given slist */ 
void flipTest()
{
	/*int result = 0;
	slist_t *linked_list = SlistCreate();
	node_t *head = (node_t*)SlistBegin(linked_list);

	head = Flip(head);

	result = ((node_t*)(linked_list->tail) == head);

	TEST("Flip()", result, 1);

	SlistDestroy(linked_list);*/

}

void hasLoopTest()
{

}

void intersectionTest()
{

}

