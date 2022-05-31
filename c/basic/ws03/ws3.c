/***************************************************
* NAME : SLEEMAN NABWANI
* EXERCISE NAME : WS03
* REVIEWER NAME : ROTEM BEN SHIMON
*****************************************************/

#include<stdio.h>
#include<stddef.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/******************** JOSEPHUS *******************/
int Josephus(int size)
{
	int i;
	int result = -1;
	int *arr =(int *)malloc(size * sizeof(int *));
	
	for(i = 0; i < size; ++i)
	{
		*(arr +i) = 1;
	}
	
	killNextSoldier(arr , size, 0);
	result = findIndex(arr,size);
	free(arr);
	return result;
	
}

/************** FIND INDEX *************/
int findIndex(int *arr, int size)
{
	int i;
	
	for(i = 0; i < size; ++i)
	{
		if(arr[i] == 1)
			break;
	}
	
	return i;
}

/************** PRINT ARRAY *************/
void printArray(int *arr, int size)
{
	int i;
	
	for(i = 0; i < size; ++i)
	{
		printf("a[%d] = %d\n",i,arr[i]);
	}
	printf("-------------------------------------------\n");
}


/************** SUM ALL ALIVE SOLDIERS *************/
int sumAliveSoldiers(int *arr, int size)
{
	int i;
	int sum = 0;
	
	for(i = 0; i < size; ++i)
	{
		sum += arr[i];
	}
	
	return sum;
}

/************** KILL *************/
int killNextSoldier(int *arr, int size, int k)
{
	int i;
	int killFlag = k;
	/*printArray(arr,size); >>> OPTIONAL CHECK FOR BETTER UNDERSTANDING*/
	for(i = 0; i < size; ++i)
	{
		if(arr[i] == 1)
		{
			if(killFlag == 1)
			{
				arr[i]=0;
				killFlag = 0;
			}
			else
			{
				killFlag = 1;
			}
		}
	}
	
	
	
	if(sumAliveSoldiers(arr, size) == 1)
		return 0;
	
	return killNextSoldier(arr, size, killFlag);
}


