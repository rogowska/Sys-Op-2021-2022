/*oliwia rogowska*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

int main()
{
    int i, id, check;
    char cmd[30], err_str[]="Następujące polecenie nie mogło zostać wykonane: ";

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
            /*przygotowanie polecenia pstree dla bieżącego procesu*/
            sprintf(cmd, "pstree -p -s %d", getpid());
            check = system(cmd);
            if (check == -1)
            {
                strncat(err_str, cmd, 20);
                perror(err_str);
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
