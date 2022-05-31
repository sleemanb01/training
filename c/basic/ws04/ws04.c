#include<stdio.h>
#include<stdlib.h>


void Af()
{
	printf("A-Pressed\n");
}

void Tf()
{
	printf("T-Pressed\n");
} 

void Nf()
{
	/*Nothing*/
}

/* name of func types*/
typedef void (*pf)(void);

int main()
{
	int i;
	unsigned char input;
	/*void (*pf[4])(void) = {Af, Tf, Ef, Nf};*/
	pf pf[256];
	system("stty -icanon -echo");
	
	for(i = 0; i<256 ; ++i)
		{
			pf[i] = &Nf;		
		}
	
	pf['A'] = &Af;
	pf['T'] = &Tf;
	pf['a'] = &Af;
	pf['t'] = &Tf;
		
	while(input != 0x1B)
	{
		input = (unsigned char)getchar();

		pf[input]();
	}
	
	system("stty icanon echo");	
	
	return 0;
}
