#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "tests.h"
#include "priority_queue.h"

static int compare_func(void *data, void *to_compare);
static int match_func(void *to_match, void *data);
static priority_queue_t *CreateTest(queue_compare_t compare_func);
static void DestroyTest(priority_queue_t *queue);
static void EnqueueDeqeueTest(priority_queue_t *queue);
static void ClearTest(priority_queue_t *queue);
static void EraseTest(priority_queue_t *queue);

struct test_struct
{
	int key;
	int age;
	char l;
	float grade;
};

struct test_struct arr[15];

int main()
{
	priority_queue_t *queue = CreateTest(compare_func);
	EnqueueDeqeueTest(queue);
	ClearTest(queue);
	EraseTest(queue);
	
	DestroyTest(queue);
	
	PASS;
	
	return (0);
}

static int compare_func(void *data, void *to_compare)
{
	struct test_struct *comp_struct, *data_struct;
	
	data_struct = data;
	comp_struct = to_compare;
		
	if (data_struct->key > comp_struct->key)
	{
		return (1);
	}
	else if (data_struct->key < comp_struct->key)
	{
		return (-1);
	}
	
	return (0);
}

int match_func(void *to_match, void *data)
{
	int *key = NULL;
	struct test_struct *item;
	item = to_match;
	key = data;
	
	return (*key == item->key);
}

static priority_queue_t *CreateTest(queue_compare_t compare_func)
{
	priority_queue_t *new_queue = PriorityQueueCreate(compare_func);
	
	TEST("QueueIsEmpty()", PriorityQueueIsEmpty(new_queue), 1);
	TEST("QueueSize()", PriorityQueueSize(new_queue), 0);
	
	return (new_queue);
}

static void DestroyTest(priority_queue_t *queue)
{
	PriorityQueueDestroy(queue);
}



static void EnqueueDeqeueTest(priority_queue_t *queue)
{
	int i = 0;
	struct test_struct *test;
	
	for (i = 0; i < 15; ++i)
	{
		arr[i].key = i * 15 + 7;
		arr[i].age = i + 7 * 3;
		arr[i].l = ('a' + i);
		arr[i].grade = (float)arr[i].age + 0.7;
	}
		
	for (i = 0; i < 7; ++i)
	{
		PriorityQueueEnqueue(queue, &arr[i]);
		TEST("QueueSize()", (int)PriorityQueueSize(queue), i + 1);
		TEST("QueueIsEmpty()", PriorityQueueIsEmpty(queue), 0);
	}
	
	for (i = 6; i >= 0; --i)
	{
		test = PriorityQueuePeek(queue);
		PriorityQueueDeqeue(queue);
		TEST("QueueSize()", (int)PriorityQueueSize(queue), i);
		TEST("Peek", test->key, arr[i].key);
		TEST("Peek", test->age, arr[i].age);
		TEST("Peek", test->l, arr[i].l);
		TEST("Peek", test->grade, arr[i].grade);
	}
}



static void ClearTest(priority_queue_t *queue)
{
	size_t i = 0;
	
	for (i = 0; i < 7; ++i)
	{
		PriorityQueueEnqueue(queue, &arr[i]);
		TEST("QueueSize()", PriorityQueueSize(queue), i + 1);
		TEST("QueueIsEmpty()", PriorityQueueIsEmpty(queue), 0);
	}
	PriorityQueueClear(queue);
	TEST("QueueSize()", PriorityQueueSize(queue), 0);
	TEST("QueueIsEmpty()", PriorityQueueIsEmpty(queue), 1);
	
}

static void EraseTest(priority_queue_t *queue)
{
	size_t i = 0;
	int killer = 7, killer2 = 22;
	
	for (i = 0; i < 7; ++i)
	{
		PriorityQueueEnqueue(queue, &arr[i]);
		TEST("QueueSize()", PriorityQueueSize(queue), i + 1);
		TEST("QueueIsEmpty()", PriorityQueueIsEmpty(queue), 0);
	}
	
	PriorityQueueErase(queue, match_func, &killer);
	TEST("QueueSize()", PriorityQueueSize(queue), 6);
	PriorityQueueErase(queue, match_func, &killer2);
	TEST("QueueSize()", PriorityQueueSize(queue), 5);
	
	PriorityQueueClear(queue);
	TEST("QueueSize()", PriorityQueueSize(queue), 0);
	TEST("QueueIsEmpty()", PriorityQueueIsEmpty(queue), 1);
}
