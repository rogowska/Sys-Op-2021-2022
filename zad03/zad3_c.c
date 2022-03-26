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
    const int proc_nb = 3;

    if (argc != 3)
    {
        printf("Wrong number of arguments (expected: signal number and action number)\n");
        exit(EXIT_FAILURE);
    }
    char errmsg[20];
    char *signumber_str = argv[1];
    char *sigaction_str = argv[2];
    int signumber_int = strtol(argv[1], NULL, 0);

    /*tworzenie procesu macierzystego i potomnego*/
    id = fork();

    
    if (id > 0)
    {
        printf("Identyfikator procesu: %d\n", getpid());
        printf("Identyfikator procesu macierzystego: %d\n", getppid());
        printf("Identyfikator grupy procesów: %d\n\n", getpgrp());
        /*sprawdzenie istnienia procesu potomnego*/
        while ((kill(id, 0) == -1) || (errno == ESRCH))
        {
            errno = ETIME;
        }
        sleep(1);
        /*wysyłanie sygnałów do grupy procesów potomnych*/ 
        for (i = 0; i < proc_nb; i++)
        {
            sleep(1);
            kill(-id, signumber_int);
        }
        wait(NULL);
    }
    else if (id == 0)
    {
        /*ustawienie procesu potomnego jako lidera grupy*/
        setpgid(getpid(), getpid());
        /*obsługa sygnału - ignorowanie przez lidera grupy*/
        if (signal(signumber_int, SIG_IGN) == SIG_ERR)
        {
            sprintf(errmsg, "Signal %d%s", signumber_int, " error");
            perror(errmsg);
            exit(EXIT_FAILURE);
        }
        printf("Identyfikator procesu: %d\n", getpid());
        printf("Identyfikator procesu macierzystego: %d\n", getppid());
        printf("Identyfikator grupy procesów: %d\n\n", getpgrp());
        /*tworzenie procesów potomnych lidera grupy*/
        for (i = 0; i < proc_nb; i++)
        {
            int id2 = fork();
            /*oczekiwanie na zakończenie procesów potomnych i wyświetlenie ich statusu*/
            int waitVal = wait(NULL);
            if (waitVal != -1)
            {
                printf("Wait return value: %d\n", waitVal);
            }
            if (id2 > 0)
            {
            }
            else if (id == 0)
            {
                printf("Identyfikator procesu: %d\n", getpid());
                printf("Identyfikator procesu macierzystego: %d\n", getppid());
                printf("Identyfikator grupy procesów: %d\n\n", getpgrp());
                /*uruchomnienie programu obsługi sygnałów*/
                execlp("./zad3_a.x", "zad3_a.x", signumber_str, sigaction_str, NULL);
                perror("execlp error");
            }
        }
    }
    return 0;
}