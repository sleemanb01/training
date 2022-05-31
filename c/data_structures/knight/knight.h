#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include <stddef.h> /* for size_t */

#define BOARD_SIZE 64

/********* VERSION 2 *********/

typedef enum return_ty{SUCCESS,FAIL, TIME_OUT}return_ty;

typedef struct position
{
	int row;
	int col;
	
}position_ty;


/****************** FUNCS *********************/

/* user should allocate position_ty array of size row * col ( maximum number of steps avialable )  */
return_ty KnightTour(position_ty start_pos, position_ty steps[BOARD_SIZE]); /* stpes LUT */


#endif
