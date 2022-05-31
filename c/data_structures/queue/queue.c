/***************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : QUEUE
* REVIEWER NAME : ANTON
*****************************************************/

#include<stdlib.h>
#include<stddef.h>

#include"queue.h"
#include"slist.h"

struct queue
{
    slist_t *queue;
};

/*Creates queue, returns pointer to queue*/
queue_t *QueueCreate()
{
	queue_t *new = malloc(sizeof(queue_t));

	if(NULL == new)
	{
		return NULL;
	}

	new->queue = SlistCreate();

	return new;

}

/*Destroys whole queue, receives pointer to queue_t*/
void QueueDestroy(queue_t *queue)
{
	SlistDestroy(queue->queue);
	free(queue);
}

/*Will get the data from the first element in queue. returns data (void *)*/
void *QueuePeek(const queue_t *queue)
{
	if(NULL == queue->queue)
	{
		return NULL;
	}

	return (SlistGetData(SlistBegin(queue->queue)));
}

/*Adds new element to queue, Malloc may return NULL*/
int Enqueue(queue_t *queue, void *data)
{
	/*slist_node_t *tmp = SlistEnd(queue->queue);*/

	return(1 == (SlistInsert(SlistEnd(queue->queue), data))); 
}

/*Receives queue and removes first */
void Dequeue(queue_t *queue)
{
	/*slist_node_t *tmp = SlistBegin(queue->queue);*/
	SlistRemove(SlistBegin(queue->queue));
}

/*Returns the length of the queue*/
size_t QueueSize(const queue_t *queue)
{
	if(NULL == queue)
	{
		return 0;
	}

	return SlistCount(queue->queue);
}

/*If there are no elements in queue, returns true */
int QueueIsEmpty(const queue_t *queue)
{
	return (0 == QueueSize(queue));
}

/*Appends q2 to the end of q1*/
void QueueAppend(queue_t *q1, queue_t *q2)
{
	SlistAppend(q1->queue, q2->queue);
}