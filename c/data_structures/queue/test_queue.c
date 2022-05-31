#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

#include"tests.h"
#include"queue.h"


void CreateDestroyQueueTest();
void PeekQueueTest();
void EnqueueDequeueTest();
void SizeQueueTest();
void IsEmptyQueueTest();
void AppendQueueTest();

int main()
{
	CreateDestroyQueueTest();
	PeekQueueTest();
	EnqueueDequeueTest();
	SizeQueueTest();
	IsEmptyQueueTest();
	AppendQueueTest();

	PASS;
	return (0);
}

void CreateDestroyQueueTest()
{
	queue_t *new_queue = QueueCreate();
	QueueDestroy(new_queue);
}
void PeekQueueTest()
{
	queue_t *new_queue = QueueCreate();
	size_t data = 123, *data_ptr = &data, tmp = 0, *tmp_ptr = &tmp;
	int status = 0;
	
	status = Enqueue(new_queue, data_ptr);
	assert(0 == status);
	*tmp_ptr = *(size_t *)QueuePeek(new_queue);
	TEST("QueuePeek()", tmp, data);
	QueueDestroy(new_queue);
}
void EnqueueDequeueTest()
{
	queue_t *new_queue = QueueCreate();
	size_t data = 123, *data_ptr = &data, tmp = 0, *tmp_ptr = &tmp;
	int status = 0;
	status = Enqueue(new_queue, data_ptr);
	assert(0 == status);
	*tmp_ptr = *(size_t *)QueuePeek(new_queue);
	TEST("QueuePeek()", tmp, data);
	Dequeue(new_queue);
	*tmp_ptr = *(size_t *)QueuePeek(new_queue);
	status = (tmp == data);
	TEST("QueueEnqueueDequeue()", status, 0);
	QueueDestroy(new_queue);
}
void SizeQueueTest()
{
	queue_t *new_queue = QueueCreate();
	size_t data = 123, *data_ptr = &data, max = 5, i = 0;
	int status = 0;
	for (i = 0; i < max; ++i)
	{
		status = Enqueue(new_queue, data_ptr);
	}
	assert(0 == status);
	
	i = QueueSize(new_queue);
	TEST("QueueSize()", i, max);
	
	for (i = 0; i < max; ++i)
	{
		Dequeue(new_queue);
	}
	assert(0 == status);
	
	i = QueueSize(new_queue);
	TEST("QueueSize()", i, 0);
	
	QueueDestroy(new_queue);
}
void IsEmptyQueueTest()
{
	queue_t *new_queue = QueueCreate();
	size_t data = 123, *data_ptr = &data, max = 5, i = 0;
	int status = 0;
	for (i = 0; i < max; ++i)
	{
		status = Enqueue(new_queue, data_ptr);
	}
	assert(0 == status);
	
	i = QueueIsEmpty(new_queue);
	TEST("QueueIsEmpty()", i, 0);
	
	for (i = 0; i < max; ++i)
	{
		Dequeue(new_queue);
	}
	assert(0 == status);
	
	i = QueueIsEmpty(new_queue);
	TEST("QueueIsEmpty()", i, 1);
	
	QueueDestroy(new_queue);
}

void AppendQueueTest()
{
	/*queue_t *new_queue = QueueCreate();
	queue_t *new_queue2 = QueueCreate();
	size_t data = 123, *data_ptr = &data, max = 5, i = 0;
	int status = 0;
	for (i = 0; i < max; ++i)
	{
		status = Enqueue(new_queue, data_ptr);
		status = Enqueue(new_queue2, data_ptr);
	}
	assert(0 == status);
	
	i = QueueSize(new_queue);
	TEST("QueueSize()", i, max);
	i = QueueSize(new_queue2);
	TEST("QueueSize()", i, max);
	
	QueueAppend(new_queue, new_queue2);
	
	i = QueueSize(new_queue);
	TEST("QueueSize()", i, (max*2));
	
	QueueDestroy(new_queue2);
	QueueDestroy(new_queue);*/
}

