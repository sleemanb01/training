#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "wd.h"

typedef struct tls{

    char *path;
    int pid;
    int is_wd;

}tls_ty;

/****************************** MAIN *************************************/

int main()
{
    tls_ty *tls;

    tls = malloc(sizeof(struct tls));
    if(!tls)
    {
        printf("*** MALLOC ERROR ***\n");
        return MEM_ERR;
    }

    tls->path = getenv("client_path");
    tls->pid = getppid();
    tls->is_wd = 1;

    SetupWD(tls);

	return 0;
}