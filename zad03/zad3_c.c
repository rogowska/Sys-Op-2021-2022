/*Oliwia Rogowska*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <wait.h>

int main(int argc, char *argv[])
{
    int i, id;

    if (argc != 3)
    {
        printf("Wrong number of arguments (expected: signal number and action number)\n");
        exit(EXIT_FAILURE);
    }
    char *signumber_str = argv[1];
    char *sigaction_str = argv[2];
    int signumber_int = strtol(argv[1], NULL, 0);
    id = fork();

    if (id > 0)
    {
        printf("Identyfikator procesu: %d\n", getpid());
        printf("Identyfikator procesu macierzystego: %d\n", getppid());
        printf("Identyfikator grupy procesów: %d\n\n", getpgrp());
        while ((kill(id, 0) == -1) || (errno == ESRCH))
        {
            errno = ETIME;
        }
        sleep(1);
        kill(id, signumber_int);
        wait(NULL);
    }
    else if (id == 0)
    {
        setpgid(getpid(), getpid());
        printf("Identyfikator procesu: %d\n", getpid());
        printf("Identyfikator procesu macierzystego: %d\n", getppid());
        printf("Identyfikator grupy procesów: %d\n\n", getpgrp());
        for (i = 0; i < 2; i++)
        {
            int id2 = fork();
            wait(NULL);
            if (id2 > 0)
            {
            }
            else if (id == 0)
            {
                execlp("./zad3_a.x", "zad3_a.x", signumber_str, sigaction_str, NULL);
                perror("execlp error");
                printf("Identyfikator procesu: %d\n", getpid());
                printf("Identyfikator procesu macierzystego: %d\n", getppid());
                printf("Identyfikator grupy procesów: %d\n\n", getpgrp());
            }
        }
    }
    return 0;
}