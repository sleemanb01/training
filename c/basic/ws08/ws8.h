#ifndef __WS_8__
#define __WS_8__

#include <stdio.h>	/* print struct */
#include <stdlib.h>	/* malloc */
#include <string.h>	/* concat, strlen */

#define UNUSED(x) (void)x;


typedef enum return_t { SUCCESS, ERR_NOSTRING, ERR } return_t;
typedef return_t(*add_t)(void*, int);
typedef return_t(*print_t)(void*);
typedef return_t(*clean_t)(void*);
typedef struct Node
{
	void* type;
	add_t Add;
	print_t Print;
	clean_t Clean;
}Node;


return_t Add2Int(void*, int);
return_t Add2Flt(void*, int);
return_t Add2Str(void*, int);
return_t PrintInt(void*);
return_t PrintFlt(void*);
return_t PrintStr(void*);
return_t CleanUpStr(void*);
return_t DoNothing(void*);
#endif
