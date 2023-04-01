/*
    Uma abstação do que um escalonador de processos geralmente faz
*/

void* td_scheduler();

void*
td_scheduler()
{
    No* no;
    Job* job;

    while( 1 )
    {   
        // tirar o job do job list to scheduler
        pthread_mutex_lock( &mutex_jobList_to_scheduler );
        if ( jobList_to_scheduler->tam_atual == 0 )
        {
            pthread_cond_wait( &cond_jobList_to_scheduler,&mutex_jobList_to_scheduler ); // ele sempre vai esperar
        }
        no = fila_drop( jobList_to_scheduler );
        pthread_mutex_unlock( &mutex_jobList_to_scheduler );

        job = no->data;
        
        // adicionar o job na estrutura do escalonamento por prioridade
        pthread_mutex_lock( &mutex_priority );
        priority_row_add( priority,job );
        if ( priority->tam <= 1 )
        {
            pthread_cond_signal( &cond_priority );
        }
        pthread_mutex_unlock( &mutex_priority );
    }
}