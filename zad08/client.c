#include <fcntl.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "msg_queue_library.h"

mqd_t serverDesc, clientDesc;
char cName[10];

/*tworzenie funkcji rejestrowanych przez atexit i signal*/

void sQueueClose()
{
    printf("sQueueClose przed\n");
    msq_close(serverDesc);
    printf("sQueueClose po\n");
}

void cQueueClose()
{
    printf("cQueueClose przed\n");
    msq_unlink(cName);
    msq_close(clientDesc);
    printf("cQueueClose po\n");
}

void exit_signal(int signal)
{
    printf("\nSygnał przerwania, zamykanie kolejki\n");
    exit(EXIT_SUCCESS);
}

int main()
{

    if (signal(SIGINT, exit_signal) == SIG_ERR)
    {
        perror("Signal error:");
        exit(EXIT_FAILURE);
    }

    atexit(sQueueClose);
    atexit(cQueueClose);

    /*definiowanie zmiennych*/
    int pid;
    char msgReceived[60];
    char str[70];
    char strRead[60];

    /*odczytywanie pid procesu kilenta*/
    pid = getpid();
    sprintf(cName, "/%d", pid);

    struct mq_attr newattr;
    newattr.mq_flags = 0;
    newattr.mq_maxmsg = 10;
    newattr.mq_msgsize = MSGLENGTH;
    newattr.mq_curmsgs = 0;

    /*otwieranie kolejek dla klienta i serwera*/
    clientDesc = msq_create(cName, &newattr);
    clientDesc = msq_open_readonly(cName);
    serverDesc = msq_open_writeonly(SERVERQUEUE);

    /*wysyłanie komunikatów do serwera*/
    while (fgets(strRead, sizeof(strRead), stdin) != NULL)
    {
        printf("Jestem w petli\n");
        sprintf(str, "%d %s", pid, strRead);
        printf("%s\n", str);
        sleep(rand()%10);
        msq_send(serverDesc, str, MSGLENGTH, 0);
        printf("Pytanie wysłane do serwera\n");
        /*odczytanie komunikatu z serwera*/
        msq_receive(clientDesc, msgReceived, MSGLENGTH);
        /*wypisanie komunikatu na konsolę*/
        printf("Otrzymana odpowiedź: %s\n", msgReceived);
        printf("\n");
    }

    printf("Client process exiting...\n");
    exit(EXIT_SUCCESS);
}