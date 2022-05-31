#include<stdio.h>
#include<stdlib.h>
#include"g.h"


int main()
{
	g_s = 3;
	printf("%d\n",g_s);
	foo();
	printf("%d\n",g_s);

	return 0;
}
