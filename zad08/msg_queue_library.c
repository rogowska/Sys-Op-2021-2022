#include <fcntl.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "msg_queue_library.h"

mqd_t msq_open_readonly(name)
{
    mqd_t desc;
    desc = mq_open(name, O_RDONLY);
    if (desc == -1)
    {
        perror("mq_open error");
        printf("Exiting...\n");
        exit(EXIT_FAILURE);
    }
    return desc;
};


mqd_t msq_open_writeonly(name)
{
    mqd_t desc;
    desc = mq_open(name, O_WRONLY);
    if (desc == -1)
    {
        perror("mq_open error");
        printf("Exiting...\n");
        exit(EXIT_FAILURE);
    }
    return desc;
};


mqd_t msq_create(name)
{
    mqd_t desc;
    desc = mq_open(name, O_CREAT | O_EXCL, 0666, NULL);
    if (desc == -1)
    {
        perror("mq_open error");
        printf("Exiting...\n");
        exit(EXIT_FAILURE);
    }
    return desc;
};


void msq_close(desc)
{
    if (mq_close(desc) == -1)
    {
        perror("mq_close error");
        printf("Exiting...\n");
        exit(EXIT_FAILURE);
    }
};


void msq_unlink(name)
{
    if (mq_unlink(name) == -1)
    {
        perror("mq_unlink error");
        printf("Exiting...\n");
        exit(EXIT_FAILURE);
    }
};


void msq_send(desc, msg, prio)
{
    int val;
    val = mq_send(desc, msg, sizeof(msg), prio);
    if (val == -1)
    {
        perror("mq_send error");
        printf("Exiting...\n");
        exit(EXIT_FAILURE);
    }
};


void msq_recieve(desc, buff)
{
    int val;
    val = mq_recieve(desc, buff, sizeof(buff), NULL);
    if (val == -1)
    {
        perror("mq_recieve error");
        printf("Exiting...\n");
        exit(EXIT_FAILURE);
    }
};


void msq_getattr(desc, attr)
{
    int val;
    val = mq_getattr(desc, attr)
    {
        perror("mq_getattr error");
        printf("Exiting...\n");
        exit(EXIT_FAILURE);
    }
};


void msq_setattr(desc, newattr, oldattr)
{
    int val;
    val = mq_setattr(desc, newattr, oldattr);
    if (val == -1)
    {
        perror("mq_setattr error");
        printf("Exiting...\n");
        exit(EXIT_FAILURE);
    }
};
