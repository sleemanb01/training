/***************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : SCHEDULER
* REVIEWER NAME : IDAN
*****************************************************/

#include <stddef.h> /* for size_t */
#include <time.h>   /* for time_t */
#include <assert.h> /* for assert */
#include <stdlib.h> /* for malloc */
#include <unistd.h> /* for sleep */

#include"scheduler.h"

/************************************** STRUCTS **************************************/

extern const ilrd_uid_t g_BadUID;

struct sched_task
{
    ilrd_uid_t uid;
    int (*task_func)(void* data);
    void *params;
    unsigned int interval_in_sec;

    time_t execution_time;
};

struct scheduler
{
    unsigned int flag;
    priority_queue_t *scheduler;
};



/************************************** ADDITIONAL FUNCS **************************************/
static int compare_func(void *data, void *to_compare)
{

  sched_task_t *data_struct, *to_compare_struct;

  assert(NULL != data);
  assert(NULL != to_compare);

  data_struct = data;       
  to_compare_struct = to_compare;

  if(data_struct->execution_time < to_compare_struct->execution_time)
  {
    return 1;
  }
  else if(data_struct->execution_time > to_compare_struct->execution_time)
  {
    return -1;
  }

  return 0;
}

static int match_func(void *data, void *to_match)
{
  int res = 0;

  assert(NULL != data);
  assert(NULL != to_match);

  res = UIDIsEqual(*(ilrd_uid_t *)data, *(ilrd_uid_t *)to_match);

  return res;
}

/************************************** CREATE **************************************/
sched_t *SchedCreate()
{
  sched_t *new = NULL;

  do
  {

    new = (sched_t*)malloc(sizeof(sched_t));
    if(NULL == new)
    {
      break;
    }

    new->scheduler = PriorityQueueCreate(compare_func);

    if(NULL == new->scheduler)
    {
      break;
    }

    new->flag = 0;

    return new;

  }while(0);

  free(new);

  return NULL;

}

/************************************** DESTROY **************************************/
void SchedDestroy(sched_t *sched)
{
  assert(NULL != sched);
  SchedClear(sched);
  PriorityQueueDestroy(sched->scheduler);
  free(sched);
}

/************************************** ADD **************************************/
ilrd_uid_t SchedAdd(sched_t *sched, task_t task_func, void *param, unsigned int interval_in_sec)
{
  sched_task_t *new = NULL;

  do
  {
    new = (sched_task_t*)malloc(sizeof(sched_task_t));

    if(NULL == new)
    {
      break;
    }

    new->uid = UIDGenerate();

    if (UIDIsEqual(new->uid, g_BadUID))
    {
      break;
    }
    
    time(&new->execution_time);

    if (0 > new->execution_time)
    {
      break;
    }

    new->task_func = task_func;
    new->params = param;
    new->interval_in_sec = interval_in_sec;
    new->execution_time += new->interval_in_sec;

    PriorityQueueEnqueue(sched->scheduler, new);

    return new->uid;

  }while(0);

  free(new);

  return g_BadUID;

}

/************************************** REMOVE **************************************/
void SchedRemove(sched_t *sched, ilrd_uid_t task_id)
{
  assert(NULL != sched);

  free(PriorityQueueErase(sched->scheduler,match_func,&task_id));
}

/************************************** RUN **************************************/
int SchedRun(sched_t *sched)
{
  time_t now = 0;
  sched_task_t *task = NULL;

  assert(NULL != sched);

  sched->flag = 0;

  while (!SchedIsEmpty(sched) && (1 != sched->flag))
  {
    time(&now);

    if(0 > now)
    {
      return 1;
    }

    task = PriorityQueuePeek(sched->scheduler);

    if(0 < (task->execution_time - now))
    {
      sleep(task->execution_time - now);
    }

    PriorityQueueDeqeue(sched->scheduler);

    if(task->task_func(task->params))
    {
      task->execution_time += task->interval_in_sec;
      if(PriorityQueueEnqueue(sched->scheduler, task))
      {
        return 1;
      }
    }
    else
    {
      free(task);
    }
  }

  return 0;

}

/************************************** STOP **************************************/
void SchedStop(sched_t *sched)
{
  assert(NULL != sched);

  sched->flag = 1;
}

/************************************** SIZE **************************************/
size_t SchedSize(sched_t *sched)
{
  assert(NULL != sched);
  return (PriorityQueueSize(sched->scheduler));
}

/************************************** ISEMPTY **************************************/
int SchedIsEmpty(sched_t *sched)
{
   assert(NULL != sched);

   return (PriorityQueueIsEmpty(sched->scheduler));
}

/************************************** CLEAR **************************************/
void SchedClear(sched_t *sched)
{
  sched_task_t *data = NULL;
 
  assert(NULL != sched);

  while (!SchedIsEmpty(sched))
  {
    data = PriorityQueuePeek(sched->scheduler);
    PriorityQueueDeqeue(sched->scheduler);
    free(data);
  }

}