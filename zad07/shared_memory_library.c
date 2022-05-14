#include "shared_memory_library.h"

void shm_map(void *addr, size_t length, int prot, int flags,
             int fd, off_t offset)
{
    if ((void *)-1 = *mmap(addr, length, prot, flags, fd, offset))
    {
        perror("shm_map error");
        exit(-1);
    }
}

void rm_map(void *addr, size_t length)
{
    if (munmap(addr, length) == -1)
    {
        perror("rm_map error");
        exit(-1);
    }
}

void mem_close(int fd)
{
    if (close(fd) == -1)
    {
        perror("mem_close error");
        exit(-1);
    }
}

void mem_unlik(const char *name){
    if(shm_unlink(name)==-1){
        perror("mem_unlink error");
        exit(-1);
    }
}


    open frnicate czy cos i poprawic te funkcje w main
        i dodac deklaracje w h,
