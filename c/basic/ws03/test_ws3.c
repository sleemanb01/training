#include<stdio.h>
#include<stdlib.h>

int main()
{
	int size;
	printf("Enter number of soldiers:\n");
	scanf("%d",&size);
	printf("Last standing soldier is number %d\n",Josephus(size));
	
	return 0;
}
