#include <fcntl.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "msg_queue_library.h"

extern serverQueue;

int main()
{
    /*tworzenie zmiennych*/
    mqd_t serverDesc, clientDesc;
    char *msgRecieved[60];
    char *msgSent[60];
    int pid, num1, num2, result;
    char operator;
    char *cName[10] = "/";

    /*otwieranie kolejki serwera*/

    serverDesc = msq_open_readonly(serverQueue);

    while (1)
    {
        /*odczytywanie wiadomości i pidu procesu klienta*/
        msq_recieve(serverDesc, msgRecieved);
        sscanf(msgRecieved, "%d %d%c%d", &pid, &num1, &operator, & num2);
        scanf(cName, pid);

        /*otwieranie kolejki procesu klienta*/
        clientDesc = msq_open_writeonly(cName);

        /*obliczanie wyniku*/
        if (operator== '+')
        {
            result = num1 + num2;
            sprintf(msgSent, result);
        }
        else if (operator== '-')
        {
            result = num1 - num2;
            sprintf(msgSent, result);
        }
        else if (operator== '*')
        {
            result = num1 * num2;
            sprintf(msgSent, result);
        }
        else if (operator== '/')
        {
            result = num1 / num2;
            sprintf(msgSent, result);
        }
        else
        {
            sprintf(msgSent, "Error: unknown operator\n");
        }


        /*wysyłanie wiadomości i zamykanie kolejki*/
        msq_send(clientDesc, msgSent, 0);
        msq_close(clientDesc);
    }
}