#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "priority_queue.h"
#include "uid.h"

typedef struct scheduler sched_t;
typedef struct sched_task sched_task_t;
typedef int (*task_t)(void *param);/* returns 1 if repeat, 0 otherwise*/ 



/*
*  Description:     SchedCreate- allocates memory and initializes the scheduler 
*  Errors:          malloc can return NULL if failed
*  Parameters:      
*  Return value:    Returns pointer to sched_t on success, NULL otherwise 
  Complexity:      O(1)
*/
sched_t *SchedCreate();
/*
*  Description:     SchedDestroy- removes all elements from scheduler and frees allocated memory
*  Errors:          
*  Parameters:      pointer to scheduler
*  Return value:     
  Complexity:      O(1)
*/
void SchedDestroy(sched_t *sched);
/*
*  Description:    SchedAdd - adds a task "task_func" to scheduler with the given "param", to be repeated every "interval_in_sec" seconds
*  Errors:         memory allocation may fail/ uid generation may fail. 
*  Parameters:     pointer to scheduler, task_func- function to be executed, param -to be sent to task_func, interval_in_sec- interval of executionk
*  Return value:   uid_ilrd - BadUID for failure, other uid for success
  Complexity:      O(1)
*/
ilrd_uid_t SchedAdd(sched_t *sched, task_t task_func, void *param, unsigned int interval_in_sec);
/*
*  Description:     SchedRemove- removes element with given uid from scheduler
*  Errors:          
*  Parameters:      pointer to scheduler, task_id to be removed
*  Return value:     
  Complexity:      O(1)
*/
void SchedRemove(sched_t *sched, ilrd_uid_t task_id);
/*
*  Description:     SchedRun- runs the scheduler
*  Errors:          
*  Parameters:      pointer to scheduler
*  Return value:     
  Complexity:      O(1)
*/
int SchedRun(sched_t *sched);
/*
*  Description:     SchedStop- stops the scheduler without removing tasks 
*  Errors:          
*  Parameters:      pointer to scheduler
*  Return value:     
  Complexity:      O(1)
*/
void SchedStop(sched_t *sched);
/*
*  Description:     SchedSize- returns the number of pending tasks 
*  Errors:          
*  Parameters:      pointer to scheduler
*  Return value:    size_t number of pending tasks.
  Complexity:      O(1)
*/
size_t SchedSize(sched_t *sched);
/*
*  Description:     SchedIsEmpty- checks if the scheduler is empty  
*  Errors:          
*  Parameters:     pointer to scheduler
*  Return value:   0 if there are pending tasks, 1 otherwise
  Complexity:      O(1)
*/
int SchedIsEmpty(sched_t *sched);
/*
*  Description:     SchedClear- stops the scheduler and removes all pendong tasks.
*  Errors:          
*  Parameters:      pointer to scheduler
*  Return value:     
  Complexity:      O(1)
*/
void SchedClear(sched_t *sched);

#endif