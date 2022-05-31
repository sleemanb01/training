/***************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : STACK
* REVIEWER NAME : 
*****************************************************/

#include<stdio.h>	         /* printכ */
#include<stddef.h>	         /* size_t */ 
#include<stdlib.h>           /* malloc */
#include<string.h>           /* memcpy */
#include <assert.h>          /* memcpy */
#include"stack.h"

/****** creates a stack DS *****/
stack_t *StackCreate(size_t element_size ,size_t amount)
{
	stack_t *stack = (void *)malloc((element_size * amount) + (3 * sizeof(void *)));
	void *stack_arr = (void *)malloc(element_size * amount);
	if(NULL != stack_arr)
	{
		stack->stack_arr = stack_arr;
		stack->top = stack_arr;
		stack->amount = amount;
		stack->element_size = element_size;
	}
	else
	{
		printf("** MALLOC ERROR **\n");
		return NULL;
	}
	
	return stack;
}

/****** destroy stack DS *****/
void StackDestroy(stack_t *stack)
{
	free(stack->stack_arr);
	free(stack);
}

/****** check if stack is empty *****/
int StackIsEmpty(const stack_t *stack)
{
	if((*(int *)(stack->top) - *(int *)(stack->stack_arr)) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/****** Push element to stack *****/
void StackPush(stack_t *stack, void *item)
{                                              
	
	assert(NULL != stack);
	assert(NULL != item);
	assert(StackSize(stack) < StackCapacity(stack));

	stack->top = memmove ((void*)((char*)stack->top + stack->element_size), item, stack->element_size);

}

/****** Pop element from stack *****/
void StackPop(stack_t *stack)
{

	assert(NULL != stack);
	assert(stack->amount > 0);
	stack->top = (void*)((char*)(stack->top) - stack->element_size);
}

/****** returns pointer to stack last element *****/
void *StackPeek(const stack_t *stack)
{
	return stack->top;
}

/****** return the size left on the stack *****/
size_t StackSize(const stack_t *stack)
{
	return (((char*)(stack->top) - (char*)(stack->stack_arr))/stack->element_size);
}

/****** return the size of the stack *****/
size_t StackCapacity(const stack_t *stack)
{
	/*return ((stack->element_size) * (stack->amount));*/
	return stack->amount;
}
