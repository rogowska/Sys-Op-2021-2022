#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "library.h"

const char *my_semaph = "firstSemaph";

/*utworzenie funkcji obsługiwanej przez atexit*/
void atexfunc()
{
    semaph_remove(my_semaph);
}

int main(int argc, char *argv[])
{
    /*sprawdzanie liczby argumentów*/
    if (argc != 4)
    {
        printf("Wrong number of arguments (expected: program name, number of processes, number of critical sections)\n");
        exit(EXIT_FAILURE);
    }

    /*tworzenie zmiennych*/
    sem_t *my_semaph_address;
    unsigned int sem_init_value = 1;
    int i, id, fdesc;
    char buffer[12];

    /*przypisywanie argumentów do zmiennych*/
    char *program_name = argv[1];
    char *critsection_num = argv[3];
    char program_path[50];
    strncat(program_path, "./", 3);
    strncat(program_path, program_name, 20);
    int process_num = strtol(argv[2], NULL, 0);

    /*inicjalizacja semafora*/
    my_semaph_address = semaph_init(my_semaph, O_CREAT | O_EXCL, 0666, sem_init_value);
    printf("Semaphore address: %d\n", my_semaph_address);
    printf("Semaphore inital value: %d\n", sem_init_value);

    /*utworzenie pliku i zapisanie do niego 0*/
    fdesc = open("numer.txt", O_WRONLY | O_CREAT, 0666);
    if (fdesc == -1)
    {
        perror("File opening error\n");
        exit(EXIT_FAILURE);
    };
    if (write(fdesc, "0", 1) < 1)
    {
        perror("File write error\n");
        _exit(EXIT_FAILURE);
    }
    if (close(fdesc) == -1)
    {
        perror("File closing error\n");
        _exit(EXIT_FAILURE);
    }

    /*tworzenie procesów potomnych w pętli*/
    for (i = 0; i < process_num; i++)
    {
        id = fork();
        if (id > 0)
        {
            if (signal(SIGINT, atexfunc) == SIG_ERR)
            {
                perror("signal error");
                exit(EXIT_FAILURE);
            }
            sleep(1);
        }
        else if (id == 0)
        {
            execlp(program_path, program_name, critsection_num, my_semaph, NULL);
            perror("execlp error\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            perror("fork error\n");
            exit(EXIT_FAILURE);
        }
    }

    /* czekanie na procesy potomne */
    if (signal(SIGINT, atexfunc) == SIG_ERR)
    {
        perror("signal error");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < process_num; i++)
    {
        if (waitpid(-1, NULL, 0) == -1)
        {
            perror("wait error");
            exit(EXIT_FAILURE);
        }
    }

    /*czytanie wyniku z pliku*/
    fdesc = open("numer.txt", O_RDONLY, 0666);
    if (fdesc == -1)
    {
        perror("File opening error\n");
        exit(EXIT_FAILURE);
    };
    if (read(fdesc, buffer, 12) < 1)
    {
        perror("File read error\n");
        _exit(EXIT_FAILURE);
    }
    int check = strtol(buffer, NULL, 0);

    /*sprawdzanie zgodności wyniku z oczekiwanym rezultatem*/
    if (check == (atoi(critsection_num) * process_num))
    {
        printf("Number saved in numer.txt file is correct\n");
        printf("Number value: %d\n", check);
    }
    else
    {
        printf("Number saved in numer.txt file is incorrect\n");
        printf("Number value: %d\n", check);
    }
    /*zamknięcie pliku oraz semafora*/
    if (close(fdesc) == -1)
    {
        perror("File closing error\n");
        _exit(EXIT_FAILURE);
    }
    atexit(atexfunc);

    exit(EXIT_SUCCESS);
}