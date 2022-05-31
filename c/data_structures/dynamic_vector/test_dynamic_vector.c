/***************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : DV
* REVIEWER NAME : 
*****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"dynamic_vector.h"
#include"tests.h"


void CreateDestroyTest();
void CapacityTest();
void PushBackTest();
void GetElementTest();
void SizeTest();
void PopBackTest();
void SetElementTest();
void ReserveShrinkTest();

int main()
{
	void CreateDestroyTest();
	void CapacityTest();
	void PushBackTest();
	void GetElementTest();
	void SizeTest();
	void PopBackTest();
	void SetElementTest();
	void ReserveShrinkTest();
	
	PASS;
	
	return (0);
}

void CreateDestroyTest()
{
	size_t num1 = 10, status = 0;
	struct dynamic_vector *vector_t = DVectorCreate(num1);
	
	TEST("DVectorCreate()", DVectorCapacity(vector_t), num1);
	
	DVectorDestroy(vector_t);
	status = (vector_t == NULL);
	
	TEST("DVectorCreate()", status, 1);
}

void CapacityTest()
{
	size_t num1 = 15, num2 = 20;
	struct dynamic_vector *vector_t = DVectorCreate(num1);
	
	TEST("DVectorCapacity()", DVectorCapacity(vector_t), num1);
	
	DVectorReserve(vector_t, num2);
	TEST("DVectorSize", DVectorCapacity(vector_t), num2);
	
	DVectorDestroy(vector_t);
}

void PushBackTest()
{
	size_t num0 = 0, num1 = 15, num2 = 4, num3 = 6534, num4 = 432, num5 = 101010;
	size_t *num1_ptr = &num1, *num2_ptr = &num2, *num3_ptr = &num3, *num4_ptr = &num4, *num5_ptr = &num5;
	
	struct dynamic_vector *vector_t = DVectorCreate(num1);
	
	DVectorPushBack(vector_t, num1_ptr);
	DVectorPushBack(vector_t, num2_ptr);
	DVectorPushBack(vector_t, num3_ptr);
	DVectorPushBack(vector_t, num4_ptr);
	DVectorPushBack(vector_t, num5_ptr);

	num0 = *(size_t *)DVectorGetElement(vector_t, 0);
	TEST("DVectorPushBack()", num0, num1);
	
	num0 = *(size_t *)DVectorGetElement(vector_t, 1);
	TEST("DVectorPushBack()", num0, num2);
	
	num0 = *(size_t *)DVectorGetElement(vector_t, 2);
	TEST("DVectorPushBack()", num0, num3);
	
	num0 = *(size_t *)DVectorGetElement(vector_t, 3);
	TEST("DVectorPushBack()", num0, num4);
	
	num0 = *(size_t *)DVectorGetElement(vector_t, 4);
	TEST("DVectorPushBack()", num0, num5);
	
	DVectorDestroy(vector_t);
}

void GetElementTest()
{
	struct dynamic_vector *vector_t;
	size_t num1 = 15, num2 = 1, *num2_ptr = &num2, *num_ptr = NULL;
	float f1 = 4.5, *f1_ptr = &f1, *f_ptr = NULL;
	char chr1 = 'a', *chr1_ptr = &chr1, *chr_ptr = NULL;
	char *str1 = "abc", *str = NULL;
	str = (char *) malloc(strlen(str1) + 1);
	vector_t = DVectorCreate(num1);
	
	DVectorPushBack(vector_t, num2_ptr);
	num_ptr = (size_t *)DVectorGetElement(vector_t, 0);
	TEST("DVectorGetElement()", *num_ptr, *num2_ptr);
	
	DVectorPushBack(vector_t, f1_ptr);
	f_ptr = (float *)DVectorGetElement(vector_t, 1);
	TEST("DVectorGetElement()", f_ptr, f1_ptr);
	
	DVectorPushBack(vector_t, chr1_ptr);
	chr_ptr = (char *)DVectorGetElement(vector_t, 2);
	TEST("DVectorGetElement()", *chr_ptr, *chr1_ptr);
	
	DVectorPushBack(vector_t, str1);
	str = (char *)DVectorGetElement(vector_t, 3);
	/*TEST_STR("DVectorGetElement()",strcmp(str, str1) ,str , str1, 0);*/
	
	DVectorDestroy(vector_t);
	free(str);
}

void SizeTest()
{
	size_t num1 = 10, num2 = 15, size = 20, runner = 0, *num1_ptr = &num1, *num2_ptr = &num2;
	struct dynamic_vector *vector_t = DVectorCreate(size);
	
	for(runner = 10; runner > 0; --runner)
	{
		DVectorPushBack(vector_t, num1_ptr);
	}
	
	TEST("DVectorSize", DVectorSize(vector_t), num1);
	
	for(runner = 5; runner > 0; --runner)
	{
		DVectorPushBack(vector_t, num2_ptr);
	}
	
	TEST("DVectorSize", DVectorSize(vector_t), num2);
	
	DVectorDestroy(vector_t);
}

void PopBackTest()
{
	size_t num0 = 0, num1 = 15, num2 = 4, num3 = 6534, num4 = 432, num5 = 101010;
	size_t *num1_ptr = &num1, *num2_ptr = &num2, *num3_ptr = &num3, *num4_ptr = &num4, *num5_ptr = &num5;
	
	struct dynamic_vector *vector_t = DVectorCreate(num1);
	
	DVectorPushBack(vector_t, num1_ptr);
	DVectorPushBack(vector_t, num2_ptr);
	DVectorPushBack(vector_t, num3_ptr);
	DVectorPushBack(vector_t, num4_ptr);
	DVectorPushBack(vector_t, num5_ptr);
	
	DVectorPopBack(vector_t);
	num0 = *(size_t *)DVectorGetElement(vector_t, 3);
	TEST("DVectorPopBack()", num0, num4);
	DVectorPopBack(vector_t);
	num0 = *(size_t *)DVectorGetElement(vector_t, 2);
	TEST("DVectorPopBack()", num0, num3);
	DVectorPopBack(vector_t);
	num0 = *(size_t *)DVectorGetElement(vector_t, 1);
	TEST("DVectorPopBack()", num0, num2);
	DVectorPopBack(vector_t);
	num0 = *(size_t *)DVectorGetElement(vector_t, 0);
	TEST("DVectorPopBack()", num0, num1);

	DVectorDestroy(vector_t);
}

void SetElementTest()
{
	size_t num1 = 15, num2 = 4, num3 = 6534, num4 = 432, num5 = 101010, dummy = 123, i = 0;
	size_t *num1_ptr = &num1, *num2_ptr = &num2, *num3_ptr = &num3, *num4_ptr = &num4, *num5_ptr = &num5, *dummy_ptr = &dummy;
	
	struct dynamic_vector *vector_t = DVectorCreate(num1);
	
	DVectorPushBack(vector_t, num1_ptr);
	DVectorPushBack(vector_t, num2_ptr);
	DVectorPushBack(vector_t, num3_ptr);
	DVectorPushBack(vector_t, num4_ptr);
	DVectorPushBack(vector_t, num5_ptr);
	
	for (i = 0; i < 5; ++i)
	{
		DVectorSetItem(vector_t, i, num1_ptr);
		dummy = *(size_t *)DVectorGetElement(vector_t, i);
		TEST("DVectorSetItem()", *dummy_ptr, *num1_ptr);
	}
	DVectorDestroy(vector_t);
}

void ReserveShrinkTest()
{
	size_t size = 10, new_size = 20, smaller = 6, i = 0, *num_ptr = &size; 
	struct dynamic_vector *vector_t = DVectorCreate(size);
	DVectorReserve(vector_t, new_size);
	TEST("DVectorReserve()", DVectorCapacity(vector_t), new_size);
	
	for (i = 0; i < 5; ++i)
	{
		DVectorPushBack(vector_t, num_ptr);
	}
	
	DVectorShrinkToFit(vector_t);
	TEST("DVectorShrinkToFit()", DVectorCapacity(vector_t), smaller);
	
	DVectorDestroy(vector_t);
}
