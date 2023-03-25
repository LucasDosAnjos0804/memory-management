#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#include "utils.h"
#include "fifo.h"


int
main ()
{
    srand(time(NULL));
    
    Fifo* f = create_fifo(10);
    
    while (1)
    {
        system("clear");

        puts("FIFO ALGORITHM\n");

        addin_fifo( f, create_pagina( rand()%sizeof(int), rand()%sizeof(int) ) );
        puts("");
        print_fifo( f);

        sleep(1);
    }

    return 0;
}