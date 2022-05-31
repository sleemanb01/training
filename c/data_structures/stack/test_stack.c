/***************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : STACK
* REVIEWER NAME : 
*****************************************************/

#include <stdio.h>		/* print to */
#include <stddef.h>		/* size_t */ 
#include"stack.h"

int main()
{
	/***** Declaration *****/
	
	stack_t *stack;
	size_t element_size;
	size_t amount;
	
	int push_int = 5;
	char push_char = 'a';
	float push_float = 2.5;
	
	/***** Initializing *****/
	
	printf("** STACK **\n");
	printf("Enter elemant size\n");
	scanf("%lu",&element_size);
	printf("Enter amount of elements\n");
	scanf("%lu",&amount);
	
	stack = StackCreate(element_size, amount);
	
	/***** TESTING *****/
	
	if(StackIsEmpty(stack) == 1)
	{
		printf("** STACK IS EMPTY **\n");
	}
	printf("** STACK CAPACITY **\n");
	printf("%lu\n", StackCapacity(stack));
	printf("** STACK PUSH **\n");
	printf("5, 'a', 2.5\n");
	
	StackPush(stack ,&push_int);
	StackPush(stack ,&push_char);
	StackPush(stack ,&push_float);
	
	if(StackIsEmpty(stack) == 1)
	{
		printf("** STACK IS EMPTY **\n");
	}
	
	printf("stack Peek = %p\n", StackPeek(stack));
	printf("stack Size = %lu\n", StackSize(stack));
	printf("** STACK POP **\n");
	
	StackPop(stack);
	
	printf("stack Peek = %p\n", StackPeek(stack));
	printf("stack Size = %lu\n", StackSize(stack));
	
	StackDestroy(stack);
	
	return 0;
}
