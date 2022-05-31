/***************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : SLIST
* REVIEWER NAME : ANTON
*****************************************************/

#include<stdio.h>	         /* printf */
#include<stdlib.h>           /* malloc */
#include <assert.h>

#include"slist.h"

struct slist_node
{
	void *data;
	slist_node_t *next;
};

struct slist
{
	slist_node_t *head;
	slist_node_t *tail;
};

struct node
{
	void *data;
	struct node *next;
};

/*Creates slist, returns pointer to slist*/
slist_t *SlistCreate()
{
	slist_t *list; 
	slist_node_t *dummy_node;

	list = (slist_t*) malloc(sizeof(slist_t));

	if(NULL == list)
	{
		return NULL;
	}

	dummy_node = (slist_node_t*) malloc(sizeof(slist_node_t));

	if(NULL == dummy_node)
	{
		free(list);
		return NULL;
	}

	list->head = dummy_node;
	list->tail = dummy_node;

	dummy_node->data = list; 
	dummy_node->next = NULL;


	return list;
}

/*Destroys whole linked list, receives pointer to slist_t*/
void SlistDestroy(slist_t *list)
{
	slist_node_t *tmp = list->head;
	slist_node_t *next;
	while(NULL != tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(list);
}

/*will return the first valid node. Receives pointer to head, returns head*/
slist_iter_t SlistBegin(const slist_t *list)
{
	return list->head;
}

/*Receives head, returns tail*/
slist_iter_t SlistEnd(const slist_t *list)
{
	return list->tail;
}

/*Receives pointer to node, returns pointer to next node*/
slist_iter_t SlistNext(const slist_iter_t iter)
{
	return iter->next;
}

/*Will get the data from the node. returns data (void *)*/
void *SlistGetData(const slist_iter_t iter)
{
	return (void*)(iter->data);
}

/*Sets data in node*/
void SlistSetData(slist_iter_t iter, void *data)
{
	iter->data = data;
}

/*Malloc may return NULL*/
int SlistInsert(slist_iter_t iter, void *data)
{
	slist_node_t *node = (slist_node_t*) malloc(sizeof(slist_node_t));
	slist_t *tmp = NULL;

	if(NULL == node)
	{
		return 1;	
	}

	if (NULL == iter->next)             /* IN CASE OF ITER  = TAIL */
	{                                   /* tmp is a list that has a head and tail */
		tmp = (slist_t *)iter->data;    /* tmp gets the tail data which is pointer to the list*/ 
		tmp->tail = node;               /* points to the new node */
	}                                   /* now the tail has two nodes*/

	node->data = iter->data;           /* node will become the tail */
	node->next = iter->next;
	iter->data = data;                 /* the old tail will get the data and pointer to new tail (node)*/
	iter->next = node;                 
	
	return 0;

}

/*Receives pointer to node and pointer to list*/
void SlistRemove(slist_iter_t iter)
{

	slist_node_t *tmp = iter->next;
	slist_t *tail = NULL;
	
	if (NULL == tmp->next)
	{
		tail = (slist_t *)tmp->data;
		tail->tail = iter;
	}
	iter->data = tmp->data;
	iter->next = tmp->next;
	free(tmp);

}

/*Returns the length of the list*/
size_t SlistCount(const slist_t *slist)
{
	size_t counter = 0;
	slist_node_t *tmp = slist->head->next;

	assert(NULL != slist);
	
	while(NULL != tmp)
	{
		++counter;
		tmp = tmp->next;
	}

	return counter;
}

/*Returns pointer to found data, else return to */
slist_iter_t SlistFind(const slist_iter_t from, const slist_iter_t to, 
	void *data, is_match_t match_func)
{
	slist_node_t *tmp = from;

	while(tmp != to)
	{
		if(match_func(tmp->data, data))
		{
			return tmp;
		}
		tmp = SlistNext(tmp);
	}

	return from;
}

/*Do action to nodes in range from to */
slist_iter_t SlistForEach(slist_iter_t from, slist_iter_t to, 
	action_func_t action_func , void *params)
{
	slist_node_t *tmp = from;

	while(tmp != to)
	{
		if(action_func(tmp->data, params))
		{
			return tmp;
		}
		tmp = SlistNext(tmp);
	}

	return from;
}

/*If head -> tail, returns true */
int SlistIsEmpty(const slist_t *slist)
{
	return ((slist->head == slist->tail) ? 0 : 1);  /* consider changing them */ 
}

/*Compare two nodes and returns 0 if equal*/
int SlistIsSameIter(const slist_iter_t iter1, const slist_iter_t iter2)
{
	return ((iter1->next == iter2->next) ? 0 : 1);  /* consider changing them */ 
}

/*Appends list2 to list1 */
void SlistAppend(slist_t *list1, slist_t *list2)
{
	slist_node_t *list1_tail = SlistEnd(list1);
	slist_node_t *list2_tail = SlistEnd(list2); 
	slist_node_t *list2_head = SlistBegin(list2);
	
	list2_tail->data = list1;
	list1->tail = list2_tail;
	
	list1_tail->next = SlistNext(list2_head);
	list1_tail->data = SlistGetData(list2_head);
	
	list2_head->next = NULL;
	list2_head->data = list2;
	list2->head = list2_head;
	list2->tail = list2_head;

}

node_t *Flip(node_t *head)
{
	node_t *tmp = head;

	while(NULL != tmp->next)
	{
		tmp->next = tmp;
		tmp = tmp->next;
	}

	tmp->next = tmp;
	head->next = NULL;

	return tmp;
}

/* Tells wether a given list has a loop */
/*int HasLoop(const node_t *head)
{
	int result = 0;


	return result;
}*/

/*Returns a pointer to a first node mutual fot both if any */
/*node_t *FindIntersection(node_t *head_1, node_t *head2)
{
	return NULL;
}*/