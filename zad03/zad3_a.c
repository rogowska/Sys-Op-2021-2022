/*Oliwia Rogowska*/
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        printf("Wrong number of arguments (expected: signal number and action number)\n");
        exit(EXIT_FAILURE);
    }
    char errmsg[20];

    /*argument conversion from string to int*/
    int signumber = strtol(argv[1], NULL, 0);
    int sigaction = strtol(argv[2], NULL, 0);

    /*sigaction validation*/
    if ((sigaction != 1) && (sigaction != 2) && (sigaction != 3))
    {
        printf("Wrong action number (expected 1, 2 or 3)\n");
        exit(EXIT_FAILURE);
    }

    void custom_signalhandler(int sig)
    {
        printf("Using a custom signalhander for signal number:%d\n", sig);
    }
    
    if (sigaction == 1)
    {
        printf("Default signalhander will be performed for signal number:%d\n", signumber);
        /* Install a signal handler. */
        if (signal(signumber, SIG_DFL) == SIG_ERR)
        {
            sprintf(errmsg, "Signal %d%s", signumber, " error");
            perror(errmsg);
            exit(EXIT_FAILURE);
        }
    }

    if (sigaction == 2)
    {
        printf("Ignoring signal number:%d\n", signumber);
        /* Install a signal handler. */
        if (signal(signumber, SIG_IGN) == SIG_ERR)
        {
            sprintf(errmsg, "Signal %d%s", signumber, " error");
            perror(errmsg);
            exit(EXIT_FAILURE);
        }
    }
    if (sigaction == 3)
    {
        /* Install a signal handler. */
        if (signal(signumber, custom_signalhandler) == SIG_ERR)
        {
            sprintf(errmsg, "Signal %d%s", signumber, " error");
            perror(errmsg);
            exit(EXIT_FAILURE);
        }
    }

    pause();

    return 0;
}