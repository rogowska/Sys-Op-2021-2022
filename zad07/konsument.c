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
#define NELE 20
#define NBUF 10

typedef struct
{
    char bufor[NBUF][NELE];
    int insert;
    int get;
} SegmentSHM;

int main(int argc, char *argv[])
{

    /*sprawdzanie liczby argumentów*/
    if (argc != 5)
    {
        printf("Wrong number of arguments (expected: producent semaphore, konsument semaphore, memory and destination file names)\n");
        exit(EXIT_FAILURE);
    }

    /*tworzenie i przypisywanie zmiennych*/
    char *prod_semaph = argv[1];
    char *kons_semaph = argv[2];
    char *shm_name = argv[3];
    char *destfile = argv[4];
    int prodsemvalue, konssemvalue, fdst, bytesread, shmdesc;

    /*otwarcie pliku do zapisu*/
    fdst = open(destfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fdst == -1)
    {
        perror("Open error\n");
        exit(-1);
    }

    /*otwarcie semaforów i pamieci dzielonej, rzutowanie*/
    sem_t *prod_semaph_address = semaph_open(prod_semaph, 0);
    printf("Producent semaphore's address: %d\n", prod_semaph_address);
    sem_t *kons_semaph_address = semaph_open(kons_semaph, 0);
    printf("Konsument semaphore's address: %d\n", kons_semaph_address);
    shmdesc = my_shm_open(shm_name);

    SegmentSHM *SHM = (SegmentSHM *)my_mmap(sizeof(SegmentSHM), shmdesc);

    printf("Konsument: Shared memory size:%d\n", sizeof(SegmentSHM));
    printf("Shared memory address:%d\n", shmdesc);

    SHM->get = 0;

    /*zapisywanie wyprodukowanych produktów z pamieci dzielonej do pliku*/
    do
    {
        /*opuszczenie semafora konsumenta*/
        semaph_run(kons_semaph_address);

        /*wypisywanie wartosci semaforow*/
        prodsemvalue = semaph_getvalue(prod_semaph_address);
        konssemvalue = semaph_getvalue(kons_semaph_address);
        printf("\nProducent semaphore value: %d\n", prodsemvalue);
        printf("\nKonsument semaphore value: %d\n", konssemvalue);

        /*czytanie z pliku do pamięci dzielonej*/
        bytesread = write(fdst, SHM->bufor[SHM->get], NELE);
        if (bytesread == -1)
        {
            perror("read error\n");
            _exit(EXIT_FAILURE);
        };

        /*wypisanie towaru na ekran*/
        printf("Current bufor element index in konsument process: %d\n", SHM->get);
        printf("Bytes read: %d\n", bytesread);
        printf("Text recieved:\n\n");
        if (-1 == write(STDOUT_FILENO, SHM->bufor[SHM->get], bytesread))
        {
            perror("write error\n");
            _exit(EXIT_FAILURE);
        }

        /*zwiększenie indeksu*/
        SHM->get = (SHM->get + 1) % NBUF;

        /*podniesienie semafora producenta*/
        semaph_wait(prod_semaph_address);

    } while (bytesread == NELE);

    /* zamykanie pliku, semaforów i pamięci dzielonej */
    if (close(fdst) == -1)
    {
        perror("Close error\n");
        _exit(EXIT_FAILURE);
    }
    semaph_close(prod_semaph_address);
    semaph_close(kons_semaph_address);
    my_close(shmdesc);

    printf("Konsument: End - exiting\n");

    _exit(EXIT_SUCCESS);
}