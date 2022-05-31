#include <stdio.h>      /* printf */
#include <stdlib.h>     /* malloc */
#include <string.h>     /* strcpy */
#include <unistd.h>     /* sleep  */
#include <dlfcn.h>      /* dlopen */

/****************************** GLOBAL *************************************/

#define MAX 100
#define INTERVAL 2
#define MAX_MISS 3
#define PATH "utils/wd.c"
#define LIBRARY_PATH "utils/libwd.so"

#include "utils/wd.h"
#include "utils/wdinternals.h"

/****************************** MAIN *************************************/

int main(int argc, char **argv)
{
    int i;
    const char **args = NULL;
    void *handle;

    (void)argc;
    (void)argv;

    handle = dlopen(LIBRARY_PATH, RTLD_LAZY);
    if (!handle) 
    {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    args = malloc(strlen(PATH) + 1);
    if(!args)
    {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    args[0] = PATH;

    MakeMeImmortal(args, INTERVAL, MAX);

    for(i = 0; i < MAX; ++i)
    {
        sleep(1);
        printf("client here ... %d\n",i);
    }

    printf("calling DNR!\n");

    DNR();

    printf("Done!\n");

	return 0;
}
