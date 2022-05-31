#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

static void PrintPing(int pid, siginfo_t *ppid, void *ptr);
pid_t pid;

int main()
{
    struct sigaction ping;
    
    ping.sa_flags = SA_SIGINFO;
    ping.sa_sigaction = PrintPing;
    
    sigaction(SIGUSR1, &ping, NULL);

    while (1)
    {
        pause();
    }
    return (0);
}

static void PrintPing(int pid, siginfo_t *ppid, void *ptr)
{
    pid = ppid->si_pid;
    printf("\nPing\n");
    sleep(1);
    fflush(stdout);
    kill(pid, SIGUSR2);
}
