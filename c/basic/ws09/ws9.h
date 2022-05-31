#ifndef __WS_9__
#define __WS_9__
#include <stdio.h>		/* print to */
#include <stddef.h>		/* size_t */ 
			
#define UNUSED(x) (void)x;

void* Memset(void* dest, int cntnt, size_t nbytes);
void* Memcpy(void* dest, const void* src, size_t nbytes);
void* Memmove(void* dest, const void* src, size_t nbytes);

int AtoiBase10(const char *buffer);               /* string -> int */
int Atoi(const char *buffer, int base);           /* any base */
char *ItoaBase10(int value, char *buffer);
char *Itoa(int value, char *buffer, int base);   /* int -> string */

void CheckOnly2(const char *a, size_t s_a, const char *b, size_t s_b, const char *c, size_t s_c); 


/* Happy coding */ 

#endif
