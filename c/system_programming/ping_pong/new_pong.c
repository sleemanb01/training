#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

static void PrintPong(int pid);
pid_t pid;

int main(int argc, char *argv[])
{
    struct sigaction pong;
    sigset_t mask;
    pid = atoi(argv[1]);
    
    sigfillset(&mask);
    pong.sa_handler = PrintPong;
    pong.sa_mask = mask;
    sigaction(SIGUSR2, &pong, NULL);

    kill(pid, SIGUSR1);
    while (1)
    {
        pause();
    }
    return (0);
}

static void PrintPong(int num)
{
    printf("\nPong\n");
    sleep(1);
    fflush(stdout);
    kill(pid, SIGUSR1);
}
