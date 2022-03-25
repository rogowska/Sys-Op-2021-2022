/*Oliwia Rogowska*/
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Wrong number of arguments\n");
        exit(EXIT_FAILURE);
    }
    char *errmsg;
    int signumber = strtol(argv[1], NULL, 0);
    int sigaction = strtol(argv[2], NULL, 0);

    if(sigaction!= 1||2||3){
        printf("Wrong action number\n");
        exit(EXIT_FAILURE);
    }

    void custom_signalhandler()
    {
        printf("Using a custom signalhander\n");
    }

    if (sigaction == 1)
    {
        if (signal(signumber, SIG_DFL) == SIG_ERR)
        {
            sprintf(errmsg, "Signal %d%s\n", signumber, " error");
            perror(errmsg);
            exit(EXIT_FAILURE);
        }
    }
    /*
    if (sigaction == 2)
    {
        if (signal(signumber, SIG_IGN) == SIG_ERR)
        {
            perror("Signal %d%s\n", signumber, " error");
            exit(EXIT_FAILURE);
        }
    }
    if (sigaction == 3)
    {
        if (signal(signumber, custom_signalhandler) == SIG_ERR)
        {
            perror("Signal %d%s\n", signumber, " error");
            exit(EXIT_FAILURE);
        }
    }*/

    return 0;
}