#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "library.h"

void criticalsection(sem_t *my_semaph_address)
{
    /*tworzenie zmiennych*/
    int fdesc, value;
    char buffer[3];

    /*otwarcie pliku do czytania*/
    fdesc = open("numer.txt", O_RDONLY, 0666);
    if (fdesc == -1)
    {
        perror("File opening error\n");
        _exit(EXIT_FAILURE);
    };
    read(fdesc, buffer, 3);
    printf("Number read from file: %s\n", buffer);
    close(fdesc);

    /*konwersja danych z char do int, podniesienie wartości*/
    int number = strtol(buffer, NULL, 0);
    number++;

    /*konwersja danych z int do char*/
    if (sprintf(buffer, "%d", number) < 0)
    {
        perror("sprintf error");
        _exit(EXIT_FAILURE);
    }
    sleep(rand() % 5);

    /*otwarcie pliku do zapisu*/
    fdesc = open("numer.txt", O_WRONLY, 0666);
    if (fdesc == -1)
    {
        perror("File opening error\n");
        _exit(EXIT_FAILURE);
    };
    write(fdesc, buffer, 3);
    
    /*odczytanie wartości semafora i zamknięcie pliku*/
    value = semaph_getvalue(my_semaph_address);
    printf("Value of semaphore in critial section: %d\n", value);
    close(fdesc);
}

int main(int argc, char *argv[])
{
    /*sprawdzanie liczby argumentów*/
    if (argc != 2)
    {
        printf("Wrong number of arguments (expected: number of critical sections)\n");
        _exit(EXIT_FAILURE);
    }

    /*otwarcie semafora, tworzenie zmiennych*/
    sem_t *my_semaph_address = semaph_open("my_semaph", 0);
    int i, value;
    int critsec_num = strtol(argv[1], NULL, 0);


    for (i = 0; i < critsec_num; i++)
    {
        printf("Loop number: %d\n", i + 1);

        /*odczytywanie wartości semafora i pid procesu*/
        value = semaph_getvalue(my_semaph_address);
        printf("Value of semaphore before critial section: %d\n", value);
        printf("Process pid: %d\n", getpid());

        /*symulowanie działania w częsci wspólnej*/
        sleep(rand() % 5);
        semaph_wait(my_semaph_address);

        /*przejście do części krytycznej*/
        criticalsection(my_semaph_address);
        semaph_run(my_semaph_address);

        /*odczytanie wartości semafora*/
        value = semaph_getvalue(my_semaph_address);
        printf("Value of semaphore after critial section: %d\n", value);
    }
    _exit(EXIT_SUCCESS);
}