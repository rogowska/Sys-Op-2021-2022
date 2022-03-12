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
    /*podpunkt c)
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
    podpunkt d)
    unbuffer ./main | awk '{ print strftime("%H:%M:%S"), $0; fflush() }'*/
    /*for (i = 0; i < 3; i++)
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
    }*/
    /*podpunkt e)*/
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
            setpgid(getpid(), getpid());
            wait(NULL);
        }
        else if (id == 0)
        {
            setpgid(getpid(), getppid());
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

    return 0;
}

/*
16:13:17 Identyfikator użytkownika: 1000
16:13:17 Identyfikator grupy użytkownika: 1000
16:13:17 Identyfikator procesu: 27088
16:13:17 Identyfikator procesu macierzystego: 27086
16:13:17 Identyfikator grupy procesów: 27088
16:13:17 
16:13:17 Proces potomny - Identyfikator użytkownika: 1000
16:13:17 Proces potomny - Identyfikator grupy użytkownika: 1000
16:13:17 Proces potomny - Identyfikator procesu: 27093
16:13:17 Proces potomny - Identyfikator procesu macierzystego: 27088
16:13:17 Proces potomny - Identyfikator grupy procesów: 27088
16:13:17 
16:13:20 Proces potomny - Identyfikator użytkownika: 1000
16:13:20 Proces potomny - Identyfikator grupy użytkownika: 1000
16:13:20 Proces potomny - Identyfikator procesu: 27098
16:13:20 Proces potomny - Identyfikator procesu macierzystego: 27093
16:13:20 Proces potomny - Identyfikator grupy procesów: 27088
16:13:20 
16:13:21 Proces potomny - Identyfikator użytkownika: 1000
16:13:21 Proces potomny - Identyfikator grupy użytkownika: 1000
16:13:21 Proces potomny - Identyfikator procesu: 27099
16:13:21 Proces potomny - Identyfikator procesu macierzystego: 27088
16:13:21 Proces potomny - Identyfikator grupy procesów: 27088
16:13:21 
16:13:22 Proces potomny - Identyfikator użytkownika: 1000
16:13:22 Proces potomny - Identyfikator grupy użytkownika: 1000
16:13:22 Proces potomny - Identyfikator procesu: 27100
16:13:22 Proces potomny - Identyfikator procesu macierzystego: 27098
16:13:22 Proces potomny - Identyfikator grupy procesów: 27088
16:13:22 
16:13:23 Proces potomny - Identyfikator użytkownika: 1000
16:13:23 Proces potomny - Identyfikator grupy użytkownika: 1000
16:13:23 Proces potomny - Identyfikator procesu: 27101
16:13:23 Proces potomny - Identyfikator procesu macierzystego: 27099
16:13:23 Proces potomny - Identyfikator grupy procesów: 27088
16:13:23 
16:13:23 Proces potomny - Identyfikator użytkownika: 1000
16:13:23 Proces potomny - Identyfikator grupy użytkownika: 1000
16:13:23 Proces potomny - Identyfikator procesu: 27102
16:13:23 Proces potomny - Identyfikator procesu macierzystego: 27093
16:13:23 Proces potomny - Identyfikator grupy procesów: 27088
16:13:23 
16:13:24 Proces potomny - Identyfikator użytkownika: 1000
16:13:24 Proces potomny - Identyfikator grupy użytkownika: 1000
16:13:24 Proces potomny - Identyfikator procesu: 27103
16:13:24 Proces potomny - Identyfikator procesu macierzystego: 27088
16:13:24 Proces potomny - Identyfikator grupy procesów: 27088
16:13:24 
*/