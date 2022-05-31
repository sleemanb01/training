#include<stdio.h>

/********************EX1*******************/
void SwapInt(int *a, int *b)
{
	int t;
	t = *a;
	*a = *b;
	*b = t;
	/* print result*/
	printf("after swap one = %d, two = %d\n", *a, *b);
}

/********************EX2*******************/
void CopyArray(int *array_a, int *array_b, size_t array_size)
{
	int i;
	for (i = 0; i < (int)array_size; i++)
		array_b[i] = array_a[i];	
	/* print result*/
	printf("coppied array\n");
	for (i = 0; i < (int)array_size; i++)
		printf(" %d ",array_b[i]);
	printf("\n");
}

/********************EX4*******************/
void SwapT(size_t *a, size_t *b)
{
	int t;
	t = *a;
	*a = *b;
	*b = t;
	/* print result*/
	printf("after swap one = %lu, two = %lu\n", *a, *b);
}

/********************EX4*******************/
size_t StrLen(const char *s)
{
	assert (NULL != *s);
	const char *runner;
	for(runner = s ; '\0' != runner ; ++runner)
	{
		/*nothing to do haha*/
	}
	return (runner - s);
}

/********************EX5*******************/
int StrCmp(const char *s1,const char *s2)
{
	assert (NULL != *s1);
	assert (NULL != *s2);
	while('\0' != *s1 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return (s1 - s2);
}
