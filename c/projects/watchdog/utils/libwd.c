#define _POSIX_C_SOURCE 200809L

#include "wdinternals.h"

/****************************** GLOBAL *************************************/

#define LOG( X ) fputs(X,stderr);
#define THREADS 1
#define PATH_MAX 80

pthread_t tid[THREADS];
sem_t sem1, sem2;

volatile size_t counter = 0;
int interval = 0;
size_t max_miss = 0;

 sched_t *sched = NULL;

/****************************** FUNCS *************************************/

int MakeMeImmortal(const char* app_argv[], int sol_interval, int max_sol_miss)
{
    int i;
    tls_ty *args = NULL;
    sigset_t set;

    args = malloc(sizeof(struct tls));
    if(!args)
    {
        LOG("*** MALLOC ERROR ***");
        return MEM_ERR;
    }

    if ((0 != sem_init(&sem1, 0, 0)) && (0 != sem_init(&sem2, 0, 0)))
    {
        LOG("*** SEM ERROR ***");
        return SYS_ERR;
    }
    
    strcpy(args->path,app_argv[0]);
    interval = sol_interval;
    max_miss = max_sol_miss;

    for(i = 0; i < THREADS; ++i)
    {
        if(pthread_create(&(tid[i]), NULL, InitWD, args))
        {
            LOG("*** THREAD CREATION ERROR ***");
            return SYS_ERR;
        }
    }

    SetClientHandlers();

    sem_wait(&sem1);

    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

	return SUCCESS;
}

/******************************/
int DNR()
{
    SchedAdd(sched,StopTask,NULL,0);

    SchedDestroy(sched);

    sem_destroy(&sem1);
    sem_destroy(&sem2);

	return SUCCESS;
}

/******************************/
void *InitWD(void *args)
{
    int i;
    pid_t child;
    char cwd[PATH_MAX];
    tls_ty *tls = (tls_ty*)args;

    getcwd(cwd, sizeof(cwd));

    setenv("client_path", cwd, 1);

    child = fork();

    if (child == 0)
    {
       if(-1 == execvp(tls->path, NULL))
        {
            LOG("*** EXECVP ERROR ***");
        }
    }

    sem_wait(&sem2);

    sem_post(&sem1);

    tls->pid = child;
    tls->is_wd = 0;

    StartSched(tls);
 
    for(i = 0; i < THREADS; ++i)
     {
         pthread_join(tid[i], NULL);
     }

    return NULL;
}

/******************************/
void StartSched(tls_ty *tls)
{
    sched = SchedCreate();

    SchedAdd(sched,Task,(void*)tls,interval);

    if(tls->is_wd)
    {
        sem_post(&sem2);
    }

    SchedRun(sched);
}

/******************************/
void SetClientHandlers(void)
{
    struct sigaction handler;
    sigset_t mask;

    sigfillset(&mask);
    handler.sa_handler = Handler;
    handler.sa_mask = mask;

    sigaction(SIGUSR1, &handler, NULL);
}

/******************************/
void SetWDHandlers(void)
{
    struct sigaction handler, handler2;
    sigset_t mask;

    sigfillset(&mask);
    handler.sa_handler = Handler;
    handler2.sa_mask = mask;


    sigaction(SIGUSR1, &handler, NULL);
    sigaction(SIGUSR2, &handler2, NULL);
}

/******************************/
void Handler(int n)
{
    (void)n;
    counter = 0;
}

/******************************/
int Task(void *params)
{
    tls_ty *tls;
    tls = (tls_ty*)params;

    if(max_miss <= counter)
    {
        if(tls->is_wd)
        {
            InitWD((void*)tls);
        }
        else
        {
            InitClient((void*)tls);
        }
    }

    __sync_fetch_and_add(&counter,1);

    kill(tls->pid,SIGUSR1);

    return 1;
}

/******************************/
int SetupWD(tls_ty *tls)
{
    SetWDHandlers();

    StartSched(tls);

    return 1;
}

/******************************/
int StopTask(void *params)
{
    (void)params;
    SchedStop(sched);

    return 0;
}

/******************************/
void InitClient(void *args)
{
    pthread_t local;

    if(pthread_create(&local, NULL, Revive, args))
    {
        LOG("*** THREAD CREATION ERROR ***");
        return;
    }

    pthread_join(local, NULL);
}

/******************************/
void *Revive(void *args)
{
    tls_ty *tls;
    pid_t child;

    tls = (tls_ty*)args;

    child = fork();

    if (child == 0)
    {
        if(-1 == execvp(tls->path, NULL))
        {
            LOG("*** EXECVP ERROR ***");
        }
    }

    return NULL;
}