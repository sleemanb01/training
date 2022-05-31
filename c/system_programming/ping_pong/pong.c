#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

static void PrintPong(int pid);

int main()
{
    struct sigaction pong;
    sigset_t mask;

    sigfillset(&mask);

    pong.sa_handler = PrintPong;
    pong.sa_mask = mask;

    sigaction(SIGUSR1, &pong, NULL);

    printf("\n");

    while (1)
    {
        pause();
    }
    return (0);
}

static void PrintPong(int pid)
{
    sleep(1);
    printf("\nPong\n");
    fflush(stdout);
}
