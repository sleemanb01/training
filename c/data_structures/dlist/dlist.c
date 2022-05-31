/***************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : DLIST
* REVIEWER NAME : ANDREY
*****************************************************/

#include<stdlib.h>           /* malloc */
#include <assert.h>

#include"dlist.h"

struct dlist_node
{
    void *data;
    dlist_node_t *next;
    dlist_node_t *prev;
};

struct dlist
{
    dlist_node_t head;
    dlist_node_t tail;
};

dlist_t *DlistCreate()
{
	dlist_t *list;
	list = (dlist_t*) malloc(sizeof(dlist_t));

	if(NULL == list)
	{
		return NULL;
	}

	list->head.next =  &list->tail;
	list->head.prev = NULL;
	list->head.data = NULL;

	list->tail.prev = &list->head;
	list->tail.next = NULL;
	list->tail.data = NULL;

	return list;
}

void DlistDestroy(dlist_t *list)
{
	dlist_node_t *tmp;
	dlist_node_t *next;

	tmp = DlistBegin(list);
	next = tmp->next;

	while(NULL != next)
	{
		free(tmp);
		tmp = next;
		next = DlistNext(tmp);
	}
	free(list);
}

dlist_iter_t DlistBegin(const dlist_t *list)
{
	assert(NULL != list);
	return list->head.next;
}

dlist_iter_t DlistEnd(const dlist_t *list)
{
	assert(NULL != list);
	return list->tail.prev->next;
}

dlist_iter_t DlistNext(const dlist_iter_t iter)
{
	assert(NULL != iter);
	return iter->next;
}

dlist_iter_t DlistPrev(const dlist_iter_t iter)
{
	assert(NULL != iter);
	return iter->prev;
}

void *DlistGetData(const dlist_iter_t iter)
{
	assert(NULL != iter);
	return iter->data;
}

void DlistSetData(dlist_iter_t iter, void *data)
{
	assert(NULL != iter);
	iter->data = data;
}

int DlistInsert(dlist_iter_t where, void *data)
{
	dlist_iter_t new = NULL;

	assert(NULL != where);

	new = malloc(sizeof(dlist_node_t));
	
	if(NULL == new)
	{
		return 1;
	}

	new->next = where;
	new->prev = where->prev;

	DlistSetData(new,data);

	where->prev->next = new;
	where->prev = new;

	return 0;
}

/*Receives pointer to node and pointer to list*/
void DlistRemove(dlist_iter_t iter)
{
	dlist_iter_t next = NULL;
	dlist_iter_t prev = NULL;

	assert(NULL != iter);
	
	if (NULL == iter->next || NULL == iter->prev)
	{
		return;
	}

	next = DlistNext(iter);
	prev = DlistPrev(iter);
	
	next->prev = prev;
	prev->next = next;
	
	free(iter);


}

/*push new node with data, to the back of dlist*/
int DlistPushBack(dlist_t *dlist, void *data)
{
	dlist_iter_t tail;

	assert(NULL != dlist);

	tail = DlistEnd(dlist);

	return (DlistInsert(tail,data));
}

/*pop node off the back */
void *DlistPopBack(dlist_t *dlist)
{
	dlist_iter_t tail;
	void *data;

	assert(NULL != dlist);

	tail = DlistPrev(DlistEnd(dlist));
	data = tail->data;

	DlistRemove(tail);

	return data;
}

/*push new node with data, to the front of dlist*/
int DlistPushFront(dlist_t *dlist, void *data)
{
	dlist_iter_t head;

	assert(NULL != dlist);

	head = DlistBegin(dlist);

	return (DlistInsert(head,data));
}

/*pop node off the front */
void *DlistPopFront(dlist_t *dlist)
{
	dlist_iter_t head;
	void *data;

	assert(NULL != dlist);

	head = DlistBegin(dlist);
	data = head->data;

	DlistRemove(head);

	return data;
}

/*Returns the length of the list*/
size_t DlistSize(const dlist_t *dlist)
{
	dlist_node_t *tmp;
	size_t i = 0;

	tmp = DlistBegin(dlist);

	for(i = 0; !DlistIsSameIter(tmp,DlistEnd(dlist)) ; ++i, tmp = DlistNext(tmp))
	{/*NOTHING*/} 

	return i;
}

/*Returns pointer to found data, else return to */
dlist_iter_t DlistFind(const dlist_iter_t from, const dlist_iter_t to, 
	const void *data, int (*match_func)(const void *data, const void *to_match))
{
	dlist_node_t *tmp;

	assert(NULL != from);
	assert(NULL != to);

	tmp = from;

	while(!DlistIsSameIter(to,tmp) && (!match_func(data,tmp->data)))
	{
		tmp = DlistNext(tmp);
	}

	return tmp;
}

/*Do action to nodes in range from to */
dlist_iter_t DlistForEach(dlist_iter_t from, dlist_iter_t to, 
    int (*action_func)(void *data, void *params), void *params)
{
	dlist_node_t *tmp;

	assert(NULL != from);
	assert(NULL != to);

	tmp = from;

	while(!DlistIsSameIter(to,tmp))
	{
		if(action_func(tmp->data, params))
		{
			break;
		}
		tmp = DlistNext(tmp);
	}

	return tmp;
}

/*If list is empty, return 1, or 0 otherwise */
int DlistIsEmpty(const dlist_t *dlist)
{
	return DlistIsSameIter(DlistBegin(dlist), DlistEnd(dlist));
}

/*Compare two nodes and returns 1 if equal*/
int DlistIsSameIter(const dlist_iter_t iter1, const dlist_iter_t iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);
	return (iter1 == iter2);
}

/*insert one list to another */
void DlistSplice(dlist_iter_t target, dlist_iter_t from, dlist_iter_t to)
{
	dlist_iter_t to_prev = to->prev;
	
	assert(NULL != target);
	assert(NULL != from);
	assert(NULL != to);
	
	from->prev->next = to;	
	to->prev = from->prev;
	
	from->prev = target->prev;
	target->prev->next = from;
	
	to_prev->next = target;	
	target->prev = to_prev;
}

/*Returns 1 if malloc failed to list of found data, else return to 
*                                                     */
int DlistMultiFind(const dlist_iter_t from, const dlist_iter_t to, 
	const void *data, int (*match_func)(const void *data, const void *to_match), dlist_t *target_list)
{
	dlist_iter_t iter = from;
	
	assert(NULL != from);
	assert(NULL != to);	
	assert(NULL != target_list);
	
	while(!DlistIsSameIter(to,iter))
	{
		if(match_func(iter->data,data))
		{
			if (DlistPushBack(target_list, DlistGetData(iter)))
			{
				return 1;
			}
		}
		iter = DlistNext(iter);
	}
	return 0;
}
