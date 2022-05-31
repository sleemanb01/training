#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "bit_array.h"
#include "tests.h"

#define BITS 64

void SetResetAllTest();
void ToStringTest();
void SetOnOffTest();
void SetBitTest();
void GetBitValTest();
void FlipBitTest();
void MirrorBitArrayTest();
void RotRLTest();
void CountOnOffTest();



int main()
{
	SetResetAllTest();
	ToStringTest();
	SetOnOffTest();
	SetBitTest();
	GetBitValTest();
	FlipBitTest();
	MirrorBitArrayTest();
	RotRLTest();
	CountOnOffTest();
	
	PASS;
	return (0);
}

void SetResetAllTest()
{
	/*bit_array_t arr1 = 234253, arr2 = 34135, arr3 = 0, arr4 = 0xffffffffffffffff, max = 0xffffffffffffffff, min = 0, result = 0;
	
	
	result = SetAll(arr1);
	TEST("SetAll()", result, max);
	result = SetAll(arr2);
	TEST("SetAll()", result, max);
	result = SetAll(arr3);
	TEST("SetAll()", result, max);
	result = SetAll(arr4);
	TEST("SetAll()", result, max);
	
	result = ResetAll(arr1);
	TEST("ResetAll()", result, min);
	result = ResetAll(arr2);
	TEST("ResetAll()", result, min);
	result = ResetAll(arr3);
	TEST("ResetAll()", result, min);
	result = ResetAll(arr4);
	TEST("ResetAll()", result, min);*/
}


void ToStringTest()
{
	/*bit_array_t arr1 = 234253, arr2 = 34135, max = 0xffffffffffffffff, min = 0, i = 0;
	char *str1, *str2, one = '1', zero = '0';
	char str3[BITS + 1] = "0000000000000000000000000000000000000000000000111001001100001101";
	char str4[BITS + 1] = "0000000000000000000000000000000000000000000000001000010101010111";
	
	str1 = (char *) malloc((BITS + 1) * sizeof(char));
	str2 = (char *) malloc((BITS + 1) * sizeof(char)); 
	
	str1 = ToString(min, str1);
	
	for (i = 0; i < BITS; ++i)
	{
		str2[i] = zero;
	}
	
	TEST_STR("ToString()",strcmp(str1, str2) ,str1 , str2, 0);
	
	for (i = 0; i < BITS; ++i)
	{
		str2[i] = one;
	}
	
	str1 = ToString(max, str1);
	TEST_STR("ToString()",strcmp(str1, str2) ,str1 , str2, 0);
	str1 = ToString(arr1, str1);
	TEST_STR("ToString()",strcmp(str1, str3) ,str1 , str3, 0);
	str1 = ToString(arr2, str1);
	TEST_STR("ToString()",strcmp(str1, str4) ,str1 , str4, 0);
	
	free(str1);
	free(str2);*/
}


void SetOnOffTest()
{
	/*bit_array_t arr1 = 0, min = 0, result = 0;
	
	result = SetBitOn(arr1, 0);
	TEST("SetBitOn()", result, 1);
	result = SetBitOff(result, 0);
	TEST("SetBitOff()", result, min);
	result = SetBitOn(arr1, 1);
	TEST("SetBitOn()", result, 2);
	result = SetBitOff(result, 1);
	TEST("SetBitOff()", result, min);
	result = SetBitOn(arr1, 2);
	TEST("SetBitOn()", result, 4);
	result = SetBitOff(result, 2);
	TEST("SetBitOff()", result, min);
	result = SetBitOn(arr1, 3);
	TEST("SetBitOn()", result, 8);
	result = SetBitOff(result, 3);
	TEST("SetBitOff()", result, min);
	result = SetBitOn(arr1, 4);
	TEST("SetBitOn()", result, 16);
	result = SetBitOff(result, 4);
	TEST("SetBitOff()", result, min);
	result = SetBitOn(arr1, 5);
	TEST("SetBitOn()", result, 32);
	result = SetBitOff(result, 5);
	TEST("SetBitOff()", result, min);*/
}


void SetBitTest()
{
	/*bit_array_t arr1 = 0, result = 0, test = 1, i = 0;
	for (i = 0; i < 5; ++i)
	{
		result = SetBit(arr1, i, 1);
		TEST("SetBit()", result, test);
		result = SetBit(arr1, i, 0);
		TEST("SetBit()", result, 0);
		test *= 2;
	}*/
}


void GetBitValTest()
{
	/*bit_array_t arr1 = 234253;
	int result = 0;
	result = GetBitVal(arr1, 0);
	TEST("GetBitVal()", result, 1);
	result = GetBitVal(arr1, 1);
	TEST("GetBitVal()", result, 0);
	result = GetBitVal(arr1, 2);
	TEST("GetBitVal()", result, 1);
	result = GetBitVal(arr1, 3);
	TEST("GetBitVal()", result, 1);
	result = GetBitVal(arr1, 4);
	TEST("GetBitVal()", result, 0);
	result = GetBitVal(arr1, 5);
	TEST("GetBitVal()", result, 0);
	result = GetBitVal(arr1, 6);
	TEST("GetBitVal()", result, 0);
	result = GetBitVal(arr1, 7);
	TEST("GetBitVal()", result, 0);
	result = GetBitVal(arr1, 8);
	TEST("GetBitVal()", result, 1);
	result = GetBitVal(arr1, 9);
	TEST("GetBitVal()", result, 1);*/
}


void FlipBitTest()
{
	/*bit_array_t result =0, i =0, min =0, max = 255;
	
	for (i = 0; i < CHAR_BIT; ++i)
	{
		result = FlipBit(result, i);
	}
	TEST("FlipBit()", result, max);
	
	for (i = 0; i < CHAR_BIT; ++i)
	{
		result = FlipBit(result, i);
	}
	TEST("FlipBit()", result, min);*/
}


void MirrorBitArrayTest()
{
	/*bit_array_t arr1 = 234253, arr2 = 0, arr3 = arr1;
	arr2 = MirrorBitArray(arr1);
	arr2 = MirrorBitArray(arr2);
	TEST("MirrorBitArray()", arr2, arr1);
	arr1 = MirrorBitArray(arr1);
	arr2 = MirrorBitArray(arr2);
	TEST("MirrorBitArray()", arr2, arr1);
	arr1 = MirrorBitArray(arr1);
	arr2 = MirrorBitArray(arr2);
	TEST("MirrorBitArray()", arr1, arr3);
	TEST("MirrorBitArray()", arr2, arr3);*/
}


void RotRLTest()
{
	/*bit_array_t arr1 = 234253, arr2 = 0, arr3 = arr1;
	unsigned int n = 37, n2 = 27;
	
	arr2 = RotR(arr1, n);
	arr2 = RotL(arr2, n);
	TEST("RotRL()", arr2, arr1);
	arr3 = RotR(arr3, n);
	arr3 = RotR(arr3, n2);
	TEST("RotR()", arr3, arr1);
	arr3 = RotL(arr3, n);
	arr3 = RotL(arr3, n2);
	TEST("RotL()", arr3, arr1);*/
}


void CountOnOffTest()
{
	/*bit_array_t arr1 = 234253, arr2 = 0, arr3 = 0xffffffffffffffff;
	size_t result1 = 0, result2 = 0, total = 0;
	result1 = CountOff(arr1);
	
	result2 = CountOn(arr1);
	total = result1 + result2;
	TEST("CountOnOff()", total, BITS);
	result1 = CountOff(arr2);
	result2 = CountOn(arr3);
	TEST("CountOff()", result1, BITS);
	TEST("CountOn()", result2, BITS);*/
}

