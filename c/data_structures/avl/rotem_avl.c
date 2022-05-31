#include <stddef.h>	/*size_t*/
#include <stdlib.h> /*malloc, free*/
#include <assert.h>

#include "avl.h"
#include "dlist.h"

#define UNUSED(x) (void)(x)

struct avl
{
    avl_node_ty *root;
    avl_compare_ty compare; 
    void* params;
};

typedef enum {NO_CHILD = -1, LEFT, RIGHT, CHILDREN_NUM} children_ty;

struct avl_node
{
    void *data;
    avl_node_ty *children[CHILDREN_NUM];
    size_t height;
};


static int PostOrderImp(avl_node_ty *node, avl_action_ty action_func, void *params);
static int InOrderImp(avl_node_ty *node, avl_action_ty action_func, void *params);
static int PreOrderImp(avl_node_ty *node, avl_action_ty action_func, void *params);
static children_ty GetChildren(avl_node_ty *node);
static avl_node_ty *InsertImp(avl_node_ty *node, avl_node_ty *new_node, avl_compare_ty compare_func, void *params);
static avl_node_ty *FindImp(avl_node_ty *node ,const void *data, avl_compare_ty compare_func, void *params);
static avl_node_ty *RemoveImp(avl_node_ty *node, void *data, avl_compare_ty compare_func, void *params);
static children_ty WhichWay(const void *data, const void *to_compare, avl_compare_ty compare_func, void *params);
static int FreeFunc(void *node, void *params);
static avl_node_ty *CreateNode(void *data);
static void UpdateHeight(avl_node_ty *node);
static int CountFunc(void *node, void *params);
static avl_node_ty *GetLargest(avl_node_ty *node);
static int ActionHandler(avl_node_ty *node, avl_action_ty action_func, void *params, void *parms2);
static avl_node_ty *Balance(avl_node_ty *node);
static int GetBalance(avl_node_ty *node);
static avl_node_ty *RotateRight(avl_node_ty *node);
static avl_node_ty *RotateLeft(avl_node_ty *node);
static int RTInOrderImp(avl_node_ty *node, avl_find_if_ty func, avl_action_ty action_func, void *data, void *params, void *param2);

/*create an avl tree*/
avl_ty *AVLCreate(avl_compare_ty compare_func, void* params)
{
    /*init varubles*/
    avl_ty *new_tree = NULL;

    /*assert*/
    assert(NULL != compare_func);
    
    /*allocate space for tree and check allocation*/
    new_tree = malloc(sizeof(avl_ty));

    if(NULL == new_tree)
    {   
        return NULL;
    }
    /*init vars of avl tree*/

    new_tree->root = NULL;
    new_tree->compare = compare_func;
    new_tree->params = params;

    return new_tree;
}

void AVLDestroy(avl_ty *this)
{
    /*assert*/
    assert(NULL != this);

    /*itereate tree in post order and free nodes*/
    PostOrderImp(this->root, FreeFunc, this->params);

    /*free tree*/
    free(this);
}   

void AVLRemove(avl_ty *this, void *data)
{
    /*assert*/
    assert(this);

    /* update root using RemoveImple*/
    this->root = RemoveImp(this->root , data, this->compare, this->params);
}

int AVLInsert(avl_ty *this, void *data)
{
    /*init vars*/
    avl_node_ty *new_node = NULL;

    /*assert*/
    assert(this);

    /*create new node with data and init node return 1 if fail*/
    new_node = CreateNode(data);

    if(NULL == new_node)
    {
        return 1;
    }

    /*call InsertImp(root, new_node, compare_func)*/
    this->root = InsertImp(this->root, new_node, this->compare, this->params);

    /*return no problems (0)*/
    return 0;
}

size_t AVLHeight(avl_ty *this)
{
    /*assert*/
    assert(NULL != this);

    if(NULL == this->root)
    {
        return 0;
    }
    /*return root height*/
    return this->root->height;
}

size_t AVLSize(const avl_ty *this)
{
    /*init counter var*/
    size_t counter = 0;
    /*assert*/
    assert(this);

    /*call in/post/pre order + count func*/
    InOrderImp(this->root , &CountFunc, &counter);

    return counter;
}

int AVLIsEmpty(const avl_ty *this)
{
    /*assert*/
    assert(NULL != this);

    /*return root = null*/
    return this->root == NULL;
}

void *AVLFind(const avl_ty *this, const void *data)
{
    /*init var for returned node*/
    avl_node_ty *node = NULL;

    /*assert*/
    assert(NULL != this);
    
    /*call FindImp(this->root, data, comp_func)*/
    node = FindImp(this->root, data, this->compare, this->params);

    /*return node data*/
    return node->data;
}

int AVLForEach(const avl_ty *this, avl_action_ty action_func, void *params, order_ty order)
{
    /*assert*/
    assert(NULL != this);
    
    /*swhic case by order*/
    switch(order)
    {    
        /*for every case call the correct order func( this->root, action func, params )*/
        /*return the returned value from the funcs (0 for ok, 1 for fail)*/
        case PRE:
        {
            return PreOrderImp(this->root, action_func, params);
            break;
        }

        case IN:
        {
            return InOrderImp(this->root, action_func, params);
            break;
        }

        case POST:
        {
            return PostOrderImp(this->root, action_func, params);
            break;
        }
    }
    return 1;
}


/*---------------------------------------ADVANCED---------------------------------------*/

void AVLRTreeForeach(const avl_ty *this, dlist_t *dlist, avl_find_if_ty func, void *data, void *params)
{
    RTInOrderImp(this->root, func, NULL, data, params, dlist);
}

size_t AVLRTreeRemoveMultiple(const avl_ty *this, avl_find_if_ty func, void *data, void *params)
{
    size_t counter = 0;
    RTInOrderImp(this->root, func, FreeFunc, data, params, &counter);
    return counter;
}
     

static int RTInOrderImp(avl_node_ty *node, avl_find_if_ty func, avl_action_ty action_func, void *data, void *params, void *param2)
{
    /*base case*/
    /*if null return 0*/
    if(NULL == node)
    {
        return 0;
    }

    /*iterate left stop if action fail*/
    if(1 == RTInOrderImp(node->children[LEFT], func, action_func, data, params, param2))
    {
        return 1;
    }
    
    /*preform action*/
     if(func(data, node->data, params))
    {
        if(1 == ActionHandler(node, action_func, params, param2))
        {
            return 1;
        }
    }

    /*iterate right stop if action fail*/
    return RTInOrderImp(node->children[RIGHT], func, action_func, data, params, param2);
    
    return 0;
}

static int FreeFunc(void *node, void *params)
{
    free((avl_node_ty *)node);
    if(NULL != params)
    {
        ++*(size_t *)params;
    }
    return 0;
}

/*iterarate avl in post order and preform action func on every node (returns 0 if operated properly*/
static int PostOrderImp(avl_node_ty *node, avl_action_ty action_func, void *params)
{
    /*base case*/
    /*if null return 0*/
    if(NULL == node)
    {
        return 0;
    }

    /*iterate left stop if action fail*/
    if(1 == PostOrderImp(node->children[LEFT], action_func, params))
    {
        return 1;
    }

    /*iterate right stop if action fail*/
    if(1 == PostOrderImp(node->children[RIGHT], action_func, params))
    {
        return 1;
    }

    /*return preform action*/
     return ActionHandler(node, action_func, params, NULL);
}

static int InOrderImp(avl_node_ty *node, avl_action_ty action_func, void *params)
{
    /*base case*/
    /*if null return 0*/
    if(NULL == node)
    {
        return 0;
    }

    /*iterate left stop if action fail*/
    if(1 == InOrderImp(node->children[LEFT], action_func, params))
    {
        return 1;
    }
    
    /*preform action*/
    if(1 == ActionHandler(node, action_func, params, NULL))
    {
        return 1;
    }

    /*iterate right stop if action fail*/
    return InOrderImp(node->children[RIGHT], action_func, params);
}

static int PreOrderImp(avl_node_ty *node, avl_action_ty action_func, void *params)
{
    /*base case*/
    /*if null return 0*/
    if(NULL == node)
    {
        return 0;
    }

    /*preform action*/
    if(1 == ActionHandler(node, action_func, params, NULL))
    {
        return 1;
    }

    /*iterate left stop if action fail*/
    if(1 == PreOrderImp(node->children[LEFT], action_func, params))
    {
        return 1;
    }
    
    /*iterate right stop if action fail*/
    return PreOrderImp(node->children[RIGHT], action_func, params);
}

static children_ty GetChildren(avl_node_ty *node)
{
    if(node->children[LEFT] == NULL && node->children[RIGHT] != NULL)
    {
        return RIGHT;
    }

    if(node->children[LEFT] != NULL && node->children[RIGHT] == NULL)
    {
        return LEFT;
    }

    if(node->children[LEFT] != NULL && node->children[RIGHT] != NULL)
    {
        return CHILDREN_NUM;
    }

    return -1;
}

static avl_node_ty *CreateNode(void *data)
{
    avl_node_ty *new_node = NULL;

    new_node = malloc(sizeof(avl_node_ty));

    if(NULL == new_node)
    {
        return NULL;
    }
    new_node->data = data;
    new_node->children[LEFT] = NULL;
    new_node->children[RIGHT] = NULL;
    new_node->height = 1;
    
    return new_node;

}

static avl_node_ty *InsertImp(avl_node_ty *node, avl_node_ty *new_node, avl_compare_ty compare_func, void *params)
{
    /*init next_child (children_ty)*/
    children_ty next_child = -1;

    /*base*/
    /*if null return newnode*/
    if(NULL == node)
    {
        return new_node;
    }

    /*next_child = call WhichWay using  node, new_node, compare_func, params)*/
    next_child = WhichWay(new_node->data , node->data , compare_func, params);

    /*assert next_chiled not NO_CHILD (node already in)*/
    assert(NO_CHILD != next_child);

    /*update node child with return of InsertImp with node child and new node*/
    node->children[next_child] = InsertImp(node->children[next_child], new_node, compare_func, params);

    /*update node height*/
    UpdateHeight(node);

    /*rebalance tree*/
    node = Balance(node);

    /*return node*/
    return node;
}

static void UpdateHeight(avl_node_ty *node)
{
    size_t height = 1;

    if(NULL != node->children[RIGHT])
    {
        height = node->children[RIGHT]->height + 1;
    }

    if(NULL != node->children[LEFT])
    {
        if(height <= node->children[LEFT]->height)
        {
            height = node->children[LEFT]->height+1;
        }
    }
    node->height = height;
}

static avl_node_ty *RemoveImp(avl_node_ty *node, void *data, avl_compare_ty compare_func, void *params)
{
    /*init next_child, replacment node, node_to_delete*/
    children_ty next_child = -1;
    avl_node_ty *replacment = NULL; 
    /*if node is null return null*/
    if(NULL == node)
    {
        return NULL;
    }
        
    /*next_child = call which way using  node, data , compare_func, params)*/
    next_child = WhichWay(data, node->data, compare_func, params);

    /*if not NO_CHILD (deleted node not found) - continue*/
    if(NO_CHILD != (int)next_child)
    {
        /*update node child with return of RemoveImp with node child and new node*/
        node->children[next_child] = RemoveImp(node->children[next_child] , data, compare_func, params);
    }

    /*else - (is node to be deleted) find a suitable child node to replace it*/
    else
    {
        /*check children*/
        switch (GetChildren(node))
        {
            /* if leaf, remove node return null*/
            case NO_CHILD:
            {
                free(node);
                return NULL;
            }

             /* if only right child delete node return child*/
            case RIGHT:
            {
                replacment = node->children[RIGHT];
                free(node);
                return replacment;
            }
             /* if only left child delete node return child*/
            case LEFT:
            {
                replacment = node->children[LEFT];
                free(node);
                return replacment;
            }
            /* if both children exist*/
            case CHILDREN_NUM:
            {
                /* get predessesor*/
                replacment = GetLargest(node->children[LEFT]);

                /*replace data with predessesor*/
                node->data = replacment->data;

                /*delete the replaced node*/
                node->children[LEFT] = RemoveImp(node->children[LEFT], node->data, compare_func, params);
            }
        }
    }

    /*rebalance tree*/
    node = Balance(node);
    
    /*update height */
    UpdateHeight(node);

    /*return node*/
    return node;
}

static avl_node_ty *GetLargest(avl_node_ty *node)
{
    if(NULL == node->children[RIGHT])
    {
        return node;
    }

    return GetLargest(node->children[RIGHT]);
}

static children_ty WhichWay(const void *data,const void *to_compare, avl_compare_ty compare_func, void *params)
{
    /*swhich case by compare_func of node and node2*/
    /*return right or left or -1 if nodes are equal*/
    switch(compare_func(data , to_compare, params))
    {
        case 1:
        {
            return RIGHT;
        }

        case -1:
        {
            return  LEFT;
        }
    }

    return NO_CHILD;
}

static int CountFunc(void *node, void *params)
{
    UNUSED(node);
    ++*(size_t *)params;
    return 0;
}

static avl_node_ty *FindImp(avl_node_ty *node ,const void *data, avl_compare_ty compare_func, void *params)
{
    /*init next_child*/
    children_ty next_child = -1;
    /*if base - null return null*/
    if(NULL == node)
    {
        return NULL;
    }

    /*next_child = call which way using  node, new_node, compare_func, params)*/
    next_child = WhichWay(data, node->data, compare_func, params);

    /*if next_chiled equals -1 - chiled was found return node*/
    if(-1 == next_child)
    {
        return node;
    }

    /*return FindImp with next child*/
    return FindImp(node->children[next_child] , data,  compare_func, params);
}

static int ActionHandler(avl_node_ty *node, avl_action_ty action_func, void *params, void *parms2)
{
    if(FreeFunc == action_func)
    {
       return FreeFunc(node, parms2);
    }

    else if(NULL != parms2)
    {
        DlistInsert(DlistEnd((dlist_t *)parms2), node->data);
        /*return action_func(node->data, params);*/
        return 0;
    }

    return action_func(node->data, params);
}

static avl_node_ty *Balance(avl_node_ty *node)
{
    avl_node_ty *new_parent = NULL;
    int balance = 0;
    int child_balance = 0;

    /*check if balance larger than |1|*/
    balance = GetBalance(node);

    if(balance <= -2 || balance >= 2)
    {
        /*check which side is heavier*/
        
        /*if left is heavier*/
        if(balance > 0)
        {
            child_balance = GetBalance(node->children[LEFT]);
            /*if child left is heavier*/
            if(child_balance > 0)
            {
                /*rotate right*/
                new_parent = RotateRight(node);
            }

            /*if right child is heavier*/
            else
            {
                /*left rotate*/
                node->children[LEFT] = RotateLeft(node->children[LEFT]);
                /*right rotate*/
                new_parent = RotateRight(node);
            }
        } 
        
        /*if right is heavier*/
        else
        {
            child_balance = GetBalance(node->children[RIGHT]);

            /*if child left is heavier*/
            if(balance > 0)
            {
                /*rotate right*/
                node->children[RIGHT] = RotateRight(node->children[RIGHT]);
                /*left rotate*/
                new_parent = RotateLeft(node);
            }
            /*if right child is heavier*/
            else
            {
                /*left rotate*/
                new_parent = RotateLeft(node);
            }
        }
        return new_parent;
    }
    return node;
}

static int GetBalance(avl_node_ty *node)
{
    int left = 0;
    int right = 0;

    if(node->children[LEFT] == NULL)
    {
        left = 0;
    }
    else
    {
        left = node->children[LEFT]->height;
    }

    if(node->children[RIGHT] == NULL)
    {
        right = 0;
    }
    else
    {
        right = node->children[RIGHT]->height;
    }

    return left - right;
}

static avl_node_ty *RotateRight(avl_node_ty *node)
{
    avl_node_ty *temp = NULL;
    avl_node_ty *new_parant = NULL;

    new_parant = node->children[LEFT];

    temp = new_parant->children[RIGHT];

    new_parant->children[RIGHT] = node;

    node->children[LEFT] = temp;

    UpdateHeight(node);

    return new_parant;
}

static avl_node_ty *RotateLeft(avl_node_ty *node)
{
    avl_node_ty *temp = NULL;
    avl_node_ty *new_parant = NULL;

    new_parant = node->children[RIGHT];

    temp = new_parant->children[LEFT];

    new_parant->children[LEFT] = node;

    node->children[RIGHT] = temp;

    UpdateHeight(node);

    return new_parant;
}

