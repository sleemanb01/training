#ifndef __WS_6__
#define __WS_6__


/*a*/
long Pow2(unsigned int x, unsigned int y);
/*b*/
int IsPowerOf2(unsigned int n);
/*c*/ 
int AddOne(int num); 
/*d*/
void PrintThreeBitOn(unsigned int *arr, size_t length);
/*e*/
unsigned char ByteMirror(unsigned char c);
/*f*/
int CheckIf2And6Set(unsigned char c);

int CheckIf2And6SetAtLeast(unsigned char c);

unsigned char SwapBits3And5(unsigned char c);
/*g*/
unsigned int DivideBy16(unsigned int num);
/*h*/
void Swap(unsigned int *x, unsigned int *y);
/*i*/ /* O(n) ---> O(log(n)) ----> O(1) */
unsigned int CountBitsOn(unsigned int num); 
/*j*/
void PrintFloatBits(float num); /* reinerpret cast in C (versus static cast) */

/* EXTRA */
void PrintCharToByte(unsigned char c);



#endif
