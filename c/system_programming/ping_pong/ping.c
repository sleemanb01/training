#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

static void PrintPing(int pid);

int main()
{
    struct sigaction ping, old_ping;
    pid_t child;
    char *child_file = "./pong.out";
    char *args[2];
    
    args[0] = child_file;
    args[1] = NULL;
    
    ping.sa_handler = &PrintPing;
    sigaction(SIGUSR2, &ping, &old_ping);

    child = fork();
    if (child == 0)
    {
        execvp(args[0], args);
    }
    else if (child > 0)
    {
        while (1)
        {
            pause();
            kill(child, SIGUSR1);
        }
    }
    return (0);
}

static void PrintPing(int pid)
{
    sleep(1);
    printf("\nPing\n");
    fflush(stdout);
}
