#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(){
printf("Proces potomny - Identyfikator użytkownika: %d\n", getuid());
printf("Proces potomny - Identyfikator grupy użytkownika: %d\n", getgid());
printf("Proces potomny - Identyfikator procesu: %d\n", getpid());
printf("Proces potomny - Identyfikator procesu macierzystego: %d\n", getppid());
printf("Proces potomny - Identyfikator grupy procesów: %d\n\n", getpgrp());
return 0;
}