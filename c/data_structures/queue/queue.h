#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h>/*size_t*/

typedef struct queue queue_t;


/*Creates queue, returns pointer to queue*/
queue_t *QueueCreate(); /*O(1)*/

/*Destroys whole queue, receives pointer to queue_t*/
void QueueDestroy(queue_t *queue);/*O(n)*/

/*Will get the data from the first element in queue. returns data (void *)*/
void *QueuePeek(const queue_t *queue);/*O(1)*/

/*Adds new element to queue, Malloc may return NULL*/
int Enqueue(queue_t *queue, void *data);/*O(1)*/

/*Receives queue and removes first */
void Dequeue(queue_t *queue);/*O(1)*/

/*Returns the length of the queue*/
size_t QueueSize(const queue_t *queue);/*O(n)*/

/*If there are no elements in queue, returns true */
int QueueIsEmpty(const queue_t *queue);/*O(1)*/

/*Appends q2 to the end of q1*/
void QueueAppend(queue_t *q1, queue_t *q2);/*O(1)*/

#endif
