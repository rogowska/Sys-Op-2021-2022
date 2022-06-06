#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/*deklaracja zmiennych globalnych*/
#define max_thread_number 10
int global_counter = 0;
int repetition_number, threads_number;
pthread_mutex_t myMutex;
pthread_t thread_array[max_thread_number];

/*funkcja do ustawiania kursora na odpowiednim miejscu w terminalu*/
void set_cursor(unsigned x, unsigned y)
{
    printf("\033[%d;%dH\033[2K", y, x);
}

/*funkcja uruchamiana w wątkach*/
void *thread_function(void *thread_number_void)
{
    int j;
    int thread_number = *((int *)thread_number_void);
    printf("Thread number: %d, ID: %ld \n", thread_number + 1, thread_array[thread_number]);

    /*przejście przez pętlę zależne od ilości cykli*/
    for (j = 0; j < repetition_number; j++)
    {
        /*--------sekcja prywatna-------*/
        sleep(rand() % 5);
        set_cursor(0, 4 + threads_number + thread_number);
        printf("\033[32mThread number: %d, loop number: %d, number: %d \033[0m\n", thread_number + 1, j + 1, global_counter);

        /*--------sekcja krytyczna-------*/
        /*zamknięcie mutexu*/
        if (pthread_mutex_lock(&myMutex) != 0)
        {
            printf("pthread_mutex_lock error, exiting...\n");
            exit(1);
        }

        /*wyświetlenie danych*/
        set_cursor(25, 4 + threads_number + thread_number);
        printf("\033[32mThread number: %d, loop number: %d, number: %d \033[0m\n", thread_number + 1, j + 1, global_counter);

        /*podbicie licznika*/
        int counter;
        counter = global_counter;
        counter++;
        sleep(rand() % 5);
        global_counter = counter;

        /*otwarcie mutexu*/
        if (pthread_mutex_unlock(&myMutex) != 0)
        {
            printf("pthread_mutex_unlock error, exiting...\n");
            exit(1);
        }
        /*--------koniec sekcji krytycznej--------*/
        set_cursor(0, 4 + threads_number + thread_number);
        printf("\033[32mThread number: %d, loop number: %d, number: %d \033[0m\n", thread_number + 1, j + 1, global_counter);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    /*sprawdzanie liczby argumentów*/
    if (argc != 3)
    {
        printf("Wrong number of arguments, expected: threads number and number of repetitions\n");
        printf("Exiting...");
        exit(1);
    }

    /*deklaracja zmiennych*/
    int i;

    /*próba konwersji argumentów do int, walidacja*/
    threads_number = strtol(argv[1], NULL, 10);
    repetition_number = strtol(argv[2], NULL, 10);

    if ((threads_number == 0) || (repetition_number == 0))
    {
        printf("Wrong type of arguments, expected: int\n");
        printf("Exiting...");
        exit(1);
    }

    if (threads_number > max_thread_number)
    {
        printf("Exceeded maximum number of threads\n");
        printf("Exiting...\n");
        exit(1);
    }

    /*tworzenie mutexu zainicjowanego na 0*/
    if (pthread_mutex_init(&myMutex, NULL) != 0)
    {
        printf("pthread_mutex_init error, exiting...\n");
        exit(1);
    }

    /*wyświetlanie adresu mutexu*/
    printf("Created mutex's address: %p\n", &myMutex);

    /*tworzenie wątków*/
    for (i = 0; i < threads_number; i++)
    {
        /*rzutowanie int na void i przekazywanie wskaźnika do wątku*/
        int *memory = malloc(sizeof(int));
        *memory = i;
        if (pthread_create(&thread_array[i], NULL, thread_function, (void *)memory) != 0)
        {
            printf("pthread_create error\n");
            printf("Exiting...\n");
        };
        /*wyświetlanie numeru i adresu stworzonego wątku*/
        printf("Created a thread number %d, it's address: %p\n", i + 1, &thread_array[i]);
    }

    /*czekanie na zakończenie wątków*/
    for (i = 0; i < threads_number; i++)
    {
        if (pthread_join(thread_array[i], NULL) != 0)
        {
            printf("Pthread_join error, exiting...\n");
            exit(1);
        }
    }

    /*weryfikacja wyniku*/
    if (global_counter == repetition_number * threads_number)
    {
        printf("Synchronisation suceeded, global counter value: %d\n", global_counter);
    }
    else
    {
        printf("Synchronisation unsuceeded, global counter value: %d, expected: %d\n", global_counter, (repetition_number * threads_number));
    }

    /*zamknięcie mutexu, wyjście*/
    if (pthread_mutex_destroy(&myMutex) != 0)
    {
        printf("pthread_mutex_destroy error, exiting...\n");
        exit(1);
    }
    exit(0);
}