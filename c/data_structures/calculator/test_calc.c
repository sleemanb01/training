#include <stdlib.h>
#include <string.h>

#include "tests.h"
#include "calc.h"

int main()
{
	char input[15];
	double result = 0.0;

	strcpy(input,"20 / 4 + 5 * 4");
	result = CalcCulate(input);

	TEST_EQUAL("Calculate()",result,25);

	PASS;

	return 0;
}