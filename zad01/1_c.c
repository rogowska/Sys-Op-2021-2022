/*oliwia rogowska*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

int main()
{
    int i, id;
    char str[30];

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
                sprintf(str, "pstree -p -s %d", getpid());
                system(str);
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