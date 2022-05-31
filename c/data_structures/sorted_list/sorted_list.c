/***************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : SORTED LIST
* REVIEWER NAME : IDAN
*****************************************************/

#include<stdlib.h>           /* malloc */
#include <assert.h>          /* assert */
#include <stdio.h>           /* sizeof */

#include"sorted_list.h"

struct sort_list
{
    dlist_t *sort_list;
    sort_compare_t compare;
};

/**********************************************************************
*  Description:     Create a Sorted List 
*  Errors:          malloc can return NULL if failed
*  Parameters:      None
*  Return value:    A pointer to the created list, NULL if malloc faild
*  Complexity:      O(1)
**********************************************************************/
sort_list_t *SortedListCreate(sort_compare_t compare_func)
{
	sort_list_t *list = NULL;
	dlist_t *dlist = NULL;

	do
	{
		list = (sort_list_t*)malloc(sizeof(sort_list_t));
		if(NULL == list)
		{
			break;
		}

		dlist = DlistCreate();
		if(NULL == dlist)
		{
			break;
		}

		list->sort_list = dlist;
		list->compare = compare_func;

		return list;

	}while(0);

	free(list);
	free(dlist);

	return NULL;
}

/**********************************************************************
*  Description:     Destroy a given Sorted List
*  Errors:          None
*  Parameters:      pointer to the sort list of type sort_list_t
*  Return value:    None
*  Complexity:      O(n)
**********************************************************************/
void SortedListDestroy(sort_list_t *list)
{
	assert(NULL != list);

	DlistDestroy(list->sort_list);

	free(list);
}

/**********************************************************************
*  Description:     get the first valid of a list
*  Errors:          None
*  Parameters:      pointer to the sort list of type sort_list_t
*  Return value:    pointer to the first valid of given list of type sort_list_node_t
*  Complexity:      O(1)
**********************************************************************/
sort_list_iter_t SortedListBegin(const sort_list_t *list)
{
	sort_list_iter_t tmp;

	assert(NULL != list);

	tmp.iter = DlistBegin(list->sort_list);
	return tmp;
}

/**********************************************************************
*  Description:     get the last node of a list
*  Errors:          None
*  Parameters:      pointer to sort list of type sort_list_t
*  Return value:    pointer to the last node of a list of type sort_list_node_t
*  Complexity:      O(1)
**********************************************************************/
sort_list_iter_t SortedListEnd(const sort_list_t *list)
{
	sort_list_iter_t tmp;

	assert(NULL != list);

	tmp.iter = DlistEnd(list->sort_list);
	return tmp;
}

/**********************************************************************
*  Description:     get the next node of a given iter
*  Errors:          None
*  Parameters:      pointer to the sort list node of type sort_list_node_t
*  Return value:    pointer to the next node in a list of type sort_list_node_t
*  Complexity:      O(1)
**********************************************************************/
sort_list_iter_t SortedListNext(sort_list_iter_t iter)
{
	assert(NULL != iter.iter);

	iter.iter = DlistNext(iter.iter);
	return iter;
}

/**********************************************************************
*  Description:     get the previous node of a given iter
*  Errors:          None
*  Parameters:      pointer to the sort list node of type sort_list_node_t
*  Return value:    pointer to the prev node in a list of type sort_list_node_t 
*  Complexity:      O(1)
**********************************************************************/
sort_list_iter_t SortedListPrev(sort_list_iter_t iter)
{
	assert(NULL != iter.iter);

	iter.iter = DlistPrev(iter.iter);
	return iter;
}

/**********************************************************************
*  Description:     get the data of a given iter
*  Errors:          None
*  Parameters:      pointer to the sort list node of type sort_list_node_t
*  Return value:    pointer to data of type void
*  Complexity:      O(1)
**********************************************************************/
void *SortedListGetData(sort_list_iter_t iter)
{
	assert(NULL != iter.iter);

	return DlistGetData(iter.iter);
}

/**********************************************************************
*  Description:     compare two nodes in a list and check if they are equal
*  Errors:          None
*  Parameters:      pointer to the sort list node of type sort_list_node_t
*					second pointer to the sort list node of type sort_list_node_t
*  Return value:    Returns 1 if equal, 0 otherwise
*  Complexity:      O(1)
**********************************************************************/
int SortedListIterIsEqual(sort_list_iter_t iter1, sort_list_iter_t iter2)
{
	return DlistIsSameIter(iter1.iter,iter2.iter);
}

/**********************************************************************
*  Description:     calculate the length of the list
*  Errors:          None
*  Parameters:      pointer to the sort list of type sort_list_t
*  Return value:    size of the sort list in size_t
*  Complexity:      O(n)
**********************************************************************/
size_t SortedListSize(const sort_list_t *list)
{
	return DlistSize(list->sort_list);
}

/**********************************************************************
*  Description:		Check if the list is empty
*  Errors:          None
*  Parameters:      pointer to the sort list of type sort_list_t
*  Return value:	Returns 1 if empty, 0 otherwise
*  Complexity:      O(1)
**********************************************************************/
int SortedListIsEmpty(const sort_list_t *list)
{
	return DlistIsEmpty(list->sort_list);
}

/**********************************************************************
*  Description:     insert data to a new node in an orderd place
*  Errors:          malloc can return NULL if failed
*  Parameters:      data to insert to the list
*					pointer to sort list of type sort_list_t
*  Return value:    Returns inserted iterator on success, end iterator otherwise
*  Complexity:      O(n)
**********************************************************************/
sort_list_iter_t SortedListInsert(sort_list_t *list, void *data)
{
	sort_list_iter_t tmp;

	assert(NULL != list);    

	tmp = SortedListBegin(list);

	while(!SortedListIterIsEqual(SortedListEnd(list), tmp))
		{
			if((1 == list->compare(data, SortedListGetData(tmp))))
			{
				break;
			}

			tmp = SortedListNext(tmp);
		}

	DlistInsert(tmp.iter, data);

	tmp = SortedListPrev(tmp);

	return tmp;
}

/**********************************************************************
*  Description:     remove a given node
*  Errors:          None
*  Parameters:      pointer to the sort list node of type sort_list_node_t
*  Return value:    Returns the next iterator
*  Complexity:      O(1)
**********************************************************************/
sort_list_iter_t SortedListRemove(sort_list_iter_t iter)
{
	sort_list_iter_t tmp;

	assert(NULL != iter.iter);

	tmp = SortedListNext(iter);

	DlistRemove(iter.iter);

	return tmp;
}

/**********************************************************************
*  Description:     remove the last node in a sort list
*  Errors:          None
*  Parameters:      pointer to the sort list of type sort_list_t
*  Return value:    pointer to data of poped node of type void
*  Complexity:      O(1)
**********************************************************************/
void *SortedListPopFront(sort_list_t *list)
{

	assert(NULL != list);

	return (DlistPopFront(list->sort_list));
}

/**********************************************************************
*  Description:     remove the last node in a sort list
*  Errors:          None
*  Parameters:      pointer to the sort list of type sort_list_t
*  Return value:    pointer to data of poped node of type void
*  Complexity:      O(1)
**********************************************************************/
void *SortedListPopBack(sort_list_t *list)
{
	assert(NULL != list);

	return (DlistPopBack(list->sort_list));
}

/**********************************************************************
*  Description:     Find a node with specified data in the sort list
*  Errors:          None
*  Parameters:      pointer to the sort list node of type sort_list_node_t (from)
*					pointer to the sort list node of type sort_list_node_t (to)
*					pointer to data of type void to find
*					function to use in searching for the data
*  Return value:    pointer to the sort list node of type sort_list_node_t with
*					asked data if found, pointer to end node (to) otherwise
*  Complexity:      O(n)
**********************************************************************/
sort_list_iter_t SortedListFind(sort_list_iter_t from, sort_list_iter_t to, const sort_list_t *list, void *data)
{
	sort_list_iter_t tmp;

	assert(NULL != from.iter);
	assert(NULL != to.iter);
	assert(NULL != list);

	tmp = from;

	while((!SortedListIterIsEqual(tmp,to)) && (0 == list->compare(SortedListGetData(tmp),data)))
	{
		/*if(0 == list->compare(SortedListGetData(tmp),data))
		{
			break;
		}*/

		tmp.iter = DlistNext(tmp.iter);
	}

	return tmp;
}

/**********************************************************************
*  Description:     Find a node with specified key in the sort list
*  Errors:          None
*  Parameters:      pointer to the sort list node of type sort_list_node_t (from)
*					pointer to the sort list node of type sort_list_node_t (to)
*					pointer to data of type void to find
*					function to use in searching for the data
*  Return value:    pointer to the sort list node of type sort_list_node_t with asked data 
*					if found, pointer to end node (to) otherwise
*  Complexity:      O(n)
**********************************************************************/
sort_list_iter_t SortedListFindIf(sort_list_iter_t from, sort_list_iter_t to, sort_is_match_t match_func, void *data)
{
	sort_list_iter_t tmp;

	assert(NULL != from.iter);
	assert(NULL != to.iter);

	/*tmp = from;

	while(!DlistIsSameIter(to.iter,tmp.iter))
	{
		if(match_func(DlistGetData(tmp.iter), data))
		{
			break;
		}
		tmp.iter = DlistNext(tmp.iter);
	}

	return tmp;*/

	tmp.iter = DlistFind(from.iter,to.iter,data, match_func);
	return tmp;
}

	
/**********************************************************************
*  Description:		Do an action on a sequence of nodes
*  Errors:			Action dependent
*  Parameters:		pointer to the sort list node of type sort_list_node_t (from)
*					pointer to the sort list node of type sort_list_node_t (to)
*					function to do said action
*					pointer to function parameters of type void
*  Return value:    pointer to the node before last end of given range of the sort list of 
                    type sort_list_node_t, pointer to other node if function failed
*  Complexity:      O(n)
**********************************************************************/
sort_list_iter_t SortedListForeach(sort_list_iter_t from, sort_list_iter_t to, sort_action_t action_func, void *params)
{
	sort_list_iter_t *tmp;

	assert(NULL != from.iter);
	assert(NULL != to.iter);

	tmp = &from;

	while(!DlistIsSameIter(to.iter,tmp->iter))
	{
		if(action_func(DlistGetData(tmp->iter), params))
		{
			break;
		}
		tmp->iter = DlistNext(tmp->iter);
	}

	return *tmp;
}


/**********************************************************************
*  Description:     merge two lists in sequential order
*  Errors:          None
*  Parameters:      pointer to the sort list of type sort_list_t
*                   second pointer to the sort list of type sort_list_t
*  Return value:    None
*  Complexity:      O(n)
**********************************************************************/
void SortedListMerge(sort_list_t *target_list, sort_list_t *src_list)
{
	sort_list_iter_t iter1, iter2;
	
	assert(NULL != target_list);
	assert(NULL != src_list);
	
	iter1 = SortedListBegin(target_list);
	iter2 = SortedListBegin(src_list);
	
	while (!SortedListIsEmpty(src_list))
	{
		if (SortedListIterIsEqual(SortedListEnd(target_list), iter1))
		{
			DlistSplice(iter1.iter, iter2.iter, SortedListEnd(src_list).iter);
		}
		else if (target_list->compare(SortedListGetData(iter1),
		 SortedListGetData(iter2)) > 0)
		{
			iter1 = SortedListNext(iter1);
		}
		else
		{
			DlistSplice(iter1.iter, iter2.iter, SortedListNext(iter2).iter);
			iter2 = SortedListBegin(src_list);
		}
	}

}