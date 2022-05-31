#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>/*size_t*/

typedef struct slist_node slist_node_t;
typedef slist_node_t* slist_iter_t;
typedef struct slist slist_t;
typedef struct node node_t;

typedef int (*is_match_t)(void *data, void *to_match); /**/
typedef int (*action_func_t)(void *data, void *params); /**/

/* In C File:

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
*/

/*Creates slist, returns pointer to slist*/
slist_t *SlistCreate(); /*O(1)*/

/*Destroys whole linked list, receives pointer to slist_t*/
void SlistDestroy(slist_t *list);/*O(1)*/

/*will return the first valid node. Receives pointer to head, returns head*/
slist_iter_t SlistBegin(const slist_t *list);/*O(1)*/

/*Receives head, returns tail*/
slist_iter_t SlistEnd(const slist_t *list);/*O(1)*/

/*Receives pointer to node, returns pointer to next node*/
slist_iter_t SlistNext(const slist_iter_t iter);/*O(1)*/

/*Will get the data from the node. returns data (void *)*/
void *SlistGetData(const slist_iter_t iter);/*O(1)*/

/*Sets data in node*/
void SlistSetData(slist_iter_t iter, void *data);/*O(1)*/

/*Malloc may return NULL*/
int SlistInsert(slist_iter_t iter, void *data);/*O(1)*/

/*Receives pointer to node and pointer to list*/
void SlistRemove(slist_iter_t iter);/*O(1)*/

/*Returns the length of the list*/
size_t SlistCount(const slist_t *slist);/*O(n)*/

/*Returns pointer to found data, else return to */
slist_iter_t SlistFind(const slist_iter_t from, const slist_iter_t to, 
	void *data, is_match_t match_func);/*O(n)*/

/*Do action to nodes in range from to */
slist_iter_t SlistForEach(slist_iter_t from, slist_iter_t to, 
	action_func_t action_func , void *params);/*O(n)*/

/*If head -> tail, returns true */
int SlistIsEmpty(const slist_t *slist);/*O(1)*/

/*Compare two nodes and returns 1 if equal*/
int SlistIsSameIter(const slist_iter_t iter1, const slist_iter_t iter2);/*O(1)*/

/*Appends list2 to list1 */
void SlistAppend(slist_t *list1, slist_t *list2);

node_t *Flip(node_t *head);

int HasLoop(const node_t *head);

#endif
