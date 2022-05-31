#ifndef WDINTERNALS_H
#define WDINTERNALS_H

#include <stddef.h>         /* size_t  */ 
#include <stdlib.h>         /* malloc  */
#include <assert.h>         /* assert  */
#include <pthread.h>        /* threads */
#include <string.h>         /* memcpy  */
#include <time.h>           /* srand   */
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/types.h>
#include "../../../ds/scheduler/scheduler.h"
#include "wd.h"

/****************************** TLS STRUCT *************************************/

typedef struct tls{

    char *path;
    int pid;
    int is_wd;

}tls_ty;

/****************************** FUNCS *************************************/

void *InitWD(void *args);
void InitClient(void *args);
void StartSched(tls_ty *tls);

void SetClientHandlers(void);
void SetWDHandlers(void);
void Handler(int n);

int Task(void *params);
int StopTask(void *params);
void *Revive(void *args);

int SetupWD(tls_ty *tls);
void WDHandler(void);

#endif