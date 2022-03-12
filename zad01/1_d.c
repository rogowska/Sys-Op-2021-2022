/*oliwia rogowska*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

int main()
{
    int i, id;
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
            /*odpowiednia redukcja liczby sekund dla funkcji sleep ze względu na iterację*/
            /*zapewniamy dłużej(4>3) działający proces rodzica aby nie osierocić procesów potomnych*/
            sleep(4 - i);
        }
        else if (id == 0)
        {
            printf("Proces potomny - Identyfikator użytkownika: %d\n", getuid());
            printf("Proces potomny - Identyfikator grupy użytkownika: %d\n", getgid());
            printf("Proces potomny - Identyfikator procesu: %d\n", getpid());
            printf("Proces potomny - Identyfikator procesu macierzystego: %d\n", getppid());
            printf("Proces potomny - Identyfikator grupy procesów: %d\n\n", getpgrp());
            sleep(3 - i);
        }
        else
        {
            perror("fork error\n");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}