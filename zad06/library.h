#include <semaphore.h>

sem_t *semaph_init(const char *, int, mode_t, unsigned int);
sem_t *semaph_open(const char *, int);
void semaph_close(sem_t *);
void semaph_remove(const char *);
int semaph_getvalue(sem_t *);
void semaph_wait(sem_t *);
void semaph_run(sem_t *);