/*
    Uma abstração do que um Gerenciador de memória faz
*/

void* td_memory_manager();
void* td_free_memory_task();
void* td_page_fault_task_cpu_to_mm();
void* td_page_fault_task_swapper_to_mm();

void*
td_page_fault_task_swapper_to_mm()
{
    Linha_Pagetable *linha_page_table;;
    while ( 1 )
    {
        // receber chamada do swapper
        pthread_mutex_lock( &mutex_page_fault_swapper_to_mm );
        if ( page_fault_swapper_to_mm->tam_atual == 0 )
            pthread_cond_wait( &cond_page_fault_swapper_to_mm, &mutex_page_fault_swapper_to_mm );
        linha_page_table = ( Linha_Pagetable *) fila_drop ( page_fault_swapper_to_mm );
        pthread_mutex_unlock( &mutex_page_fault_swapper_to_mm );

        // comunicar-se com cpu
        pthread_mutex_lock( &mutex_page_fault_mm_to_cpu );
        fila_add( page_fault_mm_to_cpu, linha_page_table );
        if ( page_fault_mm_to_cpu->tam_atual <= 1)
            pthread_cond_signal( &cond_page_fault_mm_to_cpu );
        pthread_mutex_unlock( &mutex_page_fault_mm_to_cpu );
    }
}

void*
td_page_fault_task_cpu_to_mm()
{
    Linha_Pagetable *linha_page_table;;
    while ( 1 )
    {
        // receber chamada page fault da cpu
        pthread_mutex_lock( &mutex_page_fault_cpu_to_mm );
        if ( page_fault_cpu_to_mm->tam_atual == 0 )
            pthread_cond_wait( &cond_page_fault_cpu_to_mm, &mutex_page_fault_cpu_to_mm );
        linha_page_table = ( Linha_Pagetable* ) fila_drop( page_fault_cpu_to_mm );
        pthread_mutex_unlock( &mutex_page_fault_cpu_to_mm );

        // comunicar-se com swapper
        pthread_mutex_lock( &mutex_page_fault_mm_to_swapper );
        fila_add( page_fault_mm_to_swapper , linha_page_table );
        if ( page_fault_mm_to_swapper->tam_atual <= 1)
            pthread_cond_signal( &cond_page_fault_mm_to_swapper);
        pthread_mutex_unlock( &mutex_page_fault_mm_to_swapper );
    }
    
}

void*
td_free_memory_task()
{
    Job *job; 
    No *no;
    Pagetable *pagetable;
    Linha_Pagetable *linha_pagetable;

    while( 1 )
    {
        pthread_mutex_lock( &mutex_free_memory_to_mm );
        if ( free_memory_to_mm->tam_atual == 0 )
            pthread_cond_wait( &cond_free_memory_to_mm, &mutex_free_memory_to_mm );
        no = fila_drop( free_memory_to_mm );
        pthread_mutex_unlock( &mutex_free_memory_to_mm );
        
        logs(l,"memory manager liberando memoria",'m');

        job = no->data;
        // desalocar
        pagetable = job->pagetable;
        while ( pagetable->tam_atual > 0 )
        {
            linha_pagetable = pagetable_drop( pagetable );
            // retirar a pagina de vmemory
            pthread_mutex_lock( &mutex_vmemory );
            vm_drop( vmemory );
            pthread_mutex_unlock( &mutex_vmemory );

            // escrever zeros na memoria
            if ( linha_pagetable->in_memory )
            {
                for ( int i = 0; i < PAGE_SIZE; i++ )
                {
                    pthread_mutex_lock( &mutex_memory );
                    memory_write( memory, linha_pagetable->endereco_mfisica + i , 0);
                    pthread_mutex_unlock( &mutex_memory );
                }
            }

            // liberar memoria no bitmap
            pthread_mutex_lock( &mutex_bitmap );
            bitmap_free( bitmap, linha_pagetable->endereco_mvirtual );
            pthread_cond_signal( &cond_bitmap );
            pthread_mutex_unlock( &mutex_bitmap );

            //linha_pagetable = pagetable_drop( pagetable );

        }
    }
}

void*
td_memory_manager()
{
    /*
        O gerenciador de memória é responsável por alocar e desalocar páginas na memória virtual,
        mapear essas páginas para a memória física ou para o armazenamento secundário e gerenciar
        a tabela de páginas. 
    */
    pthread_t thread_id_free_memory_task;
    if ( ( pthread_create( &thread_id_free_memory_task, NULL,  td_free_memory_task, NULL ) ) != 0 )
        err("Nao foi possivel criar a thread free_memory_task");

    pthread_t thread_id_page_fault_task_cpu_to_mm;
    if ( ( pthread_create( &thread_id_page_fault_task_cpu_to_mm, NULL,  td_page_fault_task_cpu_to_mm, NULL ) ) != 0 )
        err("Nao foi possivel criar a thread page_fault_task");

    pthread_t thread_id_page_fault_task_swapper_to_mm;
    if ( ( pthread_create( &thread_id_page_fault_task_swapper_to_mm, NULL,  td_page_fault_task_swapper_to_mm, NULL ) ) != 0 )
        err("Nao foi possivel criar a thread page_fault_task");

    
    while( 1 )
    {
        Pagetable* pagetable = pagetable_create();  // para cada processo alocado na vmemory

        int endereco_virtual;
        int qtd_paginas_virtuais;

        No* no;
        Job* job = NULL;
        Pagina* p;
        
        pthread_mutex_lock( &mutex_jobList_to_mm );   // lock job list
        if ( jobList_to_mm->tam_atual == 0 )
            pthread_cond_wait( &cond_jobList_to_mm, &mutex_jobList_to_mm );
        
        no = fila_drop( jobList_to_mm );
        pthread_mutex_unlock( &mutex_jobList_to_mm ); // unlock job list

        job = no->data;
        
        qtd_paginas_virtuais = ( job->tam / PAGE_SIZE )+1; 

        for( int i = 0; i < qtd_paginas_virtuais; i++ )
        {
            // mapeamento de endereço virtual para endereco fisico
            pthread_mutex_lock( &mutex_bitmap );
            endereco_virtual = bitmap_find( bitmap ); // percorrer o bitmap para encontrar um edereco de memoria virtual livre
            if ( endereco_virtual == -1 )
            {
                err("não foi possível alocar um endereço virtual out of vmemory");
                pthread_cond_wait( &cond_bitmap, &mutex_bitmap );
                endereco_virtual = bitmap_find( bitmap );
            }
            pthread_mutex_unlock( &mutex_bitmap );
            
            pagetable_map( pagetable,endereco_virtual,job->endereco+i );     // mapeia o endereco virtual pra o endereco fisico do processo 
            
            bitmap_print( bitmap );
        }
        
        //pthread_mutex_lock( &job->mutex );
        job->pagetable = pagetable;
        //pthread_mutex_unlock( &job->mutex );

        // emitindo um joblist to scheduler
        pthread_mutex_lock( &mutex_jobList_to_scheduler );
        fila_add( jobList_to_scheduler,job );
        if ( jobList_to_scheduler->tam_atual <= 1 )
            pthread_cond_signal( &cond_jobList_to_scheduler );
        pthread_mutex_unlock( &mutex_jobList_to_scheduler );
    }

    pthread_join( thread_id_free_memory_task, NULL );
    pthread_join( thread_id_page_fault_task_cpu_to_mm, NULL );
    pthread_join( thread_id_page_fault_task_swapper_to_mm, NULL );
}