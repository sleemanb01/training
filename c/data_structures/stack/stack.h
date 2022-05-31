#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h>

typedef struct stack
{
	void *stack_arr;
	void *top;
	size_t amount;
	size_t element_size;
}stack_t;

/* Description: creates a stack DS*/
/*Errors: malloc can return NULL if failed*/
/* Parameters: element_size - the size of each item in the stack*/
/*amount - number of items to be stored on the stack*/
/* Return value: pointer to stack DS*/
/* Complexity: O(1)*/

stack_t *StackCreate(size_t element_size ,size_t amount);

/* Description: destroy stack DS*/
/* Errors: */
/* Parameters: stack DS pointer*/
/* Return value: none*/
/* Complexity: O(1)*/
void StackDestroy(stack_t *stack);

/* Description: */
/* Errors: */
/* Parameters: */
/* Return value: */
/* Complexity: */
int StackIsEmpty(const stack_t *stack);

/* Description: */
/* Errors: */
/* Parameters: */
/* Return value: */
/* Complexity: */
void StackPush(stack_t *stack, void *item);

/* Description: */
/* Errors: */
/* Parameters: */
/* Return value: */
/* Complexity: */
void StackPop(stack_t *stack);

/* Description: */
/* Errors: */
/* Parameters: */
/* Return value: */
/* Complexity: */
void *StackPeek(const stack_t *stack);

/* Description: */
/* Errors: */
/* Parameters: */
/* Return value: */
/* Complexity: */
size_t StackSize(const stack_t *stack);

/* Description: */
/* Errors: */
/* Parameters: */
/* Return value: */
/* Complexity: */
size_t StackCapacity(const stack_t *stack);

#endif
