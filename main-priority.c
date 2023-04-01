#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>


#include "utils.h"
#include "job.h"
#include "round-robin.h"
#include "priority.h"

#define QUANTUM 2

void *
thr_one (int tmp)
{

    // pthread_mutex_lock (&j->lock);
    // pthread_cond_wait (&j->cond,&j->lock);
    // pthread_mutex_unlock (&j->lock);

    // do anything
    printf("PROC-Prioridade\n");
}

int main()
{
    srand(time(NULL));

    Priority_row *pr = (Priority_row*) malloc (sizeof(Priority_row));
    
    Round *p1 = (Round*) malloc (sizeof(Round));
    pr->p1 = p1;

    Round *p2 = (Round*) malloc (sizeof(Round));
    pr->p2 = p2;

    Round *p3 = (Round*) malloc (sizeof(Round));
    pr->p3 = p3;
    
    Round *p4 = (Round*) malloc (sizeof(Round));
    pr->p4 = p4;

    if (!pr)
    {
        err("can't malloc Priority_row");
        return 1;
    }


    add_JobToPriorityRow( create_job(thr_one,4),pr );
    add_JobToPriorityRow( create_job(thr_one,4),pr );
    add_JobToPriorityRow( create_job(thr_one,4),pr );

    add_JobToPriorityRow( create_job(thr_one,3),pr );
    add_JobToPriorityRow( create_job(thr_one,3),pr );

    add_JobToPriorityRow( create_job(thr_one,2),pr );
    add_JobToPriorityRow( create_job(thr_one,2),pr );
    add_JobToPriorityRow( create_job(thr_one,2),pr );

    add_JobToPriorityRow( create_job(thr_one,1),pr );


    
    Job *j;
    while ( (j = drop_PriorityJob(pr)) != NULL )
    {
        // executar o job
        /* 
            Simula a execucao de um processo
        */

        if (pthread_create( (pthread_t *) &j->pt, NULL,j->fn, NULL) != 0)
            err("can't create thread!");
                    
        sleep(1);

        // diminuir QUANTUN do tempo de execucao
        j->tmp = j->tmp - QUANTUM;

        
        if ( j->tmp > 0 )
        {
            // manda a thread pausar

            // pthread_mutex_lock (&j->lock);
            // pthread_cond_signal (&j->cond);
            // pthread_mutex_unlock (&j->lock);

            j->priority--;

            add_JobToPriorityRow(j,pr);  //adiciona o Job ao final da fila de prioridade
        } else {
            // da join
            if ( (pthread_join( (pthread_t) j->pt, j->tret) ) != 0)
                err("thread join Error");
            else
                logs(" - thread terminated join success!");
        }
    }

    printf("FIM\n");

    free(pr);

    return 0;
}