#include <stdlib.h>
#include <stdio.h>
#include "semaph_library.h"

sem_t *semaph_init(const char *semaph_name, int oflag, mode_t mode, unsigned int semaph_value)
{
    sem_t *returnval = sem_open(semaph_name, oflag, mode, semaph_value);
    if (returnval == SEM_FAILED)
    {
        perror("semaph_init error");
        exit(-1);
    }
    return returnval;
}

sem_t *semaph_open(const char *semaph_name, int oflag)
{
    sem_t *returnval = sem_open(semaph_name, oflag);
    if (returnval == SEM_FAILED)
    {
        perror("semaph_open error");
        exit(-1);
    }
    return returnval;
}

void semaph_close(sem_t *semaph_address)
{
    if (sem_close(semaph_address) == -1)
    {
        perror("semaph_close error");
        exit(-1);
    }
}

void semaph_remove(const char *semaph_name)
{
    if (sem_unlink(semaph_name) == -1)
    {
        perror("semaph_remove error");
        exit(-1);
    }
}

int semaph_getvalue(sem_t *semaph_address)
{
    int val;
    int *value = &val;
    if (sem_getvalue(semaph_address, value) == -1)
    {
        perror("semaph_getvalue error");
        exit(-1);
    }
    return val;
}

void semaph_wait(sem_t *semaph_address)
{
    if (sem_wait(semaph_address) == -1)
    {
        perror("semaph_wait error");
        exit(-1);
    }
}

void semaph_run(sem_t *semaph_address)
{
    if (sem_post(semaph_address) == -1)
    {
        perror("semaph_run error");
        exit(-1);
    }
}