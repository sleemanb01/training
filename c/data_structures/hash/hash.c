/************************************************************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : HASH TABLE
* REVIEWER NAME : NOA
************************************************************************************************/

#include <stddef.h>	         /* size_t */ 
#include <stdlib.h>          /* malloc */
#include <assert.h>          /* assert */
#include <stdio.h>

#include "hash.h"

/***********************************************************************************************
*                                      STRCUCTS/TYPES                                          *
************************************************************************************************/

struct hash
{
    dlist_t **hash_table;
    size_t size;
    size_t capacity;
    is_match_ty compare_func;
    hash_func_ty func;
};

struct dlist_node
{
    void *data;
    dlist_node_t *next;
    dlist_node_t *prev;
};

struct dlist
{
    dlist_node_t head;
    dlist_node_t tail;
};

/***********************************************************************************************
*                                            EXTRA FUNCS                                       *
************************************************************************************************/


/************************************************************************************************
*                   CREATE     
*  Parameters:      size, hash func, compare func
*  Return    :      pointer to has table/NULL for success/failure
*  Complexity:      O(1)
************************************************************************************************/
hash_ty *HashCreate(size_t size, hash_func_ty func, is_match_ty compare_func)
{
    size_t i;
    hash_ty *new = NULL;
    dlist_t **table = NULL;
    
	assert(0 < size);
	assert(NULL != func);
    assert(NULL != compare_func);

    do
    {
       new = (hash_ty*)malloc(sizeof(hash_ty));
       if(NULL == new)
       {
           break;
       }

       table = (dlist_t**)calloc(size, sizeof(dlist_t*));
       if(NULL == table)
       {
           break;
       }
       for(i = 0; i < size; ++i)
       {
           table[i] = NULL;
       }

       new->hash_table = table;
       new->compare_func = compare_func;
       new->func = func;
       new->size = 0;
       new->capacity = size;

       return new; 

    } while (0);

    free(new);
    free(table);
    return NULL;
        
}

/************************************************************************************************
*                   DESTROY     
*  Parameters:      hash table
*  Return    :      void
*  Complexity:      O(n)
************************************************************************************************/
void HashDestroy(hash_ty *this)
{
    size_t i;

    assert(NULL != this);

    for(i = 0; i < this->capacity ; ++i)
    {
        DlistDestroy(this->hash_table[i]);
    }

    free(this->hash_table);
    free(this);
}

/************************************************************************************************
*                   REMOVE     
*  Parameters:      hash table, data
*  Return    :      void
*  Complexity:      AVG O(1)
************************************************************************************************/
void HashRemove(hash_ty *this, const void* data)
{
    dlist_t *target_list = NULL;
    dlist_iter_t dlist_iter = NULL;

    assert(NULL != this);

    target_list = this->hash_table[this->func(data)];

    dlist_iter = DlistFind(DlistBegin(target_list),DlistEnd(target_list), data , this->compare_func);

    DlistRemove(dlist_iter);

    --this->size;
}

/************************************************************************************************
*                   INSERT     
*  Parameters:      hash table, data
*  Return    :      0/1 for success/failure
*  Complexity:      O(1)
************************************************************************************************/
int HashInsert(hash_ty *this, void* data)
{
    int res;
    size_t index;
    dlist_t *dlist = NULL;

    assert(NULL != this);

    index = this->func(data);

    if(NULL == this->hash_table[index])
    {
        dlist = DlistCreate();
        this->hash_table[index] = dlist;
    }
    else
    {
        dlist = this->hash_table[index];
    }

    res = DlistInsert(DlistEnd(dlist), data);

    if(!res)
    {
        ++this->size;
    }

    return (res);
}

/************************************************************************************************
*                   SIZE     
*  Parameters:      hash table
*  Return    :      number of nodes in the hash table
*  Complexity:      O(1)
************************************************************************************************/
size_t HashSize(const hash_ty *this)
{
    assert(NULL != this);

    return(this->size);
}

/************************************************************************************************
*                   IS EMPTY     
*  Parameters:      hash table
*  Return    :      1/0 if empty/not empty
*  Complexity:      O(1)
************************************************************************************************/
int HashIsEmpty(const hash_ty *this)
{
    assert(NULL != this);

    return(HashSize(this) == 0);
}

/************************************************************************************************
*                   FIND     
*  Parameters:      hash table, data
*  Return    :      dlist_node->data
*  Complexity:      O(1)
************************************************************************************************/
void *HashFind(const hash_ty *this, const void* data)
{
    size_t index;
    dlist_t *target_list = NULL;
    dlist_iter_t dlist_iter = NULL;

    assert(NULL != this);
    assert(NULL != data);

    index = this->func(data);

    target_list = this->hash_table[index];
    dlist_iter = DlistFind(DlistBegin(target_list),DlistEnd(target_list), data , this->compare_func);

    if(DlistIsSameIter(dlist_iter,DlistEnd(target_list)))
    {
        return NULL;
    }

    return(DlistGetData(dlist_iter));

}

/************************************************************************************************
*                   FOR EACH     
*  Parameters:      hash table, action func, param
*  Return    :      0/1 for success/failure
*  Complexity:      O(1)
************************************************************************************************/
int HashForEach(const hash_ty *hash_table, hash_action_ty action_func, void * param)
{
    int res = 0;
    size_t i;
    dlist_t *target_list = NULL;
    dlist_iter_t dlist_end = NULL;
    dlist_iter_t dlist_foreach_iter = NULL;

    assert(NULL != hash_table);
    assert(NULL != param);

    for(i = 0; i < hash_table->capacity ; ++i)
    {
        target_list = hash_table->hash_table[i];
        dlist_end = DlistEnd(target_list);
        dlist_foreach_iter = DlistForEach(DlistBegin(target_list),DlistEnd(target_list) ,action_func, param);

        if(!DlistIsSameIter(dlist_end,dlist_foreach_iter))
        {
            res = 1;
        }
    }

    return res;
}