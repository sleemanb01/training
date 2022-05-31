#include<stdio.h>	 /* print to */
#include<stddef.h>	 /* size_t */ 
#include<stdlib.h>   /* malloc */
#include<string.h>   /* strlen */
#include<ctype.h>    /* tolower */
#include"ws9.h"

#define WORD sizeof(long)
#define ISALIGNED(address) (address % sizeof(long) == 0) ? 1 : 0

/******** Extra Functions *******/
size_t countDigits(int n)
{
	size_t counter = 0;
	while(0 < n)
	{
		n/=10;
		++counter;
	}
	return counter;
}

int littleOrBig()
{
	unsigned int i = 1;
	char *c = (char*)&i;
	if (*c)
	{   
		return 1; /* little indean */
	}
	else
	{
		return 0; /* big indean */
	}
}

/****** Memset *****/
void* Memset(void* dest, int cntnt, size_t nbytes)
{
	unsigned char* tdest = (unsigned char*)dest;
	
	while(!ISALIGNED((unsigned long)tdest) && (0 < nbytes))
	{
		*(tdest) = (unsigned char)cntnt;
		++tdest;
		--nbytes;
	}

	while((WORD <= nbytes) && (0 <= nbytes - WORD))
	{
		*((long*)tdest) = (unsigned char)cntnt;
		nbytes -= WORD;
		++tdest;
	}

	while((nbytes-- > 0)) 
	{
		*((unsigned char*)tdest) = (unsigned char)cntnt;
		++tdest;
	}
	
	return dest;
}

/****** Memcpy *****/
void* Memcpy(void* dest, const void* src, size_t nbytes)
{
	unsigned char *tdest = (unsigned char*)dest;
	unsigned char *tsrc = (unsigned char*)src;

	while(!ISALIGNED((unsigned long)tdest) && (0 < nbytes))
	{
		*tdest = *tsrc;
		++tdest;
		++tsrc;
		--nbytes;
	}

	while((WORD <= nbytes) && (0 <= nbytes - WORD))
	{
		*(long*)tdest = *(long*)tsrc;
		tdest += WORD;
		tsrc += WORD;
		nbytes -= WORD;
	}

	while(0 < nbytes)
	{
		*tdest = *tsrc;
		++tdest;
		++tsrc;
		--nbytes;
	}
	return dest;
}

/****** Memmove *****/
void* Memmove(void* dest, const void* src, size_t nbytes)
{
	size_t i = 0;
	unsigned char *tdest = (unsigned char*)dest;
	unsigned char *tsrc = (unsigned char*)src;

	if(dest < src)
	{
		return Memcpy(dest,src,nbytes);
	}

	while(!ISALIGNED((unsigned long)tdest) && !ISALIGNED((unsigned long)tsrc) && (0 < nbytes))
	{
		*tdest = *tsrc;
		++tdest;
		++tsrc;
		--nbytes;
	}

	if(ISALIGNED((unsigned long)tdest) && ISALIGNED((unsigned long)tsrc))
	{
		while((WORD <= nbytes) && (0 <= nbytes - WORD))
		{
			*(long*)tdest = *(long*)tsrc;
			tdest += WORD;
			tsrc += WORD;
			nbytes -= WORD;
		}
	}

	while(0 < nbytes)
	{
		*tdest = *tsrc;
		++tdest;
		++tsrc;
		--nbytes;
	}
	return dest;
}

/****** string -> int *****/
int AtoiBase10(const char *buffer)
{
	size_t i = 0;
	int sum = 0;
	for( ; i < strlen(buffer) ; ++i)
	{
		sum *= 10;
		if('9' >= buffer[i] && '0' <= buffer[i])
		{
			sum += (int)buffer[i] - (int) '0';
		}
		else
		{
			return 0;
		}
	}
	
	return sum;
}

/****** any base *****/
int Atoi(const char *buffer, int base)
{
	size_t i = 0;
	int sum = 0;
	for( ; i < strlen(buffer) ; ++i)
	{
		sum *= base;
		if('9' >= buffer[i] && '0' <= buffer[i])
		{
			sum += (int)buffer[i] - (int) '0';
		}
		else if(('z' >= buffer[i] && 'a' <= buffer[i]) || ('Z' >= buffer[i] && 'A' <= buffer[i]))
		{
			sum += (int)(tolower(buffer[i])) - (int) 'a' + 10 ; /**** 10 ****/
		}
		else
		{
			return 0;
		}
	}
	
	return sum;
}

/****** base 10 *****/
char *ItoaBase10(int value, char *buffer)
{
	return Itoa (value,buffer,10);
}

/****** i to a *****/
char *Itoa(int value, char *buffer, int base)
{
	size_t i = 1;
	size_t size = countDigits(value);
	for(; i <= size ; ++i)
	{
		buffer[size - i] = (value % base) + '0';
		value /= base;
	}

	return buffer;
}

/****** CheckOnly2 *****/
void CheckOnly2(const char *a, size_t s_a, const char *b, size_t s_b, const char *c, size_t s_c)
{
	size_t i;
	int chars[257]= {0};
	
	for(i = 0; i < s_a; ++i)
	{
		chars[(int)(a[i])] = 1;
	}
	for(i = 0; i < s_b; ++i)
	{
		if(chars[(int)(b[i])] == 1)
		{
			++chars[(int)(b[i])];
		}
	}
	for(i = 0; i < s_c; ++i)
	{
		if(chars[(int)(c[i])] == 2)
		{
			--chars[(int)(c[i])];
		}
	}
	for(i = 0; i < 257; ++i)
	{
		if(chars[i] == 2)
		{
			printf("%c ", (char) i);
		}
	}
	printf("\n");
	
}
