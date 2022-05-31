#include <stdlib.h>
#include <stddef.h>
#include <assert.h>


#include "bst.h"


struct bst
{
	bst_compare_t compare_func;	
	bst_iter_t root;
/*	bst_iter_t end;
	*/
	void *params;
	
};

struct bst_node
{
	void* data;
	bst_iter_t parent;
	bst_iter_t left_child;
	bst_iter_t right_child;
	
};


static bst_iter_t TraverseTree(bst_iter_t bst_iter, void* data, bst_compare_t compare_func, void* params, int* ret_val);
static bst_iter_t FindMaxInLeftSubTree(bst_iter_t bst_iter);

static bst_iter_t CreateNode(void* data);
static bst_iter_t GetLeftChild(bst_iter_t bst_iter);
static bst_iter_t GetRightChild(bst_iter_t bst_iter);
static bst_iter_t GetParent(bst_iter_t bst_iter);

static void SetLeftChild(bst_iter_t parent, bst_iter_t child);
static void SetRightChild(bst_iter_t parent, bst_iter_t child);

static bst_iter_t PostOrderNext(bst_iter_t bst_iter);
static bst_iter_t PostOrderBegin(bst_iter_t bst_iter);


/*Creates BST, returns pointer to BST (single dummy node)*/
bst_t *BSTCreate(bst_compare_t compare_func, void* param) /*O(1)*/
{
	bst_t  *new_bst = NULL;
	bst_iter_t dummy = NULL;
	
	assert(compare_func);
	
	do
	{
		new_bst = (bst_t*)malloc(sizeof(bst_t));
		if(NULL == new_bst)
		{
			break;
		}
		dummy = (bst_iter_t)malloc(sizeof(struct bst_node));
		if (NULL == dummy)
		{
			break;
		}
		new_bst->compare_func = compare_func;
		new_bst->params = param;
		new_bst->root = dummy;
		dummy->parent = NULL;
		dummy->left_child = NULL;
		dummy->right_child = NULL;
		dummy->data = NULL;
		
		return new_bst;
		
	}while(0);
	free(new_bst);
	free(dummy);
	return NULL;
	
}
/*Destroys whole linked list, receives pointer to BST_t*/
void BSTDestroy(bst_t *bst)
{
	bst_iter_t runner = NULL;
	bst_iter_t temp = NULL;
	
	assert(bst);
	
	runner = PostOrderBegin(bst->root);
	while (runner != NULL)
	{
		temp  = PostOrderNext(runner);
		free(runner);
		runner = temp;
	} /* will free all nodes including dummy node */
	free(bst);
	
	return;
	
}

/*Returns the length of the list*/
size_t BSTSize(const bst_t *bst)/*O(n)*/
{
	size_t count = 0;
	bst_iter_t runner = NULL;
	bst_iter_t end = NULL;
	
	assert(bst);
	
	end = BSTEnd(bst);
	for(runner = BSTBegin(bst); !BSTIterIsEqual(runner, end); runner = BSTNext(runner))
	{
		++count;
	}
	return count;
	
}



/*If list is empty, return 1, or 0 otherwise */
int BSTIsEmpty(const bst_t *bst)/*O(1)*/
{
	assert(bst);
	
	return ( NULL == bst->root->data);
}


/*Malloc may return NULL*/
int BSTInsert(bst_t *bst, void *data)/*O(1)*/
{
	bst_iter_t runner = NULL;
	int ret_val;
	bst_iter_t new_node = NULL;
	
	assert(bst);
	assert(data);
	
	new_node = CreateNode(data);
	if(NULL == new_node)
	{
		return 1;
	}
	
	if(BSTGetData(bst->root) == NULL) /* first node to add */
	{
		bst->root->data = data;
		new_node->data = NULL;
		SetRightChild(bst->root, new_node);
		return 0;
	}
	runner = TraverseTree(bst->root, data, bst->compare_func, bst->params, &ret_val);
	
	assert(0 != ret_val); /* TraverseTree returns 0 if the key was found in the tree already */
	
	if(ret_val == -1)
	{
		SetLeftChild(runner, new_node);
		return 0;
	}
	if(ret_val == 1)
	{
		SetRightChild(new_node, GetRightChild(runner	));		
		SetRightChild(runner, new_node);
		return 0;
	}
	
	return 1;
}


/*Receives pointer to node to remove */
void BSTRemove(bst_iter_t iter)/*O(log n )*/
{
	bst_iter_t max_in_left_subtree = NULL;
	bst_iter_t left_child_of_max = NULL;
	bst_iter_t parent = NULL;
	bst_iter_t temp = NULL;
		
	assert(iter);
	
	max_in_left_subtree = FindMaxInLeftSubTree(iter);
	if(BSTIterIsEqual(iter, max_in_left_subtree)) /* no left subtree at all */
	{
		if(NULL != GetRightChild(iter))
		{
			parent = GetParent(iter);
			if(NULL == parent) /* iter is root */
			{
				temp = GetRightChild(iter);
				iter->data = temp->data;
				iter->right_child = temp->right_child;
				iter->left_child = temp->left_child;
				
				if(NULL != iter->right_child)
				{
					iter->right_child->parent = iter;
				}
				if(NULL != iter->left_child)
				{
					iter->left_child->parent = iter;
				}
				
				
				free(temp);
				temp = NULL;
				return;
				
			}
			if(iter == GetLeftChild(parent))
			{
				SetLeftChild(parent, GetRightChild(iter));
			}
			else 
			{
				SetRightChild(parent, GetRightChild(iter));
			}
		}
		else /* no right subtree also meaning iter is a leaf*/
		{
			if(NULL != GetParent(iter))
			{
				parent = GetParent(iter);
				if(iter == GetLeftChild(parent))
				{
					SetLeftChild(GetParent(iter), NULL);			
				}
				else
				{
					SetRightChild(GetParent(iter), NULL);			
				}
			}
		}
		
	}
	else
	{
		left_child_of_max = GetLeftChild(max_in_left_subtree);
		iter ->data = max_in_left_subtree->data;
		parent = GetParent(max_in_left_subtree);
		if(max_in_left_subtree == GetLeftChild(parent))
		{
			SetLeftChild(parent, left_child_of_max);
			SetRightChild(parent, NULL);
		}
		else
		{
			SetRightChild(parent, left_child_of_max);
		}
		
		free(max_in_left_subtree);
		
		return;
	}
	free(iter);
	iter = NULL;
	return;
}

/*will return the first valid node in InOrder search*/
bst_iter_t BSTBegin(const bst_t *bst)
{
	bst_iter_t runner  = NULL;
	assert(bst);
	runner = bst->root;
	while(NULL != GetLeftChild(runner))
	{
		runner = GetLeftChild(runner);
	}
	return runner;
}

/* returns a dummy node that if we use prev on it we get the node with the highest key val */
bst_iter_t BSTEnd(const bst_t *bst)
{
	bst_iter_t runner  = NULL;
	assert(bst);
	runner = bst->root;
	while(NULL != GetRightChild(runner))
	{
		runner = GetRightChild(runner);
	}
	return runner;	
}

/*Receives pointer to node, returns pointer to next node in InOrder tree traversal */
bst_iter_t BSTNext(const bst_iter_t iter) 
{
	bst_iter_t runner = NULL;
	bst_iter_t prev = NULL;
		
	assert(iter);
	
	runner = iter;
	while(1)
	{
		if((NULL != GetRightChild(runner)) && (prev != GetRightChild(runner)))
		{
			runner = GetRightChild(runner);
			while(NULL != GetLeftChild(runner))
			{
				runner = GetLeftChild(runner);				
			}
			return runner;
		}
		prev = runner;
		runner = GetParent(runner);
		if(prev == GetLeftChild(runner))
		{
			return runner;
		}
		if((NULL == GetParent(runner)) && (prev == GetRightChild(runner)))
		{
			break;
		}
	}
	
	return NULL;
}

/*Receives pointer to node, returns pointer to prev node in InOrder tree traversal */
bst_iter_t BSTPrev(const bst_iter_t iter)
{
	bst_iter_t runner = NULL;
	bst_iter_t prev = NULL;
	
	assert(iter);
	
	runner = iter;
	while(1)
	{
		if((NULL != GetLeftChild(runner)) && (prev != GetLeftChild(runner)))
		{
			runner = GetLeftChild(runner);
			while(NULL != GetRightChild(runner))
			{
				runner = GetRightChild(runner);				
			}
			return runner;
		}
		prev = runner;
		runner = GetParent(runner);
		if(prev == GetRightChild(runner))
		{
			return runner;
		}
		if((NULL == GetParent(runner)) && (prev == GetLeftChild(runner)))
		{
			break;		
		}
		
	}
	
	return NULL;
}




/*Compare two nodes and returns 1 if equal*/
int BSTIterIsEqual(const bst_iter_t iter1, const bst_iter_t iter2)/*O(1)*/
{
	assert(iter1);
	assert(iter2);
	return (iter1 == iter2);
	
}
/*Will get the data from the node. returns data (void *)*/
void *BSTGetData(const bst_iter_t iter)
{
	assert(iter);
	return iter->data;
	
}



/*Returns pointer to found data, else return to */
bst_iter_t BSTFind(const bst_t *bst, const void *data)/*O(n)*/
{
	bst_iter_t runner = NULL;
	int ret_val = 0;
	assert(bst);
	assert(data); 
	
	runner = TraverseTree(bst->root, (void*)data, bst->compare_func, bst->params, &ret_val);
	if(0 == ret_val)
	{
		return runner;
	}
	else 
	{
		return BSTEnd(bst);
	}
	
	
}



/*Do action to nodes in range from to */
bst_iter_t BSTForEach(bst_iter_t from, bst_iter_t to, bst_action_t action_func, void *params)
{
	bst_iter_t runner = from;
	int res = 0;
	assert(from);
	assert(to);
	assert(action_func);
	
	for(; !BSTIterIsEqual(runner, to); runner = BSTNext(runner))
	{
		res = action_func(BSTGetData(runner), params);
		if(1 == res)
		{
			return runner;
		}
		
	}
	return to;	
}

 
/*  finds the minimal value in the right sub tree of bst_iter. used in remove */
static bst_iter_t FindMaxInLeftSubTree(bst_iter_t iter)
{
	bst_iter_t runner = NULL;
	assert(iter);
	if(NULL == GetLeftChild(iter))
	{
		return iter;
	}
	runner = GetLeftChild(iter);
	while(NULL != GetRightChild(runner))
	{
		runner = GetRightChild(runner);
		
	}
	return runner;
}



/*  traverses the tree/ subtree and finds if the data exists in the tree, if exists return the iter, else return the possible parent of the data  */
static bst_iter_t TraverseTree(bst_iter_t bst_iter, void* data, bst_compare_t compare_func, void* params, int* ret_val)
{
	bst_iter_t runner = NULL;
	
	assert(bst_iter);
	runner = bst_iter;
	while(NULL != BSTGetData(runner))
	{
		if(1 == compare_func(BSTGetData(runner), data, params))
		{
			if(NULL != GetLeftChild(runner))
			{
				runner = GetLeftChild(runner);	
				continue;				
			}
			*ret_val = -1;
			return runner;
			/*  return here if the data is suppossed to be added as the left child of runner  */
			
		}
		else if(-1 == compare_func(BSTGetData(runner), data, params))
		{
			if(NULL != GetRightChild(runner))
			{
				runner = GetRightChild(runner);	
				continue;				
			}
			*ret_val = 1;
			return runner;	
			/*  return here if the data is suppossed to be added as the right child of runner  */
		}
		ret_val = 0;
		return runner; 
		/*  return here if the data is equal to runner  */
	}
	/* reached the dummy node */
	*ret_val = 1;
	return (GetParent(runner));
}



static bst_iter_t CreateNode(void* data)
{
	
	bst_iter_t temp = (bst_iter_t)malloc(sizeof(bst_node_t));
	if(NULL == temp)
	{
		return NULL;
	}
	temp->parent = NULL;
	temp->left_child = NULL;
	temp->right_child = NULL;
	temp->data = data;
	
	return 	temp;
}


static bst_iter_t GetLeftChild(bst_iter_t bst_iter)
{
	assert(bst_iter);
	
	return bst_iter->left_child;
}


static bst_iter_t GetRightChild(bst_iter_t bst_iter)
{
		
	assert(bst_iter);
	return bst_iter->right_child;

}


static bst_iter_t GetParent(bst_iter_t bst_iter)
{
	assert(bst_iter);
	
	return bst_iter->parent;

}

static void SetLeftChild(bst_iter_t parent, bst_iter_t child)
{
	assert(parent);
	
	parent->left_child = child;
	if(NULL != child)
	{
		child->parent = parent;
	}
}
static void SetRightChild(bst_iter_t parent, bst_iter_t child)
{
	assert(parent);
	if(NULL != parent->right_child)
	{
		if(BSTGetData(parent->right_child) == NULL) /* dummy node in right child*/
		{
			if(NULL == child)
			{
				return;
			}
			else
			{
				child->right_child = parent->right_child;
				child->right_child->parent = child;
				
			}
		}
	}
	parent->right_child = child;
	if(NULL != child)
	{
		child->parent = parent;
	}
	
	
}


static bst_iter_t PostOrderBegin(bst_iter_t bst_iter)
{
	assert(bst_iter);
	while((NULL != GetLeftChild(bst_iter)) || (NULL != GetRightChild(bst_iter)))
	{
		if(NULL != GetLeftChild(bst_iter))
		{
			bst_iter = GetLeftChild(bst_iter);
			continue;
		}
		bst_iter = GetRightChild(bst_iter);
	}
		return bst_iter;
}



static bst_iter_t PostOrderNext(bst_iter_t bst_iter)
{
	bst_iter_t prev = NULL;
	bst_iter_t runner = bst_iter;
	
	assert(bst_iter);
	
	while(1)
	{
		if((prev == GetRightChild(runner)) && (NULL == GetParent(runner)))
		{
			return NULL; /* end of post order traversal */
		}
		if((prev == GetLeftChild(runner)) && (NULL == GetParent(runner)) && (NULL == GetRightChild(runner)))
		{
			return NULL; /* end of post order traversal */
		}
		prev = runner;
		runner = GetParent(runner);
		if(NULL == runner)
		{
			return NULL;
		}
		if(prev == GetRightChild(runner))
		{
			return runner;
		}
		if((prev == GetLeftChild(runner)) && (NULL != GetRightChild(runner)))
		{
			return PostOrderBegin(GetRightChild(runner));			
		}
		return runner;		
	}
	
	
	
}
