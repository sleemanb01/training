/***************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : BIT ARRAY
* REVIEWER NAME : IDAN
*****************************************************/

#include<stdio.h>	         /* printf */
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include"bit_array.h"

/* Generate a lookup table for 64 bit integers */
#define B2(n) n, n + 1, n + 1, n + 2
#define B4(n) B2(n) , B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n) B4(n) , B4(n + 1), B4(n + 1), B4(n + 2)
#define COUNT_BITS B6(0), B6(1), B6(1), B6(2)

unsigned int lookup[256] = { COUNT_BITS };


#define WORD (sizeof(long) * CHAR_BIT) /* 64-bit machine */

/*
*  Description: 	set all bits
*  Errors: 
*  Parameters:		bit_array_t
*  Return value:
*  Complexity:		O(1)
*/
bit_array_t SetAll(bit_array_t bit_array)
{
	bit_array_t mask = 0xffffffffffffffff;
	return (bit_array | mask);
}

/*
*  Description:		reset all bits
*  Errors: 
*  Parameters:		bit_array_t
*  Return value:
*  Complexity:		O(1)
*/
bit_array_t ResetAll(bit_array_t bit_array)
{
	bit_array_t mask = 0x0000000000000000;
	return (bit_array & mask);
}

/*
*  Description:		retrurn string of bits, buffer shuld be in sizeof(bit_array_t) + 1 (for null char)
*  note:		bit order right to left 
*  Parameters:		bit_array_t, char *
*  Return value:	char *
*  Complexity:		O(n)
*/

char *ToString(bit_array_t bit_array, char *output_str)
{
	size_t i =0;
	bit_array_t tmp = bit_array;
	char *str_tmp = output_str;
	tmp = MirrorBitArray(tmp);
	for(; i < WORD; tmp >>= 1, ++str_tmp, ++i)
	{
		*str_tmp = (tmp & 0x1) + '0';
	}
	*str_tmp = '\0';


	return output_str;
}

/*
*  Description:		set a single bit on
*  Errors: 
*  Parameters:		bit_array_t, bit_array_t 
*  Return value:
*  Complexity:		O(1)
*/
bit_array_t SetBitOn(bit_array_t bit_array, size_t index)
{
	return (bit_array | (0x1 << index));
}

/*
*  Description:		set a single bit off
*  Errors: 
*  Parameters:		bit_array_t, bit_array_t 
*  Return value:
*  Complexity:		O(1)
*/
bit_array_t SetBitOff(bit_array_t bit_array, size_t index)
{
	return (bit_array & ~(0x1 << index));
}

/*
*  Description:		set a value 
*  Errors: 		value should only be 0 or 1 every other val will be cause undifined behaviour 
*  Parameters:		bit_array_t, bit_array_t, int
*  Return value:
*  Complexity:		O(1)
*/
bit_array_t SetBit(bit_array_t bit_array, size_t index, unsigned int value)
{
	if(value == 1)
	{
		bit_array = SetBitOn(bit_array, index);
	}
	else
	{
		bit_array = SetBitOff(bit_array, index);
	}
	return (bit_array);
}

/*
*  Description:		get a single bit
*  Errors: 
*  Parameters:		bit_array_t, bit_array_t
*  Return value:
*  Complexity:		O(1)
*/
int GetBitVal(bit_array_t bit_array, size_t index)
{
	return ((bit_array >> (index)) & 0x1);
}

/*
*  Description:		flip a single bit
*  Errors: 
*  Parameters:		bit_array_t, bit_array_t
*  Return value:
*  Complexity:		O(1)
*/
bit_array_t FlipBit(bit_array_t bit_array, size_t index)
{
	unsigned int tmp = (bit_array >> (index) & 0x1) ? 0 : 1 ;
	return (SetBit(bit_array, index, tmp));
}

/*
*  Description:		mirror arr
*  Errors: 
*  Parameters:		bit_array_t
*  Return value:
*  Complexity:		O(n)
*/
bit_array_t MirrorBitArray(bit_array_t bit_array)
{
	bit_array = ((bit_array & 0xffffffff00000000) >> 32) |
	 ((bit_array & 0x00000000ffffffff) << 32);
	
	bit_array = ((bit_array & 0xffff0000ffff0000) >> 16) |
	 ((bit_array & 0x0000ffff0000ffff) << 16);
	
	bit_array = ((bit_array & 0xff00ff00ff00ff00) >> 8) |
	 ((bit_array & 0x00ff00ff00ff00ff) << 8);
	
	bit_array = ((bit_array & 0xf0f0f0f0f0f0f0f0) >> 4) |
	 ((bit_array & 0x0f0f0f0f0f0f0f0f) << 4);
	
	bit_array = ((bit_array & 0xcccccccccccccccc) >> 2) |
	 ((bit_array & 0x3333333333333333) << 2);
	
	bit_array = ((bit_array & 0xaaaaaaaaaaaaaaaa) >> 1) |
	 ((bit_array & 0x5555555555555555) << 1);
	
	return (bit_array);

}

/*
*  Description:		rotate right
*  Errors: 
*  Parameters:		bit_array_t
*  Return value:
*  Complexity:		O(n)
*/
bit_array_t RotR(bit_array_t bit_array, unsigned int value)
{
	int rotator = (WORD - value);
	return (bit_array >> value | bit_array << rotator);
}

/*
*  Description:		rotate left
*  Errors: 
*  Parameters:		bit_array_t
*  Return value:
*  Complexity:		O(n)
*/
bit_array_t RotL(bit_array_t bit_array, unsigned int value)
{
	int rotator = (WORD - value);
	return (bit_array << value | bit_array >> rotator);
}

/*
*  Description:		count
*  Errors: 
*  Parameters:		bit_array_t
*  Return value:
*  Complexity:		O(n)
*/
size_t CountOn(bit_array_t bit_array)
{
	size_t result = 0;
	
	result = lookup[bit_array & 0xff] +
	lookup[(bit_array >> 8) & 0xff] +
	lookup[(bit_array >> 16) & 0xff] +
	lookup[(bit_array >> 24) & 0xff] +
	lookup[(bit_array >> 32) & 0xff] +
	lookup[(bit_array >> 40) & 0xff] +
	lookup[(bit_array >> 48) & 0xff] +
	lookup[(bit_array >> 56) & 0xff];
	
	return (result);

}

/*
*  Description:		count
*  Errors: 
*  Parameters:		bit_array_t
*  Return value:
*  Complexity:		O(n)
*/
size_t CountOff(bit_array_t bit_array)
{
	size_t result = 0;
	
	result = lookup[bit_array & 0xff] +
	lookup[(bit_array >> 8) & 0xff] +
	lookup[(bit_array >> 16) & 0xff] +
	lookup[(bit_array >> 24) & 0xff] +
	lookup[(bit_array >> 32) & 0xff] +
	lookup[(bit_array >> 40) & 0xff] +
	lookup[(bit_array >> 48) & 0xff] +
	lookup[(bit_array >> 56) & 0xff];
	
	return (WORD - result);
}