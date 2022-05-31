#ifndef __PRIORITY_QUEUE__
#define __PRIORITY_QUEUE__

#include <stddef.h>
#include "sorted_list.h"

    
typedef struct priority_queue priority_queue_t;
typedef int (*queue_compare_t)(void *data, void *to_compare);/* returns -1 if data lower, 0 if equal, 1 if data higher*/
typedef int (*queue_is_match_t)(void *to_match, void *data);/* returns 1 if match, 0 otherwise*/ 
/*
struct 
{
    priority_queue_t *sort_list;
};
*/

/************************************************************************
*  Description:     Create a Priority queue 
*  Errors:          malloc can return NULL if failed
*  Parameters:      None
*  Return value:    A pointer to the created list, NULL if malloc faild
*  Complexity:      O(1)
************************************************************************/
priority_queue_t *PriorityQueueCreate(queue_compare_t compare_func);

/************************************************************************
*  Description:     Destroy a given Priority queue
*  Errors:          None
*  Parameters:      pointer to the priority queue of type priority_queue_t
*  Return value:    None
*  Complexity:      O(n)
************************************************************************/
void PriorityQueueDestroy(priority_queue_t *queue);

/************************************************************************
*  Description:     get the data of first elem in queue
*  Errors:          None
*  Parameters:      pointer to the priority queue of type priority_queue_t
*  Return value:    pointer to the data of first elem in queue type void*
*  Complexity:      O(1)
************************************************************************/
void *PriorityQueuePeek(const priority_queue_t *queue);

/************************************************************************
*  Description:     calculate the length of the list
*  Errors:          None
*  Parameters:      pointer to the priority queue of type priority_queue_t
*  Return value:    size of the priority queue in size_t
*  Complexity:      O(n)
************************************************************************/
size_t PriorityQueueSize(const priority_queue_t *queue);

/************************************************************************
*  Description:		Check if the priority queue is empty
*  Errors:          None
*  Parameters:      pointer to the priority queue of type priority_queue_t
*  Return value:	Returns 1 if empty, 0 otherwise
*  Complexity:      O(1)
************************************************************************/
int PriorityQueueIsEmpty(const priority_queue_t *queue);

/************************************************************************
*  Description:     insert data to a new node in an orderd place
*  Errors:          malloc can return NULL if failed
*  Parameters:      data to insert to the list
*					pointer to priority queue of type priority_queue_t
*  Return value:    Returns inserted iterator on success, end iterator otherwise
*  Complexity:      O(n)
************************************************************************/
int PriorityQueueEnqueue(priority_queue_t *queue, void *data);

/************************************************************************
*  Description:     remove a highest node
*  Errors:          None
*  Parameters:      pointer to the priority queue node of type sort_list_node_t
*  Return value:    Returns the next iterator
*  Complexity:      O(1)
************************************************************************/
void PriorityQueueDeqeue(priority_queue_t *queue);

/************************************************************************
*  Description:     Clear a given Priority queue
*  Errors:          None
*  Parameters:      pointer to the priority queue of type priority_queue_t
*  Return value:    None
*  Complexity:      O(n)
************************************************************************/
void PriorityQueueClear(priority_queue_t *queue);

/************************************************************************
*  Description:     Erase element with specified data in the queue
*  Errors:          None
*  Parameters:      pointer to the priority queue of type priority_queue_t
*  Return value:    None
*  Complexity:      O(n)
************************************************************************/
void *PriorityQueueErase(priority_queue_t *queue, queue_is_match_t match_func, void *data);

#endif 