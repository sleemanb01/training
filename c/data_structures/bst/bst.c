/************************************************************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : BST -> BINARY SEARCH TREE
* REVIEWER NAME : THEODOR
************************************************************************************************/

#include <stddef.h>	         /* size_t */ 
#include <stdlib.h>          /* malloc */
#include <assert.h>          /* assert */
#include <stdio.h>

#include "bst.h"

/***********************************************************************************************
*                     THIS IMPLEMANTATION IS BASED ON IN-ORDER TRAVERSING                       *
************************************************************************************************/

struct bst
{
	bst_node_ty *root;
	bst_node_ty *end;
	bst_compare_ty compare;
	void *flag;
};

struct bst_node
{
	void *data;
	bst_node_ty *parent;
	bst_node_ty *left;
	bst_node_ty *right;
};

/***********************************************************************************************
*                                            EXTRA FUNCS                                       *
************************************************************************************************/
void insertNode(bst_iter_ty node,int direction, void *data);
bst_iter_ty BSTParent(bst_iter_ty iter);
bst_iter_ty BSTGetRight(bst_iter_ty iter);
bst_iter_ty BSTGetLeft(bst_iter_ty iter);
unsigned int IsLeftOfParent(bst_iter_ty iter);
unsigned int IsRoot(bst_iter_ty iter);
unsigned int IsLeaf(bst_iter_ty iter);
bst_node_ty *GetNode(bst_iter_ty iter);

/************************************************************************************************
*                   CREATE     
*  Parameters:      compare function, params
*  Return    :      pointer to BST (single dummy node)
*  Complexity:      O(1)
************************************************************************************************/
bst_ty *BSTCreate(bst_compare_ty compare_func, void* param)
{
	bst_ty *new = NULL;
	bst_node_ty *dummy_node = NULL;
	bst_node_ty *root = NULL;

	do
	{
		new = (bst_ty*)malloc(sizeof(bst_ty));
		if(NULL == new)
		{
			break;
		}

		root = (bst_node_ty*)malloc(sizeof(bst_node_ty));
		if(NULL == root)
		{
			break;
		}

		dummy_node = (bst_node_ty*)malloc(sizeof(bst_node_ty));
		if(NULL == dummy_node)
		{
			break;
		}

		dummy_node->parent =NULL;
		dummy_node->data = NULL;
		dummy_node->left = new->root;
		dummy_node->right = NULL;

		root->parent = dummy_node;
		root->data = NULL;
		root->left = NULL;
		root->right = NULL;

		new->root = root;
		new->end = dummy_node;
		new->compare = compare_func;
		new->flag = param;

		return new;

	}while(0);

	free(new);
	free(root);
	free(dummy_node);
	return NULL;
}

/************************************************************************************************
*                DESTROY    
*  Parameters:      BST pointer
*  Return    :      void
*  Complexity:      O(n)
************************************************************************************************/
void BSTDestroy(bst_ty *bst)
{
	bst_iter_ty begin_iter = NULL;
	bst_iter_ty end_iter = NULL;
	bst_iter_ty tmp = NULL;

	assert(NULL != bst);

	begin_iter = BSTBegin(bst);
	end_iter = BSTEnd(bst);

	while(!BSTIterIsEqual(begin_iter,end_iter))
	 {
		tmp = BSTNext(begin_iter);

		BSTRemove(begin_iter);

		begin_iter = tmp;
	 }

	free(bst);
	bst = NULL;
}

/************************************************************************************************
*                SIZE   
*  Parameters:      BST pointer
*  Return    :      length of the list*
*  Complexity:      O(n)
************************************************************************************************/
size_t BSTSize(const bst_ty *bst)
{
	size_t counter = 0;
	bst_iter_ty begin_iter = NULL;
	bst_iter_ty end_iter = NULL;

	assert(NULL != bst);

	for(begin_iter = BSTBegin(bst),end_iter = BSTEnd(bst);
	 BSTIterIsEqual(begin_iter,end_iter);
	 begin_iter = BSTNext(begin_iter))
	 {
		 ++counter;
	 }
	
	return counter;
}

/************************************************************************************************
*                IS EMPTY   
*  Parameters:      BST pointer
*  Return    :      boolean
*  Complexity:      O(1)
************************************************************************************************/
int BSTIsEmpty(const bst_ty *bst)
{
	return (0 == BSTSize(bst)) ? 1 : 0;
}

/************************************************************************************************
*                INSERT   
*  Parameters:      BST pointer, data
*  Return    :      boolean
*  Errors    :      Malloc may return NULL
*  Complexity:      O(1)
************************************************************************************************/
int BSTInsert(bst_ty *bst, void *data)
{
	bst_iter_ty iter = NULL;
	int direction = 0;

	assert(NULL != bst);
	assert(NULL != data);

	iter = bst->root;

	while(NULL != BSTGetData(iter))
	{
		direction = bst->compare((void*)data, BSTGetData(iter), bst->flag);
			if(1 == direction)
			{
				if(NULL != BSTGetRight(iter))
				{
					iter = BSTNext(iter);
				}
				else
				{
					break;
				}
			}
			else if(-1 == direction)
			{
				if(NULL != BSTGetLeft(iter))
				{
					iter = BSTPrev(iter);
				}
				else
				{
					break;
				}
			}
			else
			{
				return 1;
			}
	}

	insertNode(iter,direction, data);

	return 0;
}

/************************************************************************************************
*                REMOVE   
*  Parameters:      BST iterator
*  Return    :      void
*  Complexity:      O(1)
************************************************************************************************/
void BSTRemove(bst_iter_ty iter)
{
	bst_node_ty *parent = NULL;
	bst_node_ty *right = NULL;
	bst_node_ty *left = NULL;
	bst_node_ty *node = NULL;

	node = GetNode(iter);
	right = GetNode(BSTGetRight(iter));
	parent = GetNode(BSTParent(iter));
	left = GetNode(BSTGetLeft(iter));

	assert(NULL != node);

	parent = GetNode(BSTParent(iter));

	if(NULL != GetNode(BSTGetRight(iter)))
	{
		right = GetNode(BSTGetRight(iter));
	}

	if(NULL != GetNode(BSTGetLeft(iter)))
	{
		left = GetNode(BSTGetLeft(iter));
	}

	if(IsLeaf(iter))
	{
		free(node);
		node = NULL;
		return;
	}
	else
	{
		if(NULL != right)
		{
			if(IsLeftOfParent(iter))
			{
				parent->left = right;
			}
			else
			{
				parent->right = right;
			}

			right->parent = parent;

			if(NULL != left)
			{
				left->parent = right;
			}
		}
		else
		{
			if(IsLeftOfParent(iter))
			{
				parent->left = left;
			}
			else
			{
				parent->right = left;
			}

			left->parent = parent;
		}

		free(node);
		node = NULL;
	}
}

/************************************************************************************************
*                BEGIN   
*  Parameters:      pointer to head
*  Return    :      first valid node
*  Complexity:      O(log n)
************************************************************************************************/
bst_iter_ty BSTBegin(const bst_ty *list)
{
	/*bst_iter_ty iter = NULL;

	assert(NULL != list);

	iter = list->root;

	for(iter = list->root; NULL != BSTPrev(iter); iter = BSTPrev(iter))
	{
		
	}

	return iter;*/

	bst_iter_ty runner = NULL;

	assert(NULL != list);

	runner = list->root;

	while(NULL != BSTGetLeft(runner))
	{
		runner = BSTGetLeft(runner);
	}

	return runner;
	
}

/************************************************************************************************
*                END   
*  Parameters:      pointer to list
*  Return    :      first non-valid element (dummy node)
*  Complexity:      O(1)
************************************************************************************************/
bst_iter_ty BSTEnd(const bst_ty *list)
{
	/*bst_iter_ty iter = NULL;

	assert(NULL != list);

	iter = list->root;

	for(iter = list->root; NULL != BSTNext(iter); iter = BSTNext(iter))
	{
	
	}

	return iter;*/

	bst_iter_ty runner = NULL;

	assert(NULL != list);

	runner = list->root;

	while(NULL != BSTGetRight(runner))
	{
		runner = BSTGetRight(runner);
	}

	return runner;
}

/************************************************************************************************
*              NEXT   
*  Parameters:      pointer to node
*  Return    :      pointer to next node
*  Complexity:      O(1)
************************************************************************************************/
bst_iter_ty BSTNext(const bst_iter_ty iter)
{
	bst_iter_ty runner = NULL;
	assert(NULL != iter);

	runner = iter;

	if(NULL != runner->right)
	{
		return runner->right;
	}
	else if(NULL != BSTParent(runner))
	{
		while(IsLeftOfParent(runner))
		{
			runner = BSTParent(runner);
		}

		return  BSTParent(runner);
	}

	return NULL;
}

/************************************************************************************************
*            PREVIOUS   
*  Parameters:      pointer to node
*  Return    :      pointer to prev node
*  Complexity:      O(1)
************************************************************************************************/
bst_iter_ty BSTPrev(const bst_iter_ty iter)
{
	bst_iter_ty runner = NULL;

	assert(NULL != iter);

	runner = iter;

	if(NULL != BSTGetLeft(runner))
	{
		return BSTGetLeft(runner);
	}
	else if(NULL != BSTParent(runner))
	{
		while(!IsLeftOfParent(runner))
		{
			runner = BSTParent(runner);
			
			if(IsRoot(runner))
			{
				return iter;
			}

			return BSTParent(runner);
		}

		return BSTParent(runner);
		
	}

	return NULL;
}

/************************************************************************************************
*                IS EQUAL   
*  Parameters:      two nodes
*  Return    :      boolean if equal
*  Complexity:      O(1)
************************************************************************************************/
int BSTIterIsEqual(const bst_iter_ty iter1, const bst_iter_ty iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);

	return (iter1 == iter2);
}

/************************************************************************************************
*                GET DATA   
*  Parameters:      node
*  Return    :      data (void*)
*  Complexity:      O(1)
************************************************************************************************/
void *BSTGetData(const bst_iter_ty iter)
{
	assert(NULL != iter);

	return iter->data;
}

/************************************************************************************************
*                FIND  
*  Parameters:      bst pointer, data(void*)
*  Return    :      pointer to found data, else return to
*  Complexity:      O(n)
************************************************************************************************/
bst_iter_ty BSTFind(const bst_ty *bst, const void *data)
{
	bst_iter_ty iter = NULL;

	assert(NULL != bst);
	assert(NULL != data);

	iter = BSTBegin(bst);

	while(bst->end != iter)
	{
		if(1 == bst->compare((void*)data, iter->data, bst->flag))
		{
			iter = BSTPrev(iter);
		}
		else if(-1 == bst->compare((void*)data, iter->data, bst->flag))
		{
			iter = BSTNext(iter);
		}
		else
		{
			return iter;
		}
	}

	return bst->end;
}

/************************************************************************************************
*            FOR EACH  
*  Parameters:      two node pointer (from,to),action function, it's parameters
*  Return    :      to if successed, certain node if fail
*  Complexity:      O(n)
************************************************************************************************/
bst_iter_ty BSTForEach(bst_iter_ty from, bst_iter_ty to, bst_action_ty action_func, void *params)
{
	bst_iter_ty iter = NULL;

	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != params);

	iter = to;

	while(from != iter)
	{
		if(action_func(params, iter->data))
		{
			iter = BSTNext(iter);
		}
	}

	return iter;
}

void insertNode(bst_iter_ty node,int direction, void *data)
{
	bst_node_ty *new = NULL;

	if(IsRoot(node))
	{
		if(NULL == BSTGetData(node))
		{
			node->data = data;
			return;
		}
	}

	new = (bst_node_ty*)malloc(sizeof(bst_node_ty));

	if(NULL == new)
	{
		return;
	}

	new->parent = node;
	new->left = NULL;
	new->right = NULL;
	new->data = data;

	if(1 == direction)
	{
		node->right = new;
	}
	else
	{
		node->left = new;
	}
}

bst_iter_ty BSTParent(bst_iter_ty iter)
{
	assert(NULL != iter);

	if(NULL != iter->parent)
	{
		return iter->parent;
	}

	return NULL;
}
unsigned int IsLeftOfParent(bst_iter_ty iter)
{
	assert(NULL != iter);

	if(IsRoot(iter))
	{
		return 1;
	}

	if(NULL != BSTParent(iter))
	{
		if(NULL !=BSTParent(iter)->left)
		{
			if(iter == BSTParent(iter)->left)
			{
				return 1;
			}
		}
	}
	return 0;
}

unsigned int IsRoot(bst_iter_ty iter)
{
	bst_node_ty *node = NULL;

	assert(NULL != iter);

	node = (bst_node_ty*)iter;
	if(node->parent->data == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

unsigned int IsLeaf(bst_iter_ty iter)
{
	bst_node_ty *node = NULL;

	assert(NULL != iter);

	node = (bst_node_ty*)iter;
	if(NULL == node->left && NULL == node->right)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bst_iter_ty BSTGetRight(bst_iter_ty iter)
{
	assert(NULL != iter);

	return iter->right;
}

bst_iter_ty BSTGetLeft(bst_iter_ty iter)
{
	assert(NULL != iter);

	return iter->left;
}

bst_node_ty *GetNode(bst_iter_ty iter)
{
	bst_node_ty *node;
	node = iter;
	return node;
}

