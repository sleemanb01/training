#include<stdio.h>	/* print struct */
#include<stdlib.h>	/* malloc */
#include<string.h>	/* concat, strlen */
#include"ws8.h"

/****** ADD TO INTEGER *****/
return_t Add2Int(void* p, int i)
{
	*((int *)p) += i;
	return SUCCESS;
}

/****** ADD TO FLOAT *****/
return_t Add2Flt(void* p, int i)
{
	*((float *)p) += i;
	return SUCCESS;
}

/****** ADD TO STRING *****/
return_t Add2Str(void* p, int i)
{
	size_t i_size = strlen((char *)p) + sizeof(i);
	p = (char *) realloc(p, i_size);
	sprintf((char *)p, "%s%d", (char *)p, i);
	return SUCCESS;
}

/****** PRINT INT *****/
return_t PrintInt(void* p)
{
	printf("%d\n", *((int *)p));
	return SUCCESS;
}

/****** PRINT FLOAT *****/
return_t PrintFlt(void* p)
{
	printf("%.2f\n", *((float *)p));
	return SUCCESS;
}

/****** PRINT STRING *****/
return_t PrintStr(void* p)
{
	printf("%s\n",(char *)p);
	return SUCCESS;
}

/****** CLEAN STRING *****/
return_t CleanUpStr(void* p)
{
	free(p);
	return SUCCESS;
}

/****** DO NOTHING *****/
return_t DoNothing(void* p)
{
	return SUCCESS;
}


