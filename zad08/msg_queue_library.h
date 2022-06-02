#include <fcntl.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

const char *serverQueue = "sQueue";

mqd_t msq_open_readonly(const char*);
mqd_t msq_open_writeonly(const char*);
mqd_t msq_create(const char*);
void msq_close(mqd_t);
void msq_unlink(const char*);
void msq_send(mqd_t, const char*, int);
void msq_recieve(mqd_t, char*);
void msq_getattr(mqd_t, struct mq_attr*);
void msq_setattr(mqd_t, struct mq_attr*, struct mq_attr*);