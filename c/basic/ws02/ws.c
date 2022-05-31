#include<stdio.h>
#include<stddef.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/********************strlen*******************/
size_t StrLen(const char *s)
{
	const char *runner;
	assert(NULL != s);
	for(runner = s ; '\0' != *runner ; ++runner);
	return (runner -s);
}

/********************strcpy*******************/
char *StrnCpy(char *dest, const char *src, size_t n)
{
	size_t i;
	assert(dest != NULL);
	assert(src != NULL);
	
	for(i = 0; '\0' != src[i] && i < n ; ++i)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	
	return dest;
}

/********************strncpy*******************/
char *StrCpy(char *dest, const char *src)
{
	size_t i;
	assert(dest != NULL);
	assert(src != NULL);
	
	for(i = 0; '\0' != src[i] ; ++i)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	
	return dest;
}

/********************strcmp*******************/
int StrCmp(const char *s1, const char *s2)
{
	int result = 0;
	assert(NULL != s1);
	assert(NULL != s2);
	while ('\0' != *s1 && '\0' != *s2)
	{
		if(*s1 != *s2)
		{
			result = (*s1 > *s2) ? 1 : -1;
			break;
		}
		else
		{
			++s1;
			++s2;
		}
	}
	return result;
}

/********************strcmp*******************/
int StrnCmp(const char *s1, const char *s2, size_t n)
{
	/*int result = 0;
	size_t counter = 0;
	assert(NULL != s1);
	assert(NULL != s2);
	while ('\0' != *s1 && '\0' != *s2 && counter<= n)
	{
		if(*s1 != *s2)
		{
			result = (*s1 > *s2) ? 1 : -1;
			break;
		}
		else
		{
			++s1;
			++s2;
			++counter;
		}
	}
	return result;*/
	size_t i;
	for (i = 0; (*s1 == *s2) && (i < n) && (*s1 != '\0'); ++i, ++s1, ++s2 )
	{/*Nothing*/}
	
	return *s1 - *s2;

}

/********************StrCaseCmp*******************/
int StrCaseCmp(const char *s1, const char *s2)
{
	assert(NULL != s1);
	assert(NULL != s2);
	while ('\0' != *s1 && '\0' != *s2)
	{
		if(tolower(*s1) != tolower(*s2) || '\0' == *s1 || '\0' == *s2 )
		{
			return tolower(*s1 - *s2); /* to lower added ***********************/
		}
		++s1;
		++s2;
	}
	return 0;
}

/********************StrChr*******************/
char *StrChr(const char *s, int c)
{
	assert(NULL != s);
	while('\0' != *s)
	{
		if((char)c == *s)
		{
			return (char *)s;
		}

		++s;
	}
	return NULL;
}

/********************StrDup*******************/
char *StrDup(const char *s)
{
	char *dest = (char *)malloc((strlen(s) + 1) * sizeof(char));
	assert(NULL != s);
	return StrCpy(dest, s);
}

/********************StrCat*******************/
char *StrCat(char *dest, const char *src)
{
	size_t len = strlen(dest);
	char *tmp = dest;
	
	assert(NULL != dest);
	assert(NULL != src);
	
	dest += len;
	while ('\0' != *src)
	{
		*dest = *src;
		++dest;
		++src;
	}
	*dest = '\0';
	
	return tmp; /***************          SEGMANTATION FAULT   ***************/


}

/********************StrnCat*******************/
char *StrnCat(char *dest, const char *src, size_t n)
{
	size_t len = strlen(dest);
	char *tmp = dest;
	size_t counter = 0;
	
	assert(NULL != dest);
	assert(NULL != src);
	
	dest += len;
	while ('\0' != *src && ++counter < n)
	{
		*dest = *src;
		++dest;
		++src;
	}
	*dest = '\0';
	
	return tmp; /***************          SEGMANTATION FAULT   ***************/
}

/********************StrnCat*******************/
char *StrStr(const char *haystack, const char *needle)
{
	size_t i, j;
	
	assert(haystack != NULL);
	assert(needle != NULL);
	
	for ( i = 0 ; haystack[i] != '\0' ; ++i)
	{
		for ( j = 0 ; (haystack[i + j] == needle[j]) && (needle[j] != '\0') ; ++j)
		{/*nothing*/}
		if (needle[j] == '\0')
		{
			return (char *)(haystack + i);
		} 
			
	}

	return NULL;

}
	/*char *result = NULL;
	int flag = 0;
	assert(NULL != haystack);
	assert(NULL != needle);
	
	while('\0' != *haystack && '\0' != *needle)
	{
		if(*needle == *haystack)
		{
			if(flag == 0)
			{
				result =(char *)haystack;
				flag = 1;
			}
			if('\0' == *needle)
			{
				break;
			}
		}
		else
		{
			flag = 0;
		}
		++needle;
		++haystack;
	}
	
	return result;*/


/********************StrSpn*******************/
size_t StrSpn(const char *s, const char *accept)
{
	/*size_t counter = 0;
	size_t max = 0;
	assert(NULL != s);
	assert(NULL != accept);
	
	while('\0' != *s)
	{
		if(*s == *accept)
		{
			++counter;
		}
		else
		{
			max = (counter > max) ? counter : max ;
			counter = 0;
		}
		++s;
		++accept;
	}
	return max;*/
	const char *s_mem = s, *accept_mem = accept;

	assert(s != NULL);
	assert(accept != NULL);

	for ( ; (*s != '\0') ; ++s)
	{
		for  ( ; (*s != *accept) && (*accept != '\0') ; ++accept)
		{/*nothing*/}
		if (*accept == '\0')
		{
			return (s - s_mem);
		}
		accept = accept_mem;
	}
	
	return 0;

}

/********************StrTok*******************/
char *StrTok(char *str, const char *delim)
{
	static char *iterator = NULL;		
	char *return_token;
	size_t runner, delim_len = 0, delim_runner;

	assert( NULL != delim); 				
	
	delim_len = StrLen(delim);			
	
	if(NULL != str)						
	{
		iterator = str;
	}
	
	if('\0' == iterator[0])							/* means all the string has been explored*/
	{
		return NULL;
	}
	
	if('\0' == delim[0])							/* special case with an empty delim */
	{		
		if(NULL == str)
		{
			return NULL;
		}
		return iterator;
	}
	
	return_token = (char *)malloc(StrLen(iterator) * sizeof(char) + 1);	/* this will be returned */
	
	for(runner = 0; '\0' != iterator[runner]; ++runner)
	{									/* will check for delim charecters and keep count*/
		for(delim_runner = 0; iterator[runner] != delim[delim_runner] && delim_runner < delim_len; ++delim_runner) 
		{ /* do nothing */}
		
		if(delim_runner == delim_len)					/* if this charecter is not in delim */
		{
			return_token[runner] = iterator[runner];
		}
		else								/* if this charecter is in delim */
		{
			iterator = iterator + runner+1;
			return_token[runner] = '\0';
			return return_token;
		}
	}
	++iterator;
	return_token[runner] = '\0';
	return (char *)return_token;

	
	
}

