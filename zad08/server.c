#include <fcntl.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "msg_queue_library.h"

mqd_t serverDesc, clientDesc;

void sQueueClose()
{
    printf("sQueueClose przed\n");
    msq_unlink(SERVERQUEUE);
    msq_close(serverDesc);
    printf("sQueueClose po\n");
}

void cQueueClose()
{
    printf("cQueueClose przed\n");
    msq_close(clientDesc);
    printf("cQueueClose po\n");
}

void exit_signal(int signal)
{
    printf("\nSygnał przerwania, zamykanie kolejki\n");
    atexit(sQueueClose);
    atexit(cQueueClose);
    exit(EXIT_SUCCESS);
}

int main()
{
    if (signal(SIGINT, exit_signal) == SIG_ERR)
    {
        perror("Signal error:");
        exit(EXIT_FAILURE);
    }

    /*tworzenie zmiennych*/
    struct mq_attr atributes;
    char msgReceived[MSGLENGTH];
    char msgSent[MSGLENGTH];
    int pid, num1, num2, result;
    char operator;
    char cName[10];

    struct mq_attr newattr;
    newattr.mq_flags = 0;
    newattr.mq_maxmsg = 10;
    newattr.mq_msgsize = MSGLENGTH;
    newattr.mq_curmsgs = 0;

    /*otwieranie kolejki serwera*/
    serverDesc = msq_create(SERVERQUEUE, &newattr);
    serverDesc = msq_open_readonly(SERVERQUEUE);

    msq_getattr(serverDesc, &atributes);
    printf("Utworzono kolejkę \"%s\" o atrybutach:\n", SERVERQUEUE);
    printf("mq_flags: = %ld\n", atributes.mq_flags);
    printf("mq_maxmsg: = %ld\n", atributes.mq_maxmsg);
    printf("mq_msgsize: = %ld\n", atributes.mq_msgsize);
    printf("mq_curmsgs: = %ld\n\n", atributes.mq_curmsgs);

    while (1)
    {
        /*odczytywanie wiadomości i pidu procesu klienta*/
        printf("Jestem przed msq_receive\n");
        msq_receive(serverDesc, msgReceived, MSGLENGTH);
        printf("%s\n", msgReceived);
        sleep(rand() % 10);
        sscanf(msgReceived, "%d %d%c%d", &pid, &num1, &operator, & num2);
        sprintf(cName, "/%d", pid);
        printf("%d %d %c %d\n", pid, num1, operator, num2);

        /*otwieranie kolejki procesu klienta*/
        printf("Otwieranie kolejki klienta\n");
        clientDesc = msq_open_writeonly(cName);

        /*obliczanie wyniku*/
        if (operator== '+')
        {
            printf("wykonywanie operacji +\n");
            result = num1 + num2;
            sprintf(msgSent, "%d", result);
        }
        else if (operator== '-')
        {
            printf("wykonywanie operacji -\n");
            result = num1 - num2;
            sprintf(msgSent, "%d", result);
        }
        else if (operator== '*')
        {
            printf("wykonywanie operacji *\n");
            result = num1 * num2;
            sprintf(msgSent, "%d", result);
        }
        else if (operator== '/')
        {
            printf("wykonywanie operacji /\n");
            result = num1 / num2;
            sprintf(msgSent, "%d", result);
        }
        else
        {
            sprintf(msgSent, "Error: unknown operator\n");
        }

        /*wysyłanie wiadomości i zamykanie kolejki*/
        printf("Odsyłanie odpowiedzi do klienta\n");
        msq_send(clientDesc, msgSent, MSGLENGTH, 0);
        msq_close(clientDesc);
    }
}