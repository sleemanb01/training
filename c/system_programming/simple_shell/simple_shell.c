/************************************************************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : SIMPLE SHELL
* REVIEWER NAME : AMIHAI
************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>    /* system */
#include <assert.h>    /* assert */
#include <string.h>    /* strcmp */
#include <stdlib.h>    /* malloc */
#include <sys/types.h> /* fork   */
#include <unistd.h>    /* fork   */
#include <signal.h>    /* signals*/
#include<sys/wait.h>   /* wait   */

/***********************************************************************************************
*                                      STRCUCTS/CONSTS                                          *
************************************************************************************************/

#define COMMAND_SIZE 80
#define EXIT "exit"

/***********************************************************************************************
*                                       MAIN                                                   *
************************************************************************************************/

int main()
{
	char *input = NULL;
	int pid, flag;


	input = malloc(COMMAND_SIZE);
	if(NULL == input)
	{
		printf("***MALLOC ERR***\n");
		return 0;

	}
	printf("Enter 1 for fork or 0 for system\n");
	scanf("%d", &flag);

	printf("*** To terminate enter exit ***\n");

	while(1)
	{
		printf("PID %d \nEnter a shell command \n", getpid());
		scanf("%s", input);

		if(0 == strcmp(input,EXIT))
		{
			return 0;
		}
		if(flag)
		{
			pid = fork();

			if(0 == pid)
			{
				execl("/bin/sh", "sh", "-c", input, (char*)NULL);
			}
			else
			{
				waitpid(pid, NULL, 0);
				continue;
			}
		}
		else
		{
			system(input);
		}
	}

	free(input);

	return 0;
}