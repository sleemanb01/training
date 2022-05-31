/************************************************************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : KNIGHT
* REVIEWER NAME : 
************************************************************************************************/

#include <stddef.h>	         /* size_t    */ 
#include <stdlib.h>          /* malloc    */
#include <assert.h>          /* assert    */
#include <math.h>            /* pow,sqrt  */
#include <time.h>            /* clock     */
#include <stdio.h>

#include "knight.h"

/***********************************************************************************************
*                                      STRCUCTS/CONSTS                                          *
************************************************************************************************/

#define AVAILABLE_STEPS 8

typedef enum boolean_ty{FALSE,TRUE}boolean_ty;

position_ty one_step[AVAILABLE_STEPS] = {	{1,2}, {1,-2}, {-1,2}, {-1,-2}, {2,1}, {2,-1}, {-2,1}, {-2,-1}	};

/***********************************************************************************************
*                                            EXTRA FUNCS                                       *
************************************************************************************************/

static boolean_ty IsVisited(position_ty pos, size_t visited);
static boolean_ty IsValidMove(position_ty *pos, position_ty step, size_t visited);

static void ReverseStepFromPosition(position_ty *pos, position_ty one_step);

static return_ty KnightBackTracking(position_ty pos, position_ty steps[], size_t counter, clock_t start, size_t visited);


static size_t SetBitOn(size_t visited, size_t index);
static size_t SetBitOff(size_t visited, size_t index);

/************************************************************************************************
*  Name:            KnightTour
*  Description:     Create a steps LUT
*  Parameters:      current position, steps LUT, number of row, number of columns
*  Return    :      Pointer to newly created DHCP structure
*  Complexity:      O(n!)
************************************************************************************************/

return_ty KnightTour(position_ty start_pos, position_ty steps[BOARD_SIZE])
{
	clock_t start_t;
	size_t visited = 0;

	start_t = clock();

	return KnightBackTracking(start_pos,steps, 0, start_t, visited);
}

/***********************************************************************************************
*                                            EXTRA FUNCS                                       *
************************************************************************************************/

/******************************* BACKTRACING *********************************/
static return_ty KnightBackTracking(position_ty pos, position_ty steps[], size_t counter, clock_t start, size_t visited)
{
	size_t i;
	clock_t exec;

	exec = clock();

	if (360.0 < (double)(exec - start) / CLOCKS_PER_SEC)
    {
        return TIME_OUT;
    }

		if((BOARD_SIZE - 1) == counter)
		{
			return SUCCESS;
		}

		for(i = 0; i < AVAILABLE_STEPS; ++i)
		{
			if(IsValidMove(&pos,one_step[i], visited))
			{
				size_t index = ((pos.row * (sqrt(BOARD_SIZE)) + pos.col));
				visited = SetBitOn(visited,index);
				steps[counter] = pos;
				
					/* ! because SUCCESS VALUE IS 0 */
				if(!KnightBackTracking(pos,steps,counter + 1, start, visited))  
				{
					return SUCCESS;
				}
				/*FAIL*/
				ReverseStepFromPosition(&pos,one_step[i]);
				visited = SetBitOff(visited,index);
				--counter;
			}
		}
	return FAIL;
}

/******************************* IsValidMove *********************************/
static boolean_ty IsValidMove(position_ty *pos, position_ty one_step, size_t visited)
{
	int max = sqrt(BOARD_SIZE);

	if((0 < (pos->col + one_step.col)) && 
		(0 < (pos->row + one_step.row)) &&
		(max > (pos->col + one_step.col)) && 
		(max > (pos->row + one_step.row)) )
	{
		pos->col += one_step.col;
		pos->row += one_step.row;

		if(IsVisited(*pos, visited))
		{
			pos->col -= one_step.col;
			pos->row -= one_step.row;

			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}

	return FALSE;
}

/******************************* IsValidMove *********************************/
static void ReverseStepFromPosition(position_ty *pos, position_ty one_step)
{
	pos->col -= one_step.col;
	pos->row -= one_step.row;
}

/******************************* IsValidMove *********************************/
static boolean_ty IsVisited(position_ty pos, size_t visited)
{
	size_t index;

	index = ((pos.row * (sqrt(BOARD_SIZE)) + pos.col));

	return(1 == ((visited >> index) & 1));
}

/******************************* IsValidMove *********************************/
static size_t SetBitOn(size_t visited, size_t index)
{
	return (visited | ((size_t)1 << index));
}

/******************************* IsValidMove *********************************/
static size_t SetBitOff(size_t visited, size_t index)
{
	return (visited & ~((size_t)1 << index));
}