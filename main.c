/*oliwia rogowska*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int i, id;

    /*podpunkt a)
    printf("Identyfikator użytkownika: %d\n", getuid());
    printf("Identyfikator grupy użytkownika: %d\n", getgid());
    printf("Identyfikator procesu: %d\n", getpid());
    printf("Identyfikator procesu macierzystego: %d\n", getppid());
    printf("Identyfikator grupy procesów: %d\n\n", getpgrp());

    /*podpunkt b)
    for (i = 0; i < 3; i++)
    {
        id = fork();
        if (id > 0)
        {
            if (i == 0)
            {
                printf("Identyfikator użytkownika: %d\n", getuid());
                printf("Identyfikator grupy użytkownika: %d\n", getgid());
                printf("Identyfikator procesu: %d\n", getpid());
                printf("Identyfikator procesu macierzystego: %d\n", getppid());
                printf("Identyfikator grupy procesów: %d\n\n", getpgrp());
            }
            wait(NULL);
        }
        else if (id == 0)
        {
            printf("Proces potomny - Identyfikator użytkownika: %d\n", getuid());
            printf("Proces potomny - Identyfikator grupy użytkownika: %d\n", getgid());
            printf("Proces potomny - Identyfikator procesu: %d\n", getpid());
            printf("Proces potomny - Identyfikator procesu macierzystego: %d\n", getppid());
            printf("Proces potomny - Identyfikator grupy procesów: %d\n\n", getpgrp());
        }
        else
        {
            perror("fork error\n");
            exit(EXIT_FAILURE);
        }
    }
    */
    /*podpunkt c)*/
    for (i = 0; i < 3; i++)
    {
        id = fork();
        if (id > 0)
        {
            if (i == 0)
            {
                printf("Identyfikator użytkownika: %d\n", getuid());
                printf("Identyfikator grupy użytkownika: %d\n", getgid());
                printf("Identyfikator procesu: %d\n", getpid());
                printf("Identyfikator procesu macierzystego: %d\n", getppid());
                printf("Identyfikator grupy procesów: %d\n\n", getpgrp());
            }
        }
        else if (id == 0)
        {
            sleep(2);
            printf("Proces potomny - Identyfikator użytkownika: %d\n", getuid());
            printf("Proces potomny - Identyfikator grupy użytkownika: %d\n", getgid());
            printf("Proces potomny - Identyfikator procesu: %d\n", getpid());
            printf("Proces potomny - Identyfikator procesu macierzystego: %d\n", getppid());
            printf("Proces potomny - Identyfikator grupy procesów: %d\n\n", getpgrp());
            if (i == 2)
            {
                system("pstree -p");
            }
        }
        else
        {
            perror("fork error\n");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}