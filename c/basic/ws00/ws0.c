#include<stdio.h>

/************EX4****************/
void print()
{
	printf("\"Hello World\"");
}	

/************EX5****************/
int powTen(int *p)
{
	int num=1;
	int powNum = *p;
	for(int i=0;i<powNum;i++)
	{
		num = num * 10 ;
	}
	*p = num;
}

/************EX6****************/
int flipNumber(int n)
{
	int result=0;
	while (n > 0)
		{
			result *=10;
			result += n % 10;
			n = n / 10;
		}
	return result
}
	
/************EX7****************/
void swapValues(int *x, int *y)
{
	int t;
	t = *x;
	*x = *y;
	*y = t;
}

int main()
{
	int n5 = 2;
	int n6 = 213;
	print();  //EX4
	powTen(&n); //EX5
	flipNumber(n6); //EX6
	swapValues(n5,n6); //EX7
	return 0;
}
