#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "library.h"

void criticalsection(sem_t *my_semaph_address)
{

    printf("\n    Process %d is executing critical operation\n", getpid());

    /*tworzenie zmiennych*/
    int fdesc, value;
    char buffer[12];
    char buffer2[12];

    /*otwarcie pliku do czytania*/
    fdesc = open("numer.txt", O_RDONLY, 0666);
    if (fdesc == -1)
    {
        perror("File opening error\n");
        _exit(EXIT_FAILURE);
    };
    if (read(fdesc, buffer, 12) < 1)
    {
        perror("File read error\n");
        _exit(EXIT_FAILURE);
    }
    printf("Number read from file: %s\n\n", buffer);
    if (close(fdesc) == -1)
    {
        perror("File closing error\n");
        _exit(EXIT_FAILURE);
    }

    /*konwersja danych z char do int, podniesienie wartości*/
    int number = strtol(buffer, NULL, 0);
    number++;

    /*konwersja danych z int do char*/
    if (sprintf(buffer2, "%d", number) < 0)
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
    if (write(fdesc, buffer2, 12) < 1)
    {
        perror("File writing error\n");
        _exit(EXIT_FAILURE);
    }

    /*odczytanie wartości semafora i zamknięcie pliku*/
    value = semaph_getvalue(my_semaph_address);
    printf("Value of semaphore in critial section: %d\n", value);
    if (close(fdesc) == -1)
    {
        perror("File closing error\n");
        _exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    /*sprawdzanie liczby argumentów*/
    if (argc != 3)
    {
        printf("Wrong number of arguments (expected: number of critical sections)\n");
        _exit(EXIT_FAILURE);
    }

    /*otwarcie semafora, tworzenie zmiennych*/
    char *my_semaph = argv[2];
    sem_t *my_semaph_address = semaph_open(my_semaph, 0);
    int i, value;
    int critsec_num = strtol(argv[1], NULL, 0);

    for (i = 0; i < critsec_num; i++)
    {
        printf("Process %d is looping for the %dth time\n", getpid(), i + 1);

        /*odczytywanie wartości semafora i pid procesu*/
        value = semaph_getvalue(my_semaph_address);
        printf("Value of semaphore before critial section: %d\n", value);

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