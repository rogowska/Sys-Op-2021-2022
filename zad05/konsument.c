/*Oliwia Rogowska*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    
    if (argc != 3)
    {
        printf("Wrong number of arguments (expected: source and destination file names)\n");
        exit(EXIT_FAILURE);
    }

    int fdst, mf, bytesread;
    char buffer[10];
    char *dstname = argv[1];
    char *myfifo = argv[2];

    fdst = open(dstname, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    mf = open(myfifo, O_RDONLY);
    do
    {
        bytesread = read(mf, buffer, 5);
        if (-1 == bytesread)
        {
            perror("read error\n");
            _exit(EXIT_FAILURE);
        }
        if (-1 == write(STDOUT_FILENO, buffer, bytesread))
        {
            perror("write error\n");
            _exit(EXIT_FAILURE);
        }
        if (-1 == write(fdst, buffer, bytesread))
        {
            perror("write error\n");
            _exit(EXIT_FAILURE);
        }
    } while (bytesread == 5);

    _exit(EXIT_SUCCESS);
}