/*oliwia rogowska*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int i, id;
    if(argc!=3){
        printf("Nieprawidłowa liczba argumentów\n");
        exit(EXIT_FAILURE);

    }
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
            execlp(argv[1], argv[2], NULL);
            perror("execlp error");
            _exit(2);
        }
        else
        {
            perror("fork error\n");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}