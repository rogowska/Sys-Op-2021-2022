/*oliwia rogowska*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    
    printf("Identyfikator użytkownika: %d\n", getuid());
    printf("Identyfikator grupy użytkownika: %d\n", getgid());
    printf("Identyfikator procesu: %d\n", getpid());
    printf("Identyfikator procesu macierzystego: %d\n", getppid());
    printf("Identyfikator grupy procesów: %d\n", getpgrp());

return 0;
}

