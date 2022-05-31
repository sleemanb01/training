/************************************************************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : AVL
* REVIEWER NAME : ANDREY
************************************************************************************************/

#include <stddef.h>	         /* size_t */ 
#include <stdlib.h>          /* malloc */
#include <assert.h>          /* assert */

#include "avl.h"

/***********************************************************************************************
*                                  TYPES/STRUCTS                                               *
************************************************************************************************/

typedef enum {LEFT, RIGHT, CHILDREN_NUM} children_ty;

struct avl_node
{
    void *data;
    avl_node_ty *children[CHILDREN_NUM];
    size_t height;
};

struct avl
{
    avl_node_ty root_parent;  /* <--- dummy */
    avl_compare_ty compare; 
    void* params;
};

/***********************************************************************************************
*                                            EXTRA FUNCS                                       *
************************************************************************************************/

static avl_node_ty *createNewNode(void *data);
static avl_node_ty *getLeft(avl_node_ty *node);
static avl_node_ty *getRight(avl_node_ty *node);

static void *getData(avl_node_ty *node);
static void *inOrderSuccessor(avl_node_ty *node);
static void *nodeDestroy(avl_node_ty *node, avl_ty *this);

static void *recursiveSearch(avl_node_ty *node, const avl_ty *this, const void *data);
static avl_node_ty *recursiveRemove(avl_node_ty *node, avl_ty *this, void *data);
static avl_node_ty *recursiveInsert(avl_node_ty *node, avl_ty *this, void *data);
static size_t recursiveSize(avl_node_ty *node);

static avl_node_ty *AVLEnd(avl_node_ty *root);
static avl_node_ty *AVLBegin(avl_node_ty *node);
static int isSameNode(avl_node_ty *node1, avl_node_ty *node2);

static void inOrderForEach(avl_node_ty *begin, avl_action_ty func, void *params);
static void preOrderForEach(avl_node_ty *begin, avl_action_ty func, void *params);
static void postOrderForEach(avl_node_ty *begin, avl_action_ty func, void *params);

/************************************************************************************************
*                   CREATE     
*  Parameters:      compare function, param
*  Return    :      pointer to avl
*  Complexity:      O(1)
************************************************************************************************/

avl_ty *AVLCreate(avl_compare_ty compare_func, void* param)
{
	avl_ty *new = NULL;
	avl_node_ty *dummy = NULL;

	assert(NULL != compare_func);

	do
	{
		new = (avl_ty*)malloc(sizeof(avl_ty));
		if(NULL == new)
		{
			break;
		}

		dummy = (avl_node_ty*)malloc(sizeof(avl_node_ty));
		if(NULL == dummy)
		{
			break;
		}

		dummy->children[LEFT] = NULL;
		dummy->children[RIGHT] = NULL;
		dummy->data = NULL;
		dummy->height = 0;

		new->root_parent = *dummy;
		new->compare = compare_func;
		new->params = param;

		return new;

	} while (0);

	free(new);

	return NULL;
	
}

/************************************************************************************************
*                   DESTROY     
*  Parameters:      avl type
*  Return    :      NONE
*  Complexity:      O(n)
************************************************************************************************/
void AVLDestroy(avl_ty *this)
{
	avl_node_ty node;

	assert(NULL != this);
	
	node = this->root_parent;

	nodeDestroy(&node, this);
}

/************************************************************************************************
*                   REMOVE     
*  Parameters:      pointer to node to remove
*  Return    :      void *data to the user 
*  Complexity:      O(log n) on average O(n) worst case
************************************************************************************************/
void AVLRemove(avl_ty *this, void *data)
{
	avl_node_ty node;

	assert(NULL != this);

	node = this->root_parent;

	if(NULL != getData(&node))
	{
		recursiveRemove(&node,this,data);
	}
}

/************************************************************************************************
*                   INSERT     
*  Parameters:      avl type, data
*  Return    :      1 on failure, 0 on success
*  Complexity:      O(log n) on average O(n) worst case
************************************************************************************************/
int AVLInsert(avl_ty *this, void *data)
{
	avl_node_ty node;
	size_t old_size = 0;

	assert(NULL != this);

	old_size = AVLSize(this);

	node = this->root_parent;

	if(NULL != getData(&node))
	{
		recursiveInsert(&node,this,data);
	}
	else
	{
		this->root_parent.data = data;
	}
	
	return (AVLSize(this) > old_size);
}

/************************************************************************************************
*                   HEIGHT     
*  Parameters:      avl type
*  Return    :      number of edges from the deepest leaf
*  Complexity:      O(n)
************************************************************************************************/
size_t AVLHeight(avl_ty *this)
{
	assert(NULL !=this);

	return this->root_parent.height;
}

/************************************************************************************************
*                   SIZE     
*  Parameters:      avl type
*  Return    :      number of nodes in the tree
*  Complexity:      O(n)
************************************************************************************************/
size_t AVLSize(const avl_ty *this)
{
	avl_node_ty node;
	int is_root_initialized = -1;

	assert(NULL != this);

	node = this->root_parent;

	if(NULL != getData(&node))
	{
		++is_root_initialized;
	}

	return (recursiveSize(&node) + is_root_initialized);
}

/************************************************************************************************
*                   ISEMPTY     
*  Parameters:      avl type
*  Return    :      1 if empty, 0 otherwise
*  Complexity:      O(1)
************************************************************************************************/
int AVLIsEmpty(const avl_ty *this)
{
	assert(NULL != this);

	return (AVLSize(this) == 0);
}

/************************************************************************************************
*                   FIND     
*  Parameters:      avl type, data
*  Return    :      pointer to found data, else return avlEnd
*  Complexity:      O(n)
************************************************************************************************/
void *AVLFind(const avl_ty *this, const void *data)
{
	avl_node_ty node;
	void *found = NULL;

	assert(NULL != this);

	node = this->root_parent;

	found = recursiveSearch(&node,this,data);

	return found;
}

/************************************************************************************************
*                   FOREACH     
*  Parameters:      avl type, dlist, find func, param, order type
*  Return    :      1 case of failed action
*  Complexity:      O(n)
************************************************************************************************/
int AVLForEach(const avl_ty *this, avl_action_ty action_func, void *params, order_ty order)
{
	avl_node_ty begin, end;

	assert(NULL != this);
	assert(NULL != action_func);

	begin = end = this->root_parent;
	begin = *AVLBegin(&begin);
	end = *AVLEnd(&end);

	switch (order)
	{
		case PRE:
		{
			preOrderForEach(&begin,action_func,params);
			break;
		}
		case POST:
		{
			postOrderForEach(&begin,action_func,params);
			break;
		}
		default:
		{
			inOrderForEach(&begin,action_func,params);
			break;
		}
	}

	return isSameNode(&begin,&end);

}

/***********************************************************************************************
*                                       ADVANCED                                               *
************************************************************************************************/

/************************************************************************************************
*                   TREE FOREACH     
*  Parameters:      avl type, dlist, find func, param
*  Return    :      pointer to avl
*  Complexity:      O(n)
************************************************************************************************/
/*void AVLRTreeForeach(const avl_ty *this, dlist_t *dlist, avl_find_if_ty func, void *data, void *params)
{

}*/

/************************************************************************************************
*                   REMOVE MULTIPLE     
*  Parameters:      avl type, find func, params
*  Return    :      number of removed elements
*  Complexity:      O(n)
************************************************************************************************/
/*size_t AVLRTreeRemoveMultiple(const avl_ty *this, avl_find_if_ty func, void *data, void *params)
{

}*/

/***********************************************************************************************
*                                       EXTRA FUNCS                                            *
************************************************************************************************/

/*********************************** GET LEFT **********************************************/
static avl_node_ty *getLeft(avl_node_ty *node)
{
	return node->children[LEFT];
}

/*********************************** GET RIGHT *********************************************/
static avl_node_ty *getRight(avl_node_ty *node)
{
	return node->children[RIGHT];
}

/********************************* GET DATA **********************************************/
static void *getData(avl_node_ty *node)
{
	if(NULL != node)
	{
		return node->data;
	}
	
	return NULL;
}

/*********************************** NODE DESTROY ***************************************/
static void *nodeDestroy(avl_node_ty *node, avl_ty *this)
{
	if(NULL == node)
	{
		return NULL;
	}

	AVLRemove(this, nodeDestroy(getData(getLeft(node)), this));
	AVLRemove(this, nodeDestroy(getData(getRight(node)), this));

	return NULL;
}

/********************************** RECURSIVE REMOVE ************************************/
static avl_node_ty *recursiveRemove(avl_node_ty *node, avl_ty *this, void *data)
{
	int res;
	if(NULL == node)
	{
		return node;
	}

	res = this->compare(getData(node),data,this->params);

	if(1 == res)
	{
		node->children[LEFT] = recursiveRemove(getLeft(node),this,data);
	}
	else if(-1 == res)
	{
		node->children[RIGHT] = recursiveRemove(getRight(node),this,data);
	}
	else
	{
		if(NULL == getLeft(node))
		{
			return getRight(node);
		}
		else if(NULL == getRight(node))
		{
			return getLeft(node);
		}

		node->data = inOrderSuccessor(getRight(node));
		node->children[RIGHT] = recursiveRemove(getRight(node), this, getData(node));
	}
{...}
	return node;
}

/*********************************** INORDER SUCCESSOR **********************************/
static void *inOrderSuccessor(avl_node_ty *node)
{
	void *min = NULL;

	assert(NULL != node);

	min = node->data;

	while(NULL != getLeft(node))
	{
		min = getData(getLeft(node));
		node = getLeft(node);
	}

	return min;
}

/********************************** RECURSIVE INSERT ************************************/
static avl_node_ty *recursiveInsert(avl_node_ty *node, avl_ty *this, void *data)
{
	int res;
	if (NULL == node)
	{
		return createNewNode(data);
	}

	res = this->compare(node->data,data,this->params);

	if(1 == res)
	{
		node->children[LEFT] = recursiveInsert(getLeft(node), this, data);
	}
	if(-1 == res)
	{
		node->children[RIGHT] = recursiveInsert(getRight(node), this, data);
	}

	return NULL;
}

/****************************** CREATE NEW NODE ************************************/
static avl_node_ty *createNewNode(void *data)
{
	avl_node_ty *new = NULL;

	assert(NULL != data);

	new = (avl_node_ty*)malloc(sizeof(avl_node_ty));
	if(NULL == new)
	{
		return NULL;
	}

	new->data = data;
	new->children[LEFT] = NULL;
	new->children[RIGHT] = NULL;
    new->height = 0;

	return new;
}

/****************************** SIZE ************************************/
static size_t recursiveSize(avl_node_ty *node)
{
	if (node == NULL)
	{
		return 0;
	}

	return(recursiveSize(getLeft(node)) + 1 + recursiveSize(getRight(node)));
}

/****************************** RECURSIVE SEARCH ************************************/
static void *recursiveSearch(avl_node_ty *node, const avl_ty *this, const void *data)
{
	if(data == getData(node))
	{
		return getData(node);
	} 

	if(1 == this->compare(getData(node), data, this->params))
	{
		return recursiveSearch(getLeft(node), this, data);
	}

	else if(-1 == this->compare(getData(node), data, this->params))
	{
		return recursiveSearch(getRight(node), this, data);
	}    

	return NULL;   
}

/****************************** AVL BEGIN ************************************/
static avl_node_ty *AVLBegin(avl_node_ty *root)
{
	if(NULL == getLeft(root))
	{
		return root;
	}

	return AVLBegin(getLeft(root));
}

/****************************** AVL END ************************************/
static avl_node_ty *AVLEnd(avl_node_ty *root)
{
	if(NULL == getRight(root))
	{
		return root;
	}

	return AVLEnd(getRight(root));
}

/****************************** IN ORDER ************************************/
static void inOrderForEach(avl_node_ty *begin, avl_action_ty func, void *params)
{
	if (begin == NULL)
	{
        return;
	}

    inOrderForEach(getLeft(begin), func, params);

	func(getData(begin), params);
 
    inOrderForEach(getRight(begin), func, params);

}

/****************************** PRE ORDER ************************************/
static void preOrderForEach(avl_node_ty *begin, avl_action_ty func, void *params)
{
	if (begin == NULL)
	{
        return;
	}

	func(getData(begin), params);
 
    preOrderForEach(getLeft(begin), func, params);
 
    preOrderForEach(getRight(begin), func, params);

}

/****************************** POST ORDER ************************************/
static void postOrderForEach(avl_node_ty *begin, avl_action_ty func, void *params)
{
	if (begin == NULL)
	{
        return;
	}
 
    postOrderForEach(getLeft(begin), func, params);
    postOrderForEach(getRight(begin), func, params);

	func(getData(begin), params);
}

/****************************** IS SAME NODE ************************************/
static int isSameNode(avl_node_ty *node1, avl_node_ty *node2)
{
	int res = 1;

	if(getData(node1) != getData(node2))
	{
		res = 0;
	}

	if(node1->height != node2->height)
	{
		res = 0;
	}

	if(node1->children != node2->children)
	{
		res = 0;
	}

	return res;
}
