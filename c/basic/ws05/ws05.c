/***************************************************
* NAME          : SLEEMAN NABWANI
* EXERCISE NAME : WS05
* REVIEWER NAME : 
*****************************************************/

#include<stdio.h>   /* for print and scan f*/
#include<stdlib.h>  /* for NULL */
#include<string.h>  /* for string functions */

#define UNUSED(x) (void)(x)

#define BUFFER_SIZE 1024

static char path[29] = "/home/sleeman/c/ws05/t.txt"; 

/* functions signature */
void fileAppend();
void chainOR();

/* Extra */
int copyFile(char *first, char *second);

/* chain of responsibilties functions */
void comparison(char *data, int i);
void removeFunc(char *data);
void countFunc(char *data);
void exitFunc(char *data);
void addToBegining(char *data);
void defaultHandle(char *data);

int main()
{
	/*********************************** PHASE 1 ***********************************/
	
	/*printf("*** File Append ***\n\n");
	fileAppend();*/
	
	/*********************************** PHASE 2 ***********************************/
	
	printf("\n\n *** chain of responsibility *** \n\n");
	chainOR();
	
	/*********************************** PHASE 1 ***********************************/
	
	/*printf("File Append\n");
	fileAppend();*/
	
	return 0;
}

/*********************************** FILE APPEND ***********************************/
void fileAppend()
{
	FILE *fp;
	char data[BUFFER_SIZE];
	char filename[8];
	
	printf("Enter a file name (maximum 4 chars)\n");
	fgets(filename, BUFFER_SIZE, stdin);
	strcat(path,filename);
	
	fp = fopen(path,"a");
	if(NULL == fp)         /* FILE OPEN/CREATE CHECK */
	{
		perror("Error opening file.");
	}
	else
	{
		while(1)
		{
			printf("Enter content && Enter quit to stop\n");
			fgets(data, BUFFER_SIZE, stdin);
			if(strcmp(data,"quit\n") != 0)
			{
				fputs(data,fp);
			}
			else
			{
				break;
			}
		}
	}
	fclose(fp);
}

/* LUTs for chain of responsibilties */
typedef void(*p_type)(char *data);
char *operations[] = {"-remove", "-count", "-exit", "<"};
p_type functions[] = {removeFunc, countFunc, exitFunc, addToBegining};

struct handler{
	char *str;
	p_type f1;
	void(*f2)(char *data, int i);
	}handlers[5];
	
static int flag = 1;

/************************ CHAIN OF RESPONSIBILTIES ************************/
void chainOR()
{
	int i;
	char data[BUFFER_SIZE];
	
	for(i = 0; i < 4 ; ++i)
	{
		handlers[i].str = operations[i];
		handlers[i].f1 = functions[i];
		handlers[i].f2 = &comparison;
	}
		handlers[4].str = "default";
		handlers[4].f1 = &defaultHandle;
		handlers[4].f2 = &comparison;
	

		printf("Commands : -remove , -count, -exit, <...\n");
		printf("Enter content\n");

		while(1 == flag)
		{
			scanf("%[^\n]%*c", data);
			handlers[0].f2(data, 0);
		}
}

/************************ COMPARISON ************************/
void comparison(char *data, int i)
{
	if(strcmp(data,handlers[i].str) == 0 || i == 4 )
	{
		handlers[i].f1(data);
	}
	else if(data[0] == '<')
	{
		handlers[3].f1(data);
	}
	else
	{
		++i;
		comparison(data,i);
	}
}

/************************ DEFAULT HANDLER ************************/
void defaultHandle(char *data)
{
	FILE *fp;
	fp = fopen(path,"a");
	
	if(NULL == fp)         /* FILE OPEN/CREATE CHECK */
	{
		perror("Error opening file.\n");
	}
	else
	{
		fputs(data,fp);
		fputs("\n",fp);
	}
	
	fclose(fp);
}

/************************ REMOVE ************************/
void removeFunc(char *data)
{
	if (remove(path) == 0) 
	{
        	printf("The file is deleted successfully.\n");
	} 
	else
	{
        	printf("The file is not deleted.\n");
	}
}

/************************ LINES COUNT ************************/
void countFunc(char *data)
{
	FILE *fp;
	char c;
	int count = 0;
	fp = fopen(path, "r");

	if (fp == NULL)
	{
		printf("Could not open file %s\n", path);
	}
	else
	{
		for (c = getc(fp); c != EOF; c = getc(fp)) /* get char, check it's not end of file */
		{
			if (c == '\n')
			{
				++count;
			}
		}
		
		fclose(fp);
		printf("The file %s has %d lines\n ", path, count);
	}
}

/************************ EXIT ************************/
void exitFunc(char *data)
{
	flag = 0;
}

/************************ ADD TO BEGINING ************************/
void addToBegining(char *data)
{
	FILE *target;
	target = fopen("/home/sleeman/c/ws05/tmp.txt", "w");

	if (target == NULL)
	{
		printf("Could not open file %s\n", path);
	}
	else
	{
		++data;                         /* skip the first char '<' */
		fputs(data,target);             /* enter the data at the begining */
		fputs("\n",target);
		fclose(target);
	}
	
	if(copyFile(path,"/home/sleeman/c/ws05/tmp.txt") == 1)
	{
		if (remove(path) == 0) 
		{
			if(copyFile("/home/sleeman/c/ws05/tmp.txt",path))
			{
				if (remove("/home/sleeman/c/ws05/tmp.txt") != 0) 
				{
					printf("The file is not deleted.\n");
				} 
			}
			else
			{
				printf("The file is not deleted.\n");
			}
		} 
		else
		{
			printf("The file is not deleted.\n");
		}
	}
	else
	{
		printf("ERROR! copying file.\n");
	}
	
}

/*********************************** COPY FILE ***********************************/
int copyFile(char *first, char *second)
{
	int ret = 0;
	char ch;
	FILE *source,*target;

	target = fopen(second, "a");
	
	if (target == NULL)
	{
		printf("Could not open file %s", second);
	}
	else
	{
		source = fopen(first, "r");

		if (source == NULL)
		{
			printf("Could not open file %s\n", first);
		}
		else
		{
			while ((ch = fgetc(source)) != EOF) /* copy file to another */
			{
				fputc(ch, target);
			}
			ret = 1;
			printf("File copied successfully.\n");
			fclose(source);
			fclose(target);
		}
	}
	return ret;
}
