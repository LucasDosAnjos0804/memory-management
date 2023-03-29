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

/*
    melhoria 

        um usario que cria demanda para cpu

        um escalonador que escalona os processos para o consudo da cpu

        a cpu consome um processo

        um swapper tabalha na MEMORIA (com o algoritmo especifico) movendo paginas para o DISCO (swap)
        a memoria tem um espaco de memoria no qual os processos e as paginas podem ser armazenadas
        o disco tambem tem um espaco no qual os processos e paginas podem ser movidos para ele.

*/ 