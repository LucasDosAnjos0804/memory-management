/*
    Uma abstração do que um CPU geralmente faz
*/

void* td_cpu();

void*
td_cpu()
{
    /*
        Quando um processo é executado na CPU, ele faz referência a endereços de memória virtual,
        que podem ser mapeados para endereços físicos correspondentes na memória RAM ou no disco.
        Quando a CPU precisa ler dados de um processo, ela primeiro consulta a tabela de páginas
        para descobrir o endereço físico correspondente ao endereço virtual do processo. Em seguida,
        ela acessa o endereço físico diretamente na memória RAM para ler os dados necessários. Se a
        página não estiver presente na memória RAM, o gerenciador de memória buscará a página no disco
        e a carregará na memória RAM antes que a CPU possa acessá-la.
    */
    No* no;
    Job* job;
    Pagetable* pagetable;
    Linha_Pagetable *linhapagetable;

    while( 1 )
    {
        pthread_mutex_lock( &mutex_priority );
        if ( priority->tam == 0 )
        {
            pthread_cond_wait ( &cond_priority, &mutex_priority );
        }
        job = priority_row_drop( priority );
        pthread_mutex_unlock( &mutex_priority );

        // ler a page table
        pagetable = job->pagetable;
        // ler cada linha da pagetable
        no = pagetable->start;
        while ( no != NULL )
        {
            linhapagetable = ( Linha_Pagetable * ) no->data;
            if ( linhapagetable->in_memory == 0 )
            {
                logs(l,"cpu emitindo page fault",'c');
                // emitindo page fault para memory manager
                pthread_mutex_lock( &mutex_page_fault_cpu_to_mm );
                fila_add( page_fault_cpu_to_mm, linhapagetable );
                if ( page_fault_cpu_to_mm->tam_atual <= 1)
                    pthread_cond_signal( &cond_page_fault_cpu_to_mm );
                pthread_mutex_unlock( &mutex_page_fault_cpu_to_mm );

                // a cpu tem que esperar mesmo até que o memory manager mova página para a memoria
                pthread_mutex_lock( &mutex_page_fault_mm_to_cpu );
                if ( page_fault_mm_to_cpu->tam_atual == 0)
                    pthread_cond_wait( &cond_page_fault_mm_to_cpu, &mutex_page_fault_mm_to_cpu );
                linhapagetable = ( Linha_Pagetable* ) fila_drop( page_fault_mm_to_cpu )->data;
                pthread_mutex_unlock( &mutex_page_fault_mm_to_cpu );

            }
            // ler as linhas do processo diretamente na memória
            for ( int i = 0; i < PAGE_SIZE; i++ )
            {
                memory_read( memory, linhapagetable->endereco_mfisica + i );
                // anythink
                usleep(250000);
            }
            no = no->prox;
        }

        // emitindo free memory para o memory manager
        pthread_mutex_lock( &mutex_free_memory_to_mm );
        fila_add( free_memory_to_mm, job );
        if ( free_memory_to_mm->tam_atual <= 1 )
        {
            pthread_cond_signal( &cond_free_memory_to_mm );
        }
        pthread_mutex_unlock( &mutex_free_memory_to_mm );
    }
}