/***************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : PQ
* REVIEWER NAME : IDAN
*****************************************************/

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

#include "priority_queue.h"

struct priority_queue 
{
    sort_list_t *priority_queue;
};

/************************************************************************
*  Description:     Create a Priority queue 
*  Errors:          malloc can return NULL if failed
*  Parameters:      None
*  Return value:    A pointer to the created list, NULL if malloc faild
*  Complexity:      O(1)
************************************************************************/
priority_queue_t *PriorityQueueCreate(queue_compare_t compare_func)
{
	priority_queue_t *new = NULL;

	do
	{

		new = (priority_queue_t*)malloc(sizeof(priority_queue_t));

		if(NULL == new)
		{
			break;
		}

		new->priority_queue = SortedListCreate(compare_func);

		if(NULL == new->priority_queue)
		{
			break;
		}

		return new;

	}while(0);

	free(new);

	return NULL;

}

/************************************************************************
*  Description:     Destroy a given Priority queue
*  Errors:          None
*  Parameters:      pointer to the priority queue of type priority_queue_t
*  Return value:    None
*  Complexity:      O(n)
************************************************************************/
void PriorityQueueDestroy(priority_queue_t *queue)
{
	assert(NULL != queue);

	SortedListDestroy(queue->priority_queue);

	free(queue);
}

/************************************************************************
*  Description:     get the data of first elem in queue
*  Errors:          None
*  Parameters:      pointer to the priority queue of type priority_queue_t
*  Return value:    pointer to the data of first elem in queue type void*
*  Complexity:      O(1)
************************************************************************/
void *PriorityQueuePeek(const priority_queue_t *queue)
{
	assert(NULL != queue);

	return (SortedListGetData(SortedListBegin(queue->priority_queue)));
}

/************************************************************************
*  Description:     calculate the length of the list
*  Errors:          None
*  Parameters:      pointer to the priority queue of type priority_queue_t
*  Return value:    size of the priority queue in size_t
*  Complexity:      O(n)
************************************************************************/
size_t PriorityQueueSize(const priority_queue_t *queue)
{
	assert(NULL != queue);

	return (SortedListSize(queue->priority_queue));
}

/************************************************************************
*  Description:		Check if the priority queue is empty
*  Errors:          None
*  Parameters:      pointer to the priority queue of type priority_queue_t
*  Return value:	Returns 1 if empty, 0 otherwise
*  Complexity:      O(1)
************************************************************************/
int PriorityQueueIsEmpty(const priority_queue_t *queue)
{
	assert(NULL != queue);

	return (SortedListIsEmpty(queue->priority_queue));
}

/************************************************************************
*  Description:     insert data to a new node in an orderd place
*  Errors:          malloc can return NULL if failed
*  Parameters:      data to insert to the list
*					pointer to priority queue of type priority_queue_t
*  Return value:    Returns inserted iterator on success, end iterator otherwise
*  Complexity:      O(n)
************************************************************************/
int PriorityQueueEnqueue(priority_queue_t *queue, void *data)
{
	size_t size = 0;

	assert(NULL != queue);

	size = PriorityQueueSize(queue);
	SortedListInsert(queue->priority_queue, data);

	return (PriorityQueueSize(queue) > size) ? 0 : 1 ;

}

/************************************************************************
*  Description:     remove a highest node
*  Errors:          None
*  Parameters:      pointer to the priority queue node of type sort_list_node_t
*  Return value:    Returns the next iterator
*  Complexity:      O(1)
************************************************************************/
void PriorityQueueDeqeue(priority_queue_t *queue)
{
	assert(NULL != queue);
	SortedListPopFront(queue->priority_queue);
}

/************************************************************************
*  Description:     Clear a given Priority queue
*  Errors:          None
*  Parameters:      pointer to the priority queue of type priority_queue_t
*  Return value:    None
*  Complexity:      O(n)
************************************************************************/
void PriorityQueueClear(priority_queue_t *queue)
{
	assert(NULL != queue);
	while (!PriorityQueueIsEmpty(queue))
	{
		PriorityQueueDeqeue(queue);
	}
}

/************************************************************************
*  Description:     Erase element with specified data in the queue
*  Errors:          None
*  Parameters:      pointer to the priority queue of type priority_queue_t
*  Return value:    None
*  Complexity:      O(n)
************************************************************************/
void *PriorityQueueErase(priority_queue_t *queue, queue_is_match_t match_func, void *data)
{
	void *ret = NULL;
	sort_list_iter_t target;
	assert(NULL != queue);

	target = SortedListFindIf(SortedListBegin(queue->priority_queue), SortedListEnd(queue->priority_queue), match_func, data);
	ret = SortedListGetData(target);
	SortedListRemove(target);
	return ret;
}