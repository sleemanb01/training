#include<stdio.h>
#include<stddef.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/******************** A *******************/
long Pow2(unsigned int x, unsigned int y)
{
	return (x << y);
}

/******************** B *******************/
int IsPowerOf2(unsigned int n)
{
	/* NOT A LOOP */
	if((n & (n -1 )) != 0 )
		return 0;
	/* LOOP */
	for( ;n > 2 ; n = n >> 1)
	{
		if ((n % 2) != 0)
			return 0;
	}
	return 1;
	
}

/******************** C *******************/
int AddOne(int num)
{
	return (-(~num));
}

/******************** D *******************/
void PrintThreeBitOn(unsigned int *arr, size_t length)
{
	unsigned int tmp;
	int c = 0;
	size_t i;
	for(i = 0; i < length ; ++i)
	{
		tmp = arr[i];
		for (; tmp > 0; tmp >>= 1)
		{
			if((tmp & 1) == 1)
			{
				c++;
			}
		}
		if(c == 3)
		{
			printf("arr[%lu] - %d\n",i,arr[i]);
		}
		c = 0;
	}
}

/******************** E *******************/
unsigned char ByteMirror(unsigned char c)
{
	/***** NOT A LOOP *****/
	c = (c & 0xF0) >> 4 | (c & 0x0F) << 4;
	c = (c & 0xCC) >> 2 | (c & 0x33) << 2;
	c = (c & 0xAA) >> 1 | (c & 0x55) << 1;
	return c;
	/***** NOT A LOOP *****/
	
	/* LOOP */ 
	/*unsigned int  NO_OF_BITS = sizeof(c) * 8;
	unsigned int reverse_num = 0;
	unsigned int i;
	
	for (i = 0; i < NO_OF_BITS; i++)
	{
		if((c & (1 << i)))
	   		reverse_num |= 1 << ((NO_OF_BITS - 1) - i);  
	}
	return reverse_num;*/
}

/******************** F1 *******************/
int CheckIf2And6Set(unsigned char c)
{
	return ((c >> 2) & (c>> 6) & 0x01); 
}

/******************** F2 *******************/
int CheckIf2And6SetAtLeast(unsigned char c)
{
	return (((c >> 2) | (c>> 6)) & 0x01);
}

/******************** F3 *******************/
unsigned char SwapBits3And5(unsigned char c)
{
	unsigned char tmp , res;
	tmp = ((c >> 3) ^ (c >> 5)) & 1;
	res = c ^ ((tmp << 3) | (tmp << 5));
	
	return res;
}

/******************** G *******************/
unsigned int DivideBy16(unsigned int num)
{
	num >>= 4 ;
	num <<= 4;
	return num;
}

/******************** H *******************/
void Swap(unsigned int *x, unsigned int *y)
{
	*x = *x + *y;
	*y = *x - *y;
	*x = *x - *y;
}

/******* I O(n) ---> O(log(n)) ----> O(1) */
unsigned int CountBitsOn(unsigned int num)
{
	unsigned int mask1 = 1431655765; 	/*0x55 0x55 0x55 0x55 - 01010101 01010101 01010101 01010101 */
	unsigned int mask2 = 858993459; 	/*0x33 0x33 0x33 0x33 - 00110011 00110011 00110011 00110011*/
	unsigned int mask3 = 252645135; 	/*0x0f 0x0f 0x0f 0x0f - 00001111 00001111 00001111 00001111*/
	unsigned int mask4 = 16711935; 	        /*0x00 0xff 0x00 0xff - 00000000 11111111 00000000 11111111*/
	unsigned int mask5 = 65535;		/*0x00 0x00 0xff 0xff - 00000000 00000000 11111111 11111111*/
	unsigned int temp1, temp2;
	
	/*adds the number of set bits of every 2 bits (1-2  3-4 ... 31-32)*/
	temp1 = (mask1 & num);
	temp2 = (mask1 & (num >> 1));
	num = temp1 + temp2;
	
	/*adds the number of set bits of every 4 bits (1-4  5-8 ... 29-32)*/
	temp1 = (mask2 & num);
	temp2 = (mask2 & (num >> 2));
	num = temp1 + temp2;
	
	/*adds the number of set bits of every 8 bits (1-8  9-16 ... 25-32)*/
	temp1 = (mask3 & num);
	temp2 = (mask3 & (num >> 4));
	num = temp1 + temp2;
	
	/*adds the number of set bits of every 16 bits (1-16 17-32)*/
	temp1 = (mask4 & num);
	temp2 = (mask4 & (num >> 8));
	num = temp1 + temp2;
	
	/*adds the number of set bits of 32 bits */
	temp1 = (mask5 & num);
	temp2 = (mask5 & (num >> 16));
	num = temp1 + temp2;
	return num;
}

/******************** J *******************/
void PrintFloatBits(float num) 
{
	float* f = &num;
	unsigned int ui = *(unsigned int *)(f);
	PrintCharToByte((unsigned char)(ui >> 24)); 
	printf(" ");
	PrintCharToByte((unsigned char)(ui >> 16));
	printf(" ");
	PrintCharToByte((unsigned char)(ui >> 8));	
	printf(" ");
	PrintCharToByte((unsigned char)(ui));
	printf("\n");
}
/******************** PrintCharToByte *******************/
void PrintCharToByte(unsigned char c)
{
	int idx = 128;
	for(; idx >= 1; idx >>= 1)
	{
		if(c & idx)
		{
			printf("1");	
		}
		else
		{
			printf("0");
		}
			
	}
	printf("\n");

}

