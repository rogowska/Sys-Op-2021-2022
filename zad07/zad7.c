/*Oliwia Rogowska*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <wait.h>
#include "semaph_library.h"
#include "shared_memory_library.h"

const char *prod_semaph = "prodSemaph";
const char *kons_semaph = "konsSemaph";
const char *my_shm = "memory";

/*utworzenie funkcji obsługiwanych przez atexit*/
void sphremove()
{
    semaph_remove(prod_semaph);
    semaph_remove(kons_semaph);
}

void shmremove()
{
    my_shm_unlink(*my_shm);
}

int main(int argc, char *argv[])
{

    /*sprawdzanie liczby argumentów*/
    if (argc != 3)
    {
        printf("Wrong number of arguments (expected: source and destination files' names)\n");
        exit(EXIT_FAILURE);
    }

    /*tworzenie zmiennych*/
    sem_t *prod_semaph_address, *kons_semaph_address;
    int shm_desc, id, id2;
    char *sfname = argv[1];
    char *dfname = argv[2];
    unsigned int sem_init_value = 1;

    /*inicjalizacja semaforów*/
    prod_semaph_address = semaph_init(prod_semaph, O_CREAT | O_EXCL, 0666, sem_init_value);
    printf("Producent semaphore's address: %d\n", prod_semaph_address);
    printf("Producent semaphore's inital value: %d\n", sem_init_value);

    kons_semaph_address = semaph_init(kons_semaph, O_CREAT | O_EXCL, 0666, sem_init_value);
    printf("Konsument semaphore's address: %d\n", kons_semaph_address);
    printf("Konsument semaphore's inital value: %d\n", sem_init_value);

    atexit(sphremove);
    atexit(shmremove);

    /*inicjalizacja pamięci dzielonej*/
    shm_desc = my_shm_create(my_shm);
    printf("Shared memory address:%d\n", shm_desc);

    id = fork();

    if (id > 0)
    {
        id2 = fork();
        if (id2 > 0)
        {
            wait(NULL);
        }
        else if (id2 == 0)
        {
            execlp("./konsument.x", "konsument.x", prod_semaph, kons_semaph, my_shm, dfname, NULL);
            perror("execlp error\n");
        }
        else
        {
            perror("fork error\n");
            exit(EXIT_FAILURE);
        }
        wait(NULL);
    }
    else if (id == 0)
    {
        execlp("./producent.x", "producent.x", prod_semaph, kons_semaph, my_shm, sfname, NULL);
        perror("execlp error\n");
    }
    else
    {
        perror("fork error\n");
        exit(EXIT_FAILURE);
    }

    atexit(sphremove);
    atexit(shmremove);

    exit(EXIT_SUCCESS);
}
