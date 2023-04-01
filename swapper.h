/*
    uma abtração do que um swapper geralmente faz
*/

void* td_swapper ();

void*
td_swapper ()
{
    /*
        O Swapper é um componente do sistema operacional que gerencia a troca
        de páginas entre a memória física (RAM) e o armazenamento secundário 
        (disco rígido) quando a quantidade de memória disponível na RAM é 
        insuficiente para as necessidades do sistema.
    */
    Linha_Pagetable* linha_page_table;
    Pagina *p;
    while( 1 )
    {
        // receber page fault
        pthread_mutex_lock( &mutex_page_fault_mm_to_swapper );
        if ( page_fault_mm_to_swapper->tam_atual == 0 )
            pthread_cond_wait( &cond_page_fault_mm_to_swapper, &mutex_page_fault_mm_to_swapper );
        linha_page_table = ( Linha_Pagetable* ) fila_drop( page_fault_mm_to_swapper )->data;
        pthread_mutex_unlock( &mutex_page_fault_mm_to_swapper );

        logs(l,"swapper movendo pagina para memmoria",'c');

        p = pagina_create( linha_page_table->endereco_mvirtual, linha_page_table->endereco_mfisica );    // cria uma pagina com o endereco de virtual encontrado
        pthread_mutex_lock( &mutex_vmemory );     // lock vmemory
        vm_addin( vmemory,p );                    // adiciona pagina criada à memória virtual
        pthread_mutex_unlock( &mutex_vmemory );   // unlock vmemory
    
        // mover dados do armazenamento secundário para o primário
        for (int i = 0; i < PAGE_SIZE; i++)
        {
            pthread_mutex_lock( &mutex_memory );
            // ta errado
            // ele deve primeiro descobrir qual endereço de memoria fisica está livre
            memory_write( memory,linha_page_table->endereco_mfisica+i, 1);
            pthread_mutex_unlock( &mutex_memory );
        }

        linha_page_table->in_memory = 1;
        // emitir page fault swapper to mm 
        pthread_mutex_lock( &mutex_page_fault_swapper_to_mm );
        fila_add( page_fault_swapper_to_mm, linha_page_table );
        if ( page_fault_swapper_to_mm->tam_atual <= 1 )
            pthread_cond_signal( &cond_page_fault_swapper_to_mm );
        pthread_mutex_unlock( &mutex_page_fault_swapper_to_mm );
    }
}