#ifndef __DLIST_H__
#define __DLIST_H__

typedef struct dlist dlist_t;
typedef struct dlist_node dlist_node_t;
typedef dlist_node_t *dlist_iter_t;

/*
*  Description:     Create a DLL 
*  Errors:          Malloc error,
*  Parameters:      Size of the flexabile array
*  Return value:    A pointer to the created list
*  Complexity:      O(1)match_func
*/
dlist_t *DlistCreate();

/*
*  Description:     Destroy a DLL 
*  Errors:          
*  Parameters:      A pointer to a given list
*  Return value:    
*  Complexity:      O(1)
*/
void DlistDestroy(dlist_t *list);

/*
*  Description:     get the head of a list
*  Errors:          
*  Parameters:      A pointer to the list
*  Return value:    A node
*  Complexity:      O(1)
*/
dlist_iter_t DlistBegin(const dlist_t *list);

/*
*  Description:     get the tail of a list
*  Errors:          
*  Parameters:      A pointer to the list
*  Return value:    A node
*  Complexity:      O(1)
*/
dlist_iter_t DlistEnd(const dlist_t *list);

/*Receives pointer to node, returns pointer to next node*/
/*
*  Description:     get the next node of a given node
*  Errors:          
*  Parameters:      A pointer to the list
*  Return value:    A node 
*  Complexity:      O(1)
*/
dlist_iter_t DlistNext(const dlist_iter_t iter);

/*
*  Description:     get the previous node of a given node
*  Errors:          
*  Parameters:      A node
*  Return value:    A node 
*  Complexity:      O(1)
*/
dlist_iter_t DlistPrev(const dlist_iter_t iter);

/*
*  Description:     get data of the node
*  Errors:          
*  Parameters:      A node
*  Return value:    A pointer
*  Complexity:      O(1)
*/
void *DlistGetData(const dlist_iter_t iter);

/*
*  Description:     set data to the node
*  Errors:          
*  Parameters:      A node,data
*  Return value:    
*  Complexity:      O(1)
*/
void DlistSetData(dlist_iter_t iter, void *data);

/*
*  Description:     insert data of the node
*  Errors:          Malloc may return NULL
*  Parameters:      A node, data
*  Return value:    1/0 
*  Complexity:      O(1)
*/
int DlistInsert(dlist_iter_t where, void *data);

/*
*  Description:     remove the node
*  Errors:          
*  Parameters:      A node
*  Return value:    void
*  Complexity:      O(1)
*/
void DlistRemove(dlist_iter_t iter);

/*push new node with data, to the back of dlist*/
/*
*  Description:     push data after tail
*  Errors:           Malloc may return NULL
*  Parameters:      A node,data
*  Return value:    1/0
*  Complexity:      O(1)
*/
int DlistPushBack(dlist_t *dlist, void *data);

/*push new node with data, to the back of dlist*/
/*
*  Description:     pop data before tail
*  Errors:          Malloc may return NULL
*  Parameters:      A node
*  Return value:    a pointer
*  Complexity:      O(1)
*/
void *DlistPopBack(dlist_t *dlist);

/*
*  Description:     push data after head
*  Errors:          Malloc may return NULL
*  Parameters:      A node,data
*  Return value:    1/0
*  Complexity:      O(1)
*/
int DlistPushFront(dlist_t *dlist, void *data);

/*
*  Description:     pop data after head
*  Errors:          
*  Parameters:      A pointer to the list
*  Return value:    a pointer
*  Complexity:      O(1)
*/
void *DlistPopFront(dlist_t *dlist);

/*
*  Description:     calculate the length of the list
*  Errors:          
*  Parameters:      A pointer to the list
*  Return value:    length
*  Complexity:      O(n)
*/
size_t DlistSize(const dlist_t *dlist);

/*Returns pointer to found data, else return to */
/*
*  Description:     Find data in the list
*  Errors:          
*  Parameters:      A pointer to from node, to node, data, reference to a function
*  Return value:    A node
*  Complexity:      O(n)
*/
dlist_iter_t DlistFind(const dlist_iter_t from, const dlist_iter_t to, 
	const void *data, int (*match_func)(const void *data, const void *to_match));

/*
*  Description:     Do action in the list in a specific range
*  Errors:          
*  Parameters:      (start from) node, (until you get to) node, reference to a function, pointer to the function params
*  Return value:    A node
*  Complexity:      O(n)
*/
dlist_iter_t DlistForEach(dlist_iter_t from, dlist_iter_t to, 
    int (*action_func)(void *data, void *params), void *params);

/*
*  Description:     Check if list is empty
*  Errors:          
*  Parameters:      A list pointer
*  Return value:    1/0
*  Complexity:      O(1)
*/
int DlistIsEmpty(const dlist_t *dlist);

/*
*  Description:     compare to nodes
*  Errors:          
*  Parameters:      A node, node
*  Return value:    1/0
*  Complexity:      O(1)
*/
int DlistIsSameIter(const dlist_iter_t iter1, const dlist_iter_t iter2);

/*
*  Description:     insert one list to other
*  Errors:          
*  Parameters:      (insert after) node, (from where to slice) node, (slice until you get to) node
*  Return value:    
*  Complexity:      O(1)
*/
void DlistSplice(dlist_iter_t target, dlist_iter_t from, dlist_iter_t to);

/*Returns 1 if malloc failed to list of found data, else return to 
*                                                     */

/*
*  Description:     Do action in the list in a specific range
*  Errors:          Malloc may return NULL
*  Parameters:      (start from) node, 
                    (until you get to) node,
                    data,
                    reference to a function,
                    pointer to the function params,
                    (targer) list pointer,
*  Return value:    1/0
*  Complexity:      O(n)
*/
int DlistMultiFind(const dlist_iter_t from, const dlist_iter_t to, 
	const void *data, int (*match_func)(const void *data, const void *to_match), dlist_t *target_list);

#endif