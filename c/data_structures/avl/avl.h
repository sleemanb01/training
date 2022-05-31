#ifndef __AVL_H__
#define __AVL_H__
/*	VERSION 2.1	*/
#include <stddef.h>
#include "dlist.h"
/*
struct avl
{
    avl_node_ty root_parent;  <--- dummy
    avl_compare_ty *compare; 
    void* params;
};

typedef enum {LEFT, RIGHT, CHILDREN_NUM} children_ty;
struct avl_node
{
    void *data;
    avl_node_ty *children[CHILDREN_NUM];
    size_t height;
};
*/
typedef enum {PRE, IN, POST} order_ty;

typedef struct avl avl_ty;
typedef struct avl_node avl_node_ty;

/* returns -1 if data lower, 0 if equal, 1 if data higher*/
typedef int (*avl_compare_ty)(const void *data, const void *to_compare, const void* param);
typedef int (*avl_find_if_ty)(const void *data, const void *to_compare, const void* param);
typedef int (*avl_action_ty)(void *data, void *params);

/*Creates avl, returns pointer to avl (single dummy node)*/
avl_ty *AVLCreate(avl_compare_ty compare_func, void* param); /*O(1)*/

/*Destroys whole tree and free nodes, receives pointer to avl_ty*/
void AVLDestroy(avl_ty *this);/*O(n)*/

/*Receives pointer to node to remove, returns void *data to the user */
void AVLRemove(avl_ty *this, void *data);/*O(log n) on average O(n) worst case*/

/*return 1 on failure, 0 on success*/
int AVLInsert(avl_ty *this, void *data);/*O(log n) on average O(n) worst case*/

/*Return the height of the tree. If empty - 0, if only root - 1*/
size_t AVLHeight(avl_ty *this);/*O(n)*/

/*Returns the number of nodes in the tree*/
size_t AVLSize(const avl_ty *this);/*O(n)*/

/*If list is empty, return 1, or 0 otherwise */
int AVLIsEmpty(const avl_ty *this);/*O(1)*/

/*Returns pointer to found data, else return avlEnd */
void *AVLFind(const avl_ty *this, const void *data);/*O(n)*/

/*Do action to nodes in range from to, return 1 case of failed action */
int AVLForEach(const avl_ty *this, avl_action_ty action_func, void *params, order_ty order);/*O(n)*/

/*---------------------------------------ADVANCED---------------------------------------*/

void AVLRTreeForeach(const avl_ty *this, dlist_t *dlist, avl_find_if_ty func, void *data, void *params);/*O(n)*/

/*return number of removed elements */
size_t AVLRTreeRemoveMultiple(const avl_ty *this, avl_find_if_ty func, void *data, void *params);/*O(n)*/

#endif




