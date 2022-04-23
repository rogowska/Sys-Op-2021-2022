/*Oliwia Rogowska*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define bytesForBufP 10
#define bytesForBufC 3

int main()
{
    int filedes[2], id, nobytes, fsrc, fdst, random_value;
    unsigned char bufferP[bytesForBufP], bufferC[bytesForBufC];
    char str_bytes[2];

    /*creating a pipe and handling error*/
    if (pipe(filedes) == -1)
    {
        perror("pipe error\n");
        exit(EXIT_FAILURE);
    }

    id = fork();
    if (id > 0)
    {
        /*parent process opening source file to read*/
        fsrc = open("file_src.txt", O_RDONLY, 0666);
        close(filedes[0]);
        do
        {
            /*generating random value for sleep()*/
            random_value = rand() % 5;
            sleep(random_value);
            /*reading from source file*/
            nobytes = read(fsrc, bufferP, bytesForBufP);
            /*writing buffer to pipe*/
            if (write(filedes[1], bufferP, nobytes) == -1)
            {
                perror("write error\n");
                exit(EXIT_FAILURE);
            }
            /*writing buffer to stdout for validation*/
            if (write(STDOUT_FILENO, bufferP, nobytes) == -1)
            {
                perror("write error\n");
                exit(EXIT_FAILURE);
            }
            sprintf(str_bytes, "%d", nobytes);
            if (write(STDOUT_FILENO, str_bytes, sizeof(str_bytes)) == -1)
            {
                perror("write error\n");
                exit(EXIT_FAILURE);
            }

        } while (nobytes == bytesForBufP);
        close(fsrc);
    }
    else if (id == 0)
    {
        /*child process opening destination file to write*/
        fdst = open("file_dst.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
        close(filedes[1]);
        do
        {
            /*generating random value for sleep()*/
            random_value = rand() % 5;
            sleep(random_value);
            /*reading from pipe*/
            nobytes = read(filedes[0], bufferC, bytesForBufC);
            /*writing to destination file*/
            if (write(fdst, bufferC, nobytes) == -1)
            {
                perror("write error\n");
                exit(EXIT_FAILURE);
            }
            /*writing buffer to stdout for validation*/
            if (write(STDOUT_FILENO, bufferC, nobytes) == -1)
            {
                perror("write error\n");
                exit(EXIT_FAILURE);
            }
        } while (nobytes == bytesForBufC);
        close(fdst);
    }
    else
    {
        perror("fork error\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}