#include <fcntl.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "msg_queue_library.h"

/*tworzenie funkcji rejestrowanych przez atexit*/

/*void sQueueClose()
{
    msq_close(serverDesc);
}

void cQueueClose()
{
    msq_unlink(cName);
    msq_close(clientDesc);
}*/

int main()
{

    /*definiowanie zmiennych*/
    int pid;
    mqd_t serverDesc, clientDesc;
    char msgReceived[60];

    /*odczytywanie pid procesu kilenta*/
    char cName[10];
    pid = getpid();
    sprintf(cName, "/");
    sprintf(cName, "%d", pid);

    /*otwieranie kolejek dla klienta i serwera*/
    clientDesc = msq_create(cName);
    clientDesc = msq_open_readonly(cName);
    serverDesc = msq_open_writeonly(SERVERQUEUE);

    /*wysyłanie komunikatów do serwera*/
    while (!EOF)
    {
        char str[70];
        char strRead[60];
        sprintf(str, "/");
        sprintf(str, "%d", pid);
        fgets(strRead, sizeof(strRead), STDIN_FILENO);
        sprintf(str, "%s", strRead);
        msq_send(serverDesc, str, 0);
        /*odczytanie komunikatu z serwera*/
        msq_receive(clientDesc, msgReceived);
        /*wypisanie komunikatu na konsolę*/
        if (-1 == write(STDOUT_FILENO, strRead, sizeof(strRead)))
        {
            perror("write error");
            exit(EXIT_FAILURE);
        }
    }


    msq_close(serverDesc);
    msq_unlink(cName);
    msq_close(clientDesc);
    /*atexit(sQueueClose);
    atexit(cQueueClose);*/
    printf("Client process exiting...\n");
    exit(EXIT_SUCCESS);
}