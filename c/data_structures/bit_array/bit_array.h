#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

#include <stddef.h> /*bit_array_t*/

typedef size_t bit_array_t;

/*
*  Description: 	set all bits
*  Errors: 
*  Parameters:		bit_array_t
*  Return value:
*  Complexity:		O(1)
*/
bit_array_t SetAll(bit_array_t bit_array);

/*
*  Description:		reset all bits
*  Errors: 
*  Parameters:		bit_array_t
*  Return value:
*  Complexity:		O(1)
*/
bit_array_t ResetAll(bit_array_t bit_array);

/*
*  Description:		retrurn string of bits, buffer shuld be in sizeof(bit_array_t) + 1 (for null char)
*  note:		bit order right to left 
*  Parameters:		bit_array_t, char *
*  Return value:	char *
*  Complexity:		O(n)
*/
char *ToString(bit_array_t bit_array, char *output_str);

/*
*  Description:		set a single bit on
*  Errors: 
*  Parameters:		bit_array_t, bit_array_t 
*  Return value:
*  Complexity:		O(1)
*/
bit_array_t SetBitOn(bit_array_t bit_array, size_t index);

/*
*  Description:		set a single bit off
*  Errors: 
*  Parameters:		bit_array_t, bit_array_t 
*  Return value:
*  Complexity:		O(1)
*/
bit_array_t SetBitOff(bit_array_t bit_array, size_t index);

/*
*  Description:		set a value 
*  Errors: 		value should only be 0 or 1 every other val will be cause undifined behaviour 
*  Parameters:		bit_array_t, bit_array_t, int
*  Return value:
*  Complexity:		O(1)
*/
bit_array_t SetBit(bit_array_t bit_array, size_t index, unsigned int value);

/*
*  Description:		get a single bit
*  Errors: 
*  Parameters:		bit_array_t, bit_array_t
*  Return value:
*  Complexity:		O(1)
*/
int GetBitVal(bit_array_t bit_array, size_t index);

/*
*  Description:		flip a single bit
*  Errors: 
*  Parameters:		bit_array_t, bit_array_t
*  Return value:
*  Complexity:		O(1)
*/
bit_array_t FlipBit(bit_array_t bit_array, size_t index);

/*
*  Description:		mirror arr
*  Errors: 
*  Parameters:		bit_array_t
*  Return value:
*  Complexity:		O(n)
*/
bit_array_t MirrorBitArray(bit_array_t bit_array);

/*
*  Description:		rotate right
*  Errors: 
*  Parameters:		bit_array_t
*  Return value:
*  Complexity:		O(n)
*/
bit_array_t RotR(bit_array_t bit_array, unsigned int value);

/*
*  Description:		rotate left
*  Errors: 
*  Parameters:		bit_array_t
*  Return value:
*  Complexity:		O(n)
*/
bit_array_t RotL(bit_array_t bit_array, unsigned int value);

/*
*  Description:		count
*  Errors: 
*  Parameters:		bit_array_t
*  Return value:
*  Complexity:		O(n)
*/
size_t CountOn(bit_array_t bit_array);

/*
*  Description:		count
*  Errors: 
*  Parameters:		bit_array_t
*  Return value:
*  Complexity:		O(n)
*/
size_t CountOff(bit_array_t bit_array);


#endif /*for __BIT_ARRAY_H__ S*/

