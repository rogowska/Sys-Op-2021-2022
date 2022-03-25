/*Oliwia Rogowska*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main(argc, argv[])
{

    int id, childpid;
    int signumber = strtol(argv[1], NULL, 0);

    id = fork();

    if (id > 0)
    {
        sleep(2);
        kill(childpid, signumber);
    }
    if (id == 0)
    {
        execlp("./zad3_a.x", "zad3_a.x", NULL);
        perror("execlp error");
        childpid = getpid();
    }
    else
    {
        perror("fork error\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}