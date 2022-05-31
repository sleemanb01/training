#ifndef __HASH_H__
#define __HASH_H__

/*Version 3: is_match function (1=match/0=no-match) instead of compare_func*/

#include <stddef.h> /*size_t*/
#include "dlist.h"

typedef struct hash hash_ty;
typedef size_t (*hash_func_ty)(const void *data);

/*Checks for match between data_a and data_b (returns 1/0 for match/no-match)*/
typedef int (*is_match_ty)(const void *data_a, const void *data_b); 

/*Action function: performs operation on data (returns 0/1 for success/failure)*/
typedef int (*hash_action_ty)(void *data, void *params);


/*creates a hash table with given array size, index generation function, and comparison function (returns pointer to has table/NULL for success/failure*/
hash_ty *HashCreate(size_t size, hash_func_ty func, is_match_ty compare_func);/*O(1)*/

/*destroys hash table*/
void HashDestroy(hash_ty *this);/*O(n)*/

/*Removes data from hash table*/
void HashRemove(hash_ty *this, const void* data);/* AVG O(1)*/

/*Insert new data to hash table: returns 0/1 for success/failure*/
int HashInsert(hash_ty *this, void* data);/*O(1)*/

/*Returns number of nodes in the hash table*/
size_t HashSize(const hash_ty *this);/*O(1)*/

/*Returns 1/0 if empty/not empty*/
int HashIsEmpty(const hash_ty *this);/*O(1)*/

/* returns the data of key, NULL otherwise */
void *HashFind(const hash_ty *this, const void* data);

/*Performs action function (using param) on every node in hash table (returns 0/1 for success/failure)*/
int HashForEach(const hash_ty *hash_table, hash_action_ty action_func, void * param);

#endif
