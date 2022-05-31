#ifndef WD_H
#define WD


/**** VERSION 2.2 ****/

typedef enum {SUCCESS = 0, SYS_ERR = 1, MEM_ERR = 2}return_ty;

/***********************************************************************************
*
*		FUNCTION NAME	: MakeMeImmortal
*		DESCRIPTION		: Run a watchdog to keep calling program running until 'max_sol_miss'
*						  has been reached by called program. Calling program uses
*						  'sol_interval' to count number of seconds between heart beats. 
*						  calling program MUST mask SIGUSR1, SIGUSR2 on all other threads.
*		ARGUMENT LIST	:
*		Argument		    Type				I/O		Description
*		--------		    ----				---		-----------
*		app_argv			const char* []		I		array of null terminated strings
*		sol_interval		int					I		time interval between signals
*		max_sol_miss		int					I		number of signal till timeout
*
*		RETURN:			: int, 0 on success, 1 on system error, 2 on memory error.
*
**********************************************************************************/
int MakeMeImmortal(const char* app_argv[], int sol_interval, int max_sol_miss);

/***********************************************************************************
*
*		FUNCTION NAME	: DNR
*		DESCRIPTION		: Leave calling program without monitoring heart beats
*		ARGUMENT LIST	:
*		Argument		    Type				I/O		Description
*		--------		    ----				---		-----------
*
*		RETURN:			: int, 0 on success, 1 on system error, 2 on memory error.
*
**********************************************************************************/
int DNR(); 

#endif
