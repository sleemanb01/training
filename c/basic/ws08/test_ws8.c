/***************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : WS08 - STRUCTS
* REVIEWER NAME : SHAHAR AIZIK
*****************************************************/

#include<stdio.h>	/* print struct */
#include<stdlib.h>	/* malloc */
#include<string.h>	/* concat, strlen */
#include"ws8.h"

#define ARR_SIZE 3

/**** INCREASE READABILITY FUNCTIONS ****/
void printArr(Node *p);
void addToArr(Node *p);

int main()
{
	/***** Declaration *****/
	Node nodes[ARR_SIZE];
	int n = 12;
	float f = 8.0;
	char *s = (char *)malloc(7 * sizeof(char));
	strcpy(s, "struct");
	
	/***** Initializing *****/
	nodes[0].type = (int *) &n;
	nodes[0].Add = &Add2Int;
	nodes[0].Print = &PrintInt;
	nodes[0].Clean = &DoNothing;
	
	nodes[1].type = (float *) &f;
	nodes[1].Add = &Add2Flt;
	nodes[1].Print = &PrintFlt;
	nodes[1].Clean = &DoNothing;
	
	nodes[2].type = (char *) s;
	nodes[2].Add = &Add2Str;
	nodes[2].Print = &PrintStr;
	nodes[2].Clean = &CleanUpStr;
	
	printArr(nodes);
	
	addToArr(nodes);
	
	printArr(nodes);
	
	nodes[2].Clean(nodes[2].type);
	
		
	return 0;
}

/******** PRINT ARRAY *****/
void printArr(Node *p)
{
	int i;
	for(i = 0; i < ARR_SIZE ; ++i)
	{
		p[i].Print(p[i].type);
	}
}

/******** ADD TO ARRAY *****/
void addToArr(Node *p)
{
	int i;
	for(i = 0; i < ARR_SIZE ; ++i)
	{
		p[i].Add(p[i].type, 10);
	}
}
