/***************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : WS09
* REVIEWER NAME : SHAHAR AIZIK
*****************************************************/

#include <stdio.h>		/* print to */
#include <stddef.h>		/* size_t */ 
#include <string.h>     /* strcpy , strlen */
#include <stdlib.h>     /* atoi */
#include"ws9.h"

int main()
{
	/***** Declaration *****/
	char src[20];
	char dest[20];
	char test[20];
	char *str = (char *) malloc(10);
	
	/***** Initializing *****/
	strcpy(src, "memsetTest1235");
	strcpy(dest, "memNVM!!!!");
	
	/***** TESTING *****/
	
	/********* MEMSET MEMCPY MEMMOVE ********/
	printf("\n*** string 1 : %s, string 2 : %s\n\n", src, dest);
	printf("1 - before Memset : %s\n", src);
	printf("  - after Memset  : %s\n\n",(char *)Memset(src, '$', 3));
	
	printf("2 - before Memcpy : %s\n", dest);
	printf("  - after Memcpy  : %s\n\n",(char *)Memcpy(dest, src, sizeof(src)));
	
	strcpy(src, "123456789");
	
	printf("3 - before Memmove dest : %s\n", dest);
	printf("  - before Memmove src  : %s\n", src);
	printf("  - after Memmove       : %s\n",(char *)Memmove(dest, src, sizeof(src)));
	
	/********* itoa/atoi ********/
	printf("\n*** atoi/itoa\n\n");
	printf("atoi 30 base 10: %d\n",AtoiBase10("30"));
	printf("system atoi 30: %d\n",atoi("30"));
	printf("atoi, a4 base 36 : %d\n",Atoi("a4",36));
	printf("itoa, 36 base 10 : %s\n",ItoaBase10(36,str));
	printf("itoa, 32 base 16 : %s\n",Itoa(32,str,16));
	
	/********* check parameters match in two array not third ********/
	strcpy(src, "memsetTest1");
	strcpy(dest, "memNVM!");
	strcpy(test, "goAhadChck!");
	
	printf("\n*** a = %s, b = %s, c = %s \nCheckOnly2 ? \n", src, dest, test); 
	CheckOnly2(src, strlen(src), dest, strlen(dest), test, strlen(test));
	
	return 0;
}
