/*Oliwia Rogowska*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Wrong number of arguments (expected: signal number and action number)\n");
        exit(EXIT_FAILURE);
    }

    int id;
    char *signumber_str = argv[1];
    char *sigaction_str = argv[2];
    int signumber_int = strtol(argv[1], NULL, 0);

    /*tworzenie procesu macierzystego i potomnego*/
    id = fork();

    if (id > 0)
    {
        /*oczekiwanie na uruchomienie procesu potomnego*/
        while ((kill(id, 0) == -1) || (errno == ESRCH))
        {
            errno = ETIME;
        }
        sleep(1);
        /*wysłanie sygnału do procesu potomnego*/
        kill(id, signumber_int);
    }
    else if (id == 0)
    {
        /*uruchomienie programu obsługi sygnałów w procesie potomnym*/
        execlp("./zad3_a.x", "zad3_a.x", signumber_str, sigaction_str, NULL);
        perror("execlp error");
    }
    else
    {
        perror("fork error\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}