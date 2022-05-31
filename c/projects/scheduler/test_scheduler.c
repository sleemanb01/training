#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "tests.h"
#include "uid.h"
#include "scheduler.h"
#include "priority_queue.h"

int task_func(void *params);
int stop_func(void *params);
sched_t *CreateTest(void);
void DestroyTest(sched_t *sched);
void AddTest(sched_t *sched);
void RemoveTest(sched_t *sched);
void ClearTest(sched_t *sched);
int RunTest(sched_t *sched);
void StopTest(sched_t *sched);

int main()
{
	sched_t *new_sched = CreateTest();
	StopTest(new_sched);
	ClearTest(new_sched);
	RemoveTest(new_sched);
	DestroyTest(new_sched);

	PASS;
	return (0);
}
int task_func(void *params)
{
	static int counter = 0;
	if (25 <= counter)
	{
		return (0);
	}
	printf("\n%lu\n", *(size_t *)params);
	
	*(size_t *)params += (size_t)counter;
	
	++counter;
	return (1);

}

int stop_func(void *params)
{
	sched_t *sched = NULL;
	sched = (sched_t *)params;
	SchedStop(sched);
	return (0);
}


sched_t *CreateTest()
{
	sched_t *new_sched = SchedCreate();
	TEST("SchedCreate()", SchedSize(new_sched), 0);
	TEST("SchedCreate()", SchedIsEmpty(new_sched), 1);
	return (new_sched);
}

void DestroyTest(sched_t *sched)
{
	SchedDestroy(sched);
}

void RemoveTest(sched_t *sched)
{
	unsigned int interval = 1, param = 1, *param_ptr = &param, counter = 5, i = 0, j = 0;
	ilrd_uid_t *arr = malloc(sizeof(ilrd_uid_t) * 5);
	for (i = 0; i < counter; ++i, ++interval)
	{
		arr[i] = SchedAdd(sched, task_func, param_ptr, interval);
		TEST("SchedAdd()", (unsigned int)SchedSize(sched), (i + 1));
		TEST("SchedAdd()", SchedIsEmpty(sched), 0);
	}
	
	j = (counter - 1);
	for (i = 0; i < counter; ++i, --j)
	{
		SchedRemove(sched, arr[i]);
		TEST("SchedRemove()", (unsigned int)SchedSize(sched), j);
	}
	TEST("SchedRemove()", (unsigned int)SchedSize(sched), 0);
	TEST("SchedRemove()", SchedIsEmpty(sched), 1);
	free(arr);
}

void ClearTest(sched_t *sched)
{
	SchedClear(sched);
	TEST("SchedClear()", SchedSize(sched), 0);
	TEST("SchedClear()", SchedIsEmpty(sched), 1);
}


void StopTest(sched_t *sched)
{
	size_t interval = 1, counter = 5, i = 0, param = 1, result = 0;
	for (i = 0; i < counter; ++i, ++interval)
	{	
		SchedAdd(sched, task_func, &param, interval);
		TEST("SchedAdd()", SchedSize(sched), (i + 1));
		TEST("SchedAdd()", SchedIsEmpty(sched), 0);
	}
	SchedAdd(sched, stop_func, sched, 10);
	result = SchedRun(sched);
	/*TEST_NE("SchedStop()", SchedSize(sched), 0);*/
	TEST("SchedStop()", result, 0);
}
