#ifndef __SORTED_LIST_H__
#define __SORTED_LIST_H__

#include <stddef.h>

#include "dlist.h"

typedef struct sort_list sort_list_t;
typedef struct 
{
	dlist_iter_t iter;
}sort_list_iter_t;

typedef int (*sort_compare_t)(void *data, void *to_compare);/* returns -1 if data lower, 0 if equal, 1 if data higher*/
typedef int (*sort_is_match_t)(void *to_match, void *data);/* returns 1 if match, 0 otherwise*/ 
typedef int (*sort_action_t)(void *data, void *params);
/*
struct sort_list
{
    dlist_t *sort_list;
    compare_t compare:
};
*/

/*
*  Description:     Create a Sorted List 
*  Errors:          malloc can return NULL if failed
*  Parameters:      None
*  Return value:    A pointer to the created list, NULL if malloc faild
*  Complexity:      O(1)
*/
sort_list_t *SortedListCreate(sort_compare_t compare_func);

/*
*  Description:     Destroy a given Sorted List
*  Errors:          None
*  Parameters:      pointer to the sort list of type sort_list_t
*  Return value:    None
*  Complexity:      O(n)
*/
void SortedListDestroy(sort_list_t *list);

/*
*  Description:     get the first valid of a list
*  Errors:          None
*  Parameters:      pointer to the sort list of type sort_list_t
*  Return value:    pointer to the first valid of given list of type sort_list_node_t
*  Complexity:      O(1)
*/
sort_list_iter_t SortedListBegin(const sort_list_t *list);

/*
*  Description:     get the last node of a list
*  Errors:          None
*  Parameters:      pointer to sort list of type sort_list_t
*  Return value:    pointer to the last node of a list of type sort_list_node_t
*  Complexity:      O(1)
*/
sort_list_iter_t SortedListEnd(const sort_list_t *list);

/*
*  Description:     get the next node of a given iter
*  Errors:          None
*  Parameters:      pointer to the sort list node of type sort_list_node_t
*  Return value:    pointer to the next node in a list of type sort_list_node_t
*  Complexity:      O(1)
*/
sort_list_iter_t SortedListNext(sort_list_iter_t iter);

/*
*  Description:     get the previous node of a given iter
*  Errors:          None
*  Parameters:      pointer to the sort list node of type sort_list_node_t
*  Return value:    pointer to the prev node in a list of type sort_list_node_t 
*  Complexity:      O(1)
*/
sort_list_iter_t SortedListPrev(sort_list_iter_t iter);

/*
*  Description:     get the data of a given iter
*  Errors:          None
*  Parameters:      pointer to the sort list node of type sort_list_node_t
*  Return value:    pointer to data of type void
*  Complexity:      O(1)
*/
void *SortedListGetData(sort_list_iter_t iter);

/*
*  Description:     compare two nodes in a list and check if they are equal
*  Errors:          None
*  Parameters:      pointer to the sort list node of type sort_list_node_t
*					second pointer to the sort list node of type sort_list_node_t
*  Return value:    Returns 1 if equal, 0 otherwise
*  Complexity:      O(1)
*/
int SortedListIterIsEqual(sort_list_iter_t iter1, sort_list_iter_t iter2);

/*
*  Description:     calculate the length of the list
*  Errors:          None
*  Parameters:      pointer to the sort list of type sort_list_t
*  Return value:    size of the sort list in size_t
*  Complexity:      O(n)
*/
size_t SortedListSize(const sort_list_t *list);

/*
*  Description:		Check if the list is empty
*  Errors:          None
*  Parameters:      pointer to the sort list of type sort_list_t
*  Return value:	Returns 1 if empty, 0 otherwise
*  Complexity:      O(1)
*/
int SortedListIsEmpty(const sort_list_t *list);

/*
*  Description:     insert data to a new node in an orderd place
*  Errors:          malloc can return NULL if failed
*  Parameters:      data to insert to the list
*					pointer to sort list of type sort_list_t
*  Return value:    Returns inserted iterator on success, end iterator otherwise
*  Complexity:      O(n)
*/
sort_list_iter_t SortedListInsert(sort_list_t *list, void *data);

/*
*  Description:     remove a given node
*  Errors:          None
*  Parameters:      pointer to the sort list node of type sort_list_node_t
*  Return value:    Returns the next iterator
*  Complexity:      O(1)
*/
sort_list_iter_t SortedListRemove(sort_list_iter_t iter);

/*
*  Description:     remove the last node in a sort list
*  Errors:          None
*  Parameters:      pointer to the sort list of type sort_list_t
*  Return value:    pointer to data of poped node of type void
*  Complexity:      O(1)
*/
void *SortedListPopFront(sort_list_t *list);

/*
*  Description:     remove the last node in a sort list
*  Errors:          None
*  Parameters:      pointer to the sort list of type sort_list_t
*  Return value:    pointer to data of poped node of type void
*  Complexity:      O(1)
*/
void *SortedListPopBack(sort_list_t *list);

/*
*  Description:     Find a node with specified data in the sort list
*  Errors:          None
*  Parameters:      pointer to the sort list node of type sort_list_node_t (from)
*					pointer to the sort list node of type sort_list_node_t (to)
*					pointer to data of type void to find
*					function to use in searching for the data
*  Return value:    pointer to the sort list node of type sort_list_node_t with
*					asked data if found, pointer to end node (to) otherwise
*  Complexity:      O(n)
*/
sort_list_iter_t SortedListFind(sort_list_iter_t from, sort_list_iter_t to, const sort_list_t *list, void *data);

/*
*  Description:     Find a node with specified key in the sort list
*  Errors:          None
*  Parameters:      pointer to the sort list node of type sort_list_node_t (from)
*					pointer to the sort list node of type sort_list_node_t (to)
*					pointer to data of type void to find
*					function to use in searching for the data
*  Return value:    pointer to the sort list node of type sort_list_node_t with asked data 
*					if found, pointer to end node (to) otherwise
*  Complexity:      O(n)
*/
sort_list_iter_t SortedListFindIf(sort_list_iter_t from, sort_list_iter_t to, sort_is_match_t match_func, void *data);
	
/*
*  Description:		Do an action on a sequence of nodes
*  Errors:			Action dependent
*  Parameters:		pointer to the sort list node of type sort_list_node_t (from)
*					pointer to the sort list node of type sort_list_node_t (to)
*					function to do said action
*					pointer to function parameters of type void
*  Return value:    pointer to the node before last end of given range of the sort list of 
                    type sort_list_node_t, pointer to other node if function failed
*  Complexity:      O(n)
*/
sort_list_iter_t SortedListForeach(sort_list_iter_t from, sort_list_iter_t to, sort_action_t action_func, void *params);


/*
*  Description:     merge two lists in sequential order
*  Errors:          None
*  Parameters:      pointer to the sort list of type sort_list_t
*                   second pointer to the sort list of type sort_list_t
*  Return value:    None
*  Complexity:      O(n)
*/
void SortedListMerge(sort_list_t *target_list, sort_list_t *src_list);

#endif
