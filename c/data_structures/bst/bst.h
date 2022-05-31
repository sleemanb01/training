#ifndef __BST_H__
#define __BST_H__
/*	VERSION 3.0	*/
#include <stddef.h>

typedef struct bst bst_ty;
typedef struct bst_node bst_node_ty;
typedef bst_node_ty *bst_iter_ty; 
typedef int (*bst_compare_ty)(const void *data, const void *to_compare, const void* param);/* returns -1 if data lower, 0 if equal, 1 if data higher*/
typedef int (*bst_action_ty)(void *data, void *params);

/*Creates BST, returns pointer to BST (single dummy node)*/
bst_ty *BSTCreate(bst_compare_ty compare_func, void* param); /*O(1)*/

/*Destroys whole tree and free nodes, receives pointer to bst_ty*/
void BSTDestroy(bst_ty *bst);/*O(n)*/

/*Returns the number of nodes in the tree*/
size_t BSTSize(const bst_ty *bst);/*O(n)*/

/*If list is empty, return 1, or 0 otherwise */
int BSTIsEmpty(const bst_ty *bst);/*O(1)*/

/*return 1 on failure, 0 on success*/
int BSTInsert(bst_ty *bst, void *data);/*O(log n) on average O(n) worst case*/

/*Receives pointer to node to remove */
void BSTRemove(bst_iter_ty iter);/*O(log n) on average O(n) worst case*/

/*will return the first valid node in InOrder tree traversal*/
bst_iter_ty BSTBegin(const bst_ty *bst);/*O(log n) on average O(n) worst case*/

/* returns a dummy node that if we use prev on it we get the node with the highest key value */
bst_iter_ty BSTEnd(const bst_ty *bst);/*O(log n) on average O(n) worst case*/

/*Receives pointer to node, returns pointer to next node in InOrder tree traversal */
bst_iter_ty BSTNext(const bst_iter_ty iter);/*O(log n)*/

/*Receives pointer to node, returns pointer to prev node in InOrder tree traversal */
bst_iter_ty BSTPrev(const bst_iter_ty iter);/*O(log n)*/

/*Compare two iterators and returns 1 if equal*/
int BSTIterIsEqual(const bst_iter_ty iter1, const bst_iter_ty iter2);/*O(1)*/

/*Will get the data from the iterator. returns data (void *)*/
void *BSTGetData(const bst_iter_ty iter);/*O(1)*/

/*Returns pointer to found data, else return BSTEnd */
bst_iter_ty BSTFind(const bst_ty *bst, const void *data);/*O(n)*/

/*Do action to nodes in range from to */
bst_iter_ty BSTForEach(bst_iter_ty from, bst_iter_ty to, bst_action_ty action_func, void *params);/*O(n)*/

#endif



