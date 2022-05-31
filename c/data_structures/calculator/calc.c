/***************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : CALCULATOR
* REVIEWER NAME : RONEN
*****************************************************/


/***************************************************
 *                 PSEUDO CODE
 * 
 * 1 - create states enum
 * 2 - create events enum
 * 3 - create input enum
 * 4 - create handler (calculate)
 * 5 - create handlers ( num / operator)
 * 6 - loop till fail or end of string
 * 7 - create a handler and transition
 * 8 - handler sends input to the event handler
 * 9 - in number handler if operator priority higher than 2 compute it
 * 10 - free all
 * 
 *****************************************************/

#include <stdio.h>	          /* printf */
#include <stdlib.h>           /* malloc, strtod */
#include <assert.h>           /* assert */
#include <string.h>           /* strlen */
#include <ctype.h>            /* isspace */

#include "calc.h"
#include "stack.h"

#define UNUSED(x) (void)x;

/***********************************************************************************************
*                                    TYPES/STRUCTS                                      *
************************************************************************************************/

typedef enum 
{
    START,
    WAIT_NUM,
    WAIT_OPERATOR,
    WAIT_NUM_OR_SIGN,
    FAIL /* return 0.0/0.0 -nan */
}states_ty;

typedef enum 
{
    NUM_EP,
    PLUS_MINUS,
    MUL_DIV,
	PARAN
}priority_ty;

typedef enum 
{
    NUM,
    PLUS,
    MINUS,
    MUL,
    DIV,
	OPEN_PARAN,
	CLOSE_PARAN
}input_ty;

typedef struct 
{
	input_ty op;
	priority_ty priority;
}operand_ty;

typedef struct
{
    stack_t *operands;
    stack_t *operators;
}calculator_ty;

typedef struct
{
	states_ty next_state;
	void (*func)(char **start, calculator_ty *calc, input_ty curr_input);
}handler_ty;

typedef struct
{
	double (*action_func)(double double_one, double double_two);
	priority_ty priority;
}handlers_ty;
	

/***********************************************************************************************
*                                            EXTRA FUNCS                                       *
************************************************************************************************/

static calculator_ty *calcInit (size_t size);

static void calcDestroy(calculator_ty *calc, char *tmp);

static void DoNothing(char **start, calculator_ty *calc, input_ty curr_input);
static void HandleNum(char **start, calculator_ty *calc, input_ty curr_input);
static void HandleOperator(char **start, calculator_ty *calc, input_ty curr_input);

static void compute(operand_ty op, calculator_ty *calc);

static double handler(calculator_ty *calc,char *str);
static double Add(double double_one, double double_two);
static double Subtruct(double double_one, double double_two);
static double Devide(double double_one, double double_two);
static double Multiply(double double_one, double double_two);

/***********************************************************************************************
*                                         CONSTS/LUTS                                          *
************************************************************************************************/

#define NUM_OF_STATES 4
#define NUM_OF_INPUT_TYPES 5
#define NUM_OF_OP_PRIORITY 3

handler_ty states_lut[NUM_OF_OP_PRIORITY][NUM_OF_STATES] = 
{
                /*start*/                        /*WAIT NUM*/                     /*WAIT OPERATOR*/                      /*WAIT NUM OR SIGN*/
    /*NUM*/     {{WAIT_OPERATOR, &HandleNum},    {WAIT_OPERATOR, &HandleNum},     {FAIL, &DoNothing},                   {WAIT_OPERATOR, &HandleNum}},
    /* + - */   {{WAIT_NUM, &HandleOperator},    {FAIL, &DoNothing},              {WAIT_NUM_OR_SIGN, &HandleOperator},  {WAIT_NUM, &HandleOperator}},
    /* * / */   {{FAIL, &DoNothing},             {FAIL, &DoNothing},              {WAIT_NUM_OR_SIGN, &HandleOperator},  {FAIL, &DoNothing}}
};

input_ty char_lut[] = {
	(-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1),(-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1)
	,(-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1),(-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), OPEN_PARAN
	,CLOSE_PARAN, MUL, PLUS, (-1), MINUS, (-1), DIV, NUM , NUM , NUM ,NUM , NUM , NUM , NUM , NUM , NUM , NUM , (-1),(-1),(-1)
	,(-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1) ,(-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1)
	,(-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1) ,(-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1)
	,(-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1),(-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1)
	,(-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1) ,(-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1)
	,(-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1),(-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1)
	,(-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1) ,(-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1)
	,(-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1) ,(-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1)
	,(-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1),(-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1)
	,(-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1),(-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1)
	,(-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1), (-1) ,(-1), (-1), (-1), (-1), (-1), (-1)
};

handlers_ty input_lut[NUM_OF_INPUT_TYPES] = 
{
        {NULL, NUM_EP}, {&Add, PLUS_MINUS}, {&Subtruct, PLUS_MINUS},{&Multiply, MUL_DIV},{&Devide, MUL_DIV}
};

/************************************************************************************************
*                   CREATE     
*  Parameters:      string pointer
*  Return    :      calculated value to the operands with operators within
*  Complexity:      O(n^2)
************************************************************************************************/

double CalcCulate(const char *str)
{
	calculator_ty *new = NULL;
	double ret = 0.0;
	char *tmp = NULL;

	tmp = (char*)malloc(strlen(str) + 1);

	assert(NULL != str);

	strcpy(tmp,str);

	UNUSED(str);

	new = calcInit(strlen(tmp));

	ret = handler(new,tmp);

	calcDestroy(new,tmp);

	return ret;
}

/************************************************************************************************
*                   INITIALIZE     
*  Parameters:      size
*  Return    :      calculator type pointer
*  Complexity:      O(1)
************************************************************************************************/

static calculator_ty *calcInit (size_t size)
{
	calculator_ty *new = NULL;
	stack_t *num_stack = NULL;
	stack_t *op_stack = NULL;

	assert(0 < size);

	do
	{
		new = (calculator_ty*)malloc(sizeof(calculator_ty));
		if(NULL == new)
		{
			break;
		}

		num_stack = StackCreate(sizeof(double), size);
		if(NULL == num_stack)
		{
			break;
		}

		op_stack = StackCreate(sizeof(operand_ty), size);
		if(NULL == op_stack)
		{
			break;
		}

		new->operands = num_stack;
		new->operators = op_stack;

		return new;

	} while (0);
	
	free(new);
	free(num_stack);
	
	return NULL;
}

/************************************************************************************************
*                   DESTROY    
*  Parameters:      calculator type
*  Return    :      VOID
*  Complexity:      O(1)
************************************************************************************************/

static void calcDestroy(calculator_ty *calc, char *tmp)
{
	assert(NULL != calc);

	StackDestroy(calc->operands);
	StackDestroy(calc->operators);
	free(calc);
	free(tmp);
}

/************************************************************************************************
*                   NOTHING    
*  Parameters:      char pointer, calc type, current input enum
*  Return    :      VOID
*  Complexity:      O(1)
************************************************************************************************/

static void DoNothing(char **start, calculator_ty *calc, input_ty curr_input)
{
    UNUSED(start);
    UNUSED(calc);
    UNUSED(curr_input);
}

/************************************************************************************************
*                   HANDLER
*  Parameters:      calculator type, string
*  Return    :      double
*  Complexity:      O(n)
************************************************************************************************/

static double handler(calculator_ty *calc, char *str)
{
   states_ty curr_state = START;
   handler_ty transition;
   input_ty curr_input = 0;
   operand_ty op;
   double result = 0.0;

   while(('\0' != *str) && FAIL != curr_state)
   {
	   while(isspace(str[0]))
	   {
		   ++str;
	   }
	   curr_input = char_lut[(input_ty)str[0]];
	   transition = states_lut[ input_lut[curr_input].priority ][curr_state];
	   transition.func(&str, calc, curr_input);
	   curr_state = transition.next_state;
   }

   while(!StackIsEmpty(calc->operators))
   {
		op = *(operand_ty*)StackPeek(calc->operators);
		StackPop(calc->operators);
		compute(op,calc);
   }

	result = *(double*)StackPeek(calc->operands);

	StackPop(calc->operators);

	return result;
}

/************************************************************************************************
*                   Handle Number
*  Parameters:      char pointer, calc type, current input enum
*  Return    :      VOID
*  Complexity:      O(1)
************************************************************************************************/

static void HandleNum(char **start, calculator_ty *calc, input_ty curr_input)
{
	double num = 0.0;
	char *end = NULL;
	operand_ty op;

	UNUSED(curr_input);

	assert(NULL != calc);
	assert(NULL != start);

	num = strtod(*start,&end);

	*start = end;

	StackPush(calc->operands,&num);

	if(0 < StackSize(calc->operators))
	{
		op = *(operand_ty*)StackPeek(calc->operators);
		if(1 < op.priority)
		{	
			StackPop(calc->operators);
			compute(op,calc);
		}
	}
}

/************************************************************************************************
*                   Handle Operator    
*  Parameters:      char pointer, calc type, current input enum
*  Return    :      VOID
*  Complexity:      O(1)
************************************************************************************************/

static void HandleOperator(char **start, calculator_ty *calc, input_ty curr_input)
{
	operand_ty op;
	
	assert(NULL != calc);
	assert(NULL != start);

	op.op = curr_input;
	op.priority = input_lut[curr_input].priority;
	++*start;

	StackPush(calc->operators,&op);
}

/************************************************************************************************
*                  CALC    
*  Parameters:      2 doubles, operator type
*  Return    :      value
*  Complexity:      O(1)
************************************************************************************************/

static void compute(operand_ty op, calculator_ty *calc)
{
		double num1,num2;
		handlers_ty op_handler;

		num2 = *(double*)StackPeek(calc->operands);
		StackPop(calc->operands);
		num1 = *(double*)StackPeek(calc->operands);
		StackPop(calc->operands);

		op_handler = input_lut[op.op];
		num1 = op_handler.action_func(num1,num2);

		StackPush(calc->operands,&num1);
}

/************************************************************************************************
*                  Add    
*  Parameters:      2 doubles
*  Return    :      value
*  Complexity:      O(1)
************************************************************************************************/

static double Add(double double_one, double double_two)
{
	return double_one + double_two;
}

/************************************************************************************************
*                  Subtruct    
*  Parameters:      2 doubles
*  Return    :      value
*  Complexity:      O(1)
************************************************************************************************/

static double Subtruct(double double_one, double double_two)
{
	return double_one - double_two;
}

/************************************************************************************************
*                  Devide    
*  Parameters:      2 doubles
*  Return    :      value
*  Complexity:      O(1)
************************************************************************************************/

static double Devide(double double_one, double double_two)
{
	return double_one / double_two;
}

/************************************************************************************************
*                  Multiply    
*  Parameters:      2 doubles
*  Return    :      value
*  Complexity:      O(1)
************************************************************************************************/

static double Multiply(double double_one, double double_two)
{
	return double_one * double_two;
}