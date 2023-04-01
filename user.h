/*
    Uma abstração do que um usuário geralmente faz
*/
void* td_user();

void*
td_user()
{   
    while( 1 )
    {   
        pthread_mutex_lock( &mutex_jobList_to_mm );
        fila_add( jobList_to_mm,(Job*) create_job( 2,2,2 ) );
        if ( jobList_to_mm->tam_atual <= 1 )
            pthread_cond_signal( &cond_jobList_to_mm );
        pthread_mutex_unlock( &mutex_jobList_to_mm );

        logs(l,"user added job to jobList_to_mm",'u');
        sleep( 1 );
    }
}