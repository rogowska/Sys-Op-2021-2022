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

    int fsrc, mf, bytesread;
    char buffer[10];
    char *fsrcname = argv[1];
    char *myfifo = argv[2];

    fsrc = open(fsrcname, O_RDONLY, 0666);
    mf = open(myfifo, O_WRONLY);
    do
    {
        bytesread = read(fsrc, buffer, 5);
        if (bytesread == -1)
        {
            perror("read error\n");
            _exit(EXIT_FAILURE);
        };

        write(STDOUT_FILENO, buffer, bytesread);
        if (-1 == write(mf, buffer, bytesread))
        {
            perror("write error\n");
            _exit(EXIT_FAILURE);
        }
    } while (bytesread == 5);

    close(fsrcname);
    _exit(EXIT_SUCCESS);
}
