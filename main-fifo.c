#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

#include "utils.h"

#include "memory.h"
#include "paginas.h"
#include "fifo.h"
#include "virtual-memory.h"
#include "bitmap.h"
#include "page-table.h"

#include "job.h"
#include "round-robin.h"
#include "priority.h"


Fila *jobList_to_mm;
Fila *jobList_to_scheduler;
Fila *page_fault_cpu_to_mm;
Fila *page_fault_mm_to_cpu;
Fila *page_fault_mm_to_swapper;
Fila *page_fault_swapper_to_mm;
Fila *free_memory_to_mm;

Bitmap *bitmap;
Vmemory *vmemory;
Priority_row *priority;
Memory *memory;


pthread_mutex_t mutex_jobList_to_mm;
pthread_mutex_t mutex_jobList_to_scheduler;
pthread_mutex_t mutex_bitmap;
pthread_mutex_t mutex_vmemory;
pthread_mutex_t mutex_priority;
pthread_mutex_t mutex_memory; 
pthread_mutex_t mutex_page_fault_cpu_to_mm;
pthread_mutex_t mutex_page_fault_mm_to_cpu;
pthread_mutex_t mutex_page_fault_swapper_to_mm;
pthread_mutex_t mutex_page_fault_mm_to_swapper;
pthread_mutex_t mutex_free_memory_to_mm;

pthread_cond_t cond_jobList_to_mm;
pthread_cond_t cond_jobList_to_scheduler;
pthread_cond_t cond_priority;
pthread_cond_t cond_memory;
pthread_cond_t cond_bitmap;
pthread_cond_t cond_page_fault_cpu_to_mm;
pthread_cond_t cond_page_fault_mm_to_cpu;
pthread_cond_t cond_page_fault_mm_to_swapper;
pthread_cond_t cond_page_fault_swapper_to_mm;
pthread_cond_t cond_free_memory_to_mm;

#include "user.h"
#include "memory-manager.h"
#include "scheduler.h"
#include "cpu.h"
#include "swapper.h"

int
main ()
{
    srand(time(NULL));

    pthread_t thread_id_user;
    pthread_t thread_id_memory_manager;
    pthread_t thread_id_scheduler;
    pthread_t thread_id_cpu;
    pthread_t thread_id_swapper;


    //                              initializando estruturas

    //      logs
    l = fila_create();
    //      jobList_to_mm
    jobList_to_mm = fila_create();
    //      jobList_to_scheduler
    jobList_to_scheduler = fila_create();
    //      vmemory
    vmemory = vm_create();
    //      priority
    priority = priority_row_create();
    //      memory
    memory = memory_create();
    //      page_fault_cpu_to_mm
    page_fault_cpu_to_mm = fila_create();
    //      page_fault_mm_to_cpu
    page_fault_mm_to_cpu = fila_create();
    //      page_fault_mm_to_swapper
    page_fault_mm_to_swapper = fila_create();
    //      page_fault_swapper_to_mm
    page_fault_swapper_to_mm = fila_create();
    //      free_memory_to_mm
    free_memory_to_mm = fila_create();
    //      bitmap
    bitmap = bitmap_create();


    //                              Capturas de erros de estruturas

    //      logs
    if ( l == NULL )
        err("Nao foi possivel allocar memoria para logs");
    //      jobList_to_mm
    if ( jobList_to_mm == NULL ) 
        err("Nao foi possivel allocar memoria para jobList_to_mm");
    //      jobList_to_scheduler
    if ( jobList_to_scheduler == NULL )
        err("Nao foi possivel allocar memoria para jobList_to_scheduler");
    //      vmemory
    if ( vmemory == NULL )
        err("Nao foi possivel allocar memoria para vmemory");
    //      bitmap
    if ( bitmap == NULL )
        err("Nao foi possivel allocar memoria para bitmap");
    //      priority
    if ( priority == NULL )
        err("Nao foi possivel allocar memoria para priority");  
    //      memória
    if ( memory == NULL )
        err("Nao foi possivel allocar memoria para memory :) haha");
    //      page_fault_cpu_to_mm
    if ( page_fault_cpu_to_mm == NULL )
        err("Nao foi possivel allocar memoria para page_fault_cpu_to_mm");
    //      page_fault_mm_to_cpu
    if ( page_fault_mm_to_cpu == NULL )
        err("Nao foi possivel allocar memoria para page_fault_mm_to_cpu");
    //      free_memory_to_mm
    if ( free_memory_to_mm == NULL )
        err("Nao foi possivel allocar memoria para free_memory_to_mm");
    //      page_fault_mm_to_swapper
    if ( page_fault_mm_to_swapper == NULL )
        err("Nao foi possivel allocar memoria para page_fault_mm_to_swapper");
    //      page_fault_swapper_to_mm
    if ( page_fault_swapper_to_mm == NULL )
        err("Nao foi possivel allocar memoria para page_fault_swapper_to_mm");



    //                              inicializando mutexes

    //      jobList_to_mm
    pthread_mutex_init( &mutex_jobList_to_mm, NULL );
    //      jobList_to_scheduler
    pthread_mutex_init( &mutex_jobList_to_scheduler, NULL );
    //      vmemory
    pthread_mutex_init( &mutex_vmemory, NULL );
    //      bitmap
    pthread_mutex_init( &mutex_bitmap, NULL );
    //      priority
    pthread_mutex_init( &mutex_priority, NULL );
    //      memory
    pthread_mutex_init( &mutex_memory, NULL );
    //      page_fault_cpu_to_mm
    pthread_mutex_init( &mutex_page_fault_cpu_to_mm, NULL );
    //      page_fault_mm_to_cpu
    pthread_mutex_init( &mutex_page_fault_mm_to_cpu, NULL );
    //      page_fault_mm_to_swapper
    pthread_mutex_init( &mutex_page_fault_mm_to_swapper, NULL );
    //      page_fault_swapper_to_mm
    pthread_mutex_init( &mutex_page_fault_swapper_to_mm, NULL );
    //      free_memory_to_mm
    pthread_mutex_init( &mutex_free_memory_to_mm, NULL );


    //                              Inicializando condições

    //      jobList_to_mm
    pthread_cond_init( &cond_jobList_to_mm, NULL );
    //      jobList_to_scheduler
    pthread_cond_init( &cond_jobList_to_scheduler, NULL );
    //      priority
    pthread_cond_init( &cond_priority, NULL );
    //      memory
    pthread_cond_init( &cond_memory, NULL );
    //      page_fault_cpu_to_mm
    pthread_cond_init( &cond_page_fault_cpu_to_mm, NULL );
    //      page_fault_mm_to_cpu
    pthread_cond_init( &cond_page_fault_mm_to_cpu, NULL );
    //      page_fault_mm_to_swapper
    pthread_cond_init( &cond_page_fault_mm_to_swapper, NULL );
    //      page_fault_swapper_to_mm
    pthread_cond_init( &cond_page_fault_swapper_to_mm, NULL );
    //      free_memory_to_mm
    pthread_cond_init( &cond_free_memory_to_mm, NULL );
    //      bitmap
    pthread_cond_init( &cond_bitmap, NULL );


    //                              CONTROLE DE LOGS
    add_log_cat(l,'e');
    add_log_cat(l,'u');
    add_log_cat(l,'m');
    add_log_cat(l,'s');
    add_log_cat(l,'c');
    
    logs_off(l,'e');
    logs_off(l,'u');
    // logs_off(l,'m');
    // logs_off(l,'s');
    // logs_off(l,'c');


    //                              Criando threads

    //      USER
    if ( ( pthread_create( &thread_id_user, NULL, td_user, NULL ) ) != 0 )
        err("Nao foi possivel criar a thread usuario");             
    //      MEMORY MANAGER
    if ( ( pthread_create( &thread_id_memory_manager, NULL, td_memory_manager, NULL ) ) != 0 )
        err("Nao foi possivel criar a thread memory manager");
    //      SCHEDULER
    if ( ( pthread_create( &thread_id_scheduler, NULL, td_scheduler, NULL ) ) != 0 )
        err("Nao foi possivel criar a thread scheduler");
    //      CPU
    if ( ( pthread_create( &thread_id_cpu, NULL, td_cpu, NULL ) ) != 0 )
        err("Nao foi possivel criar a thread cpu");
    //      SWAPPER
    if ( ( pthread_create( &thread_id_swapper, NULL, td_swapper, NULL)) != 0 )
        err("Nao foi possivel criar a thread swapper");



    //                              BORDER PLANET
    pthread_join( thread_id_user, NULL );
    pthread_join( thread_id_memory_manager, NULL) ;
    pthread_join( thread_id_scheduler, NULL );
    pthread_join( thread_id_cpu, NULL );

    pthread_mutex_destroy( &mutex_jobList_to_mm );
    pthread_mutex_destroy( &mutex_jobList_to_scheduler );
    pthread_mutex_destroy( &mutex_vmemory );
    pthread_mutex_destroy( &mutex_bitmap );
    pthread_mutex_destroy( &mutex_priority );
    pthread_mutex_destroy( &mutex_memory );
    pthread_mutex_destroy( &mutex_page_fault_cpu_to_mm );
    pthread_mutex_destroy( &mutex_page_fault_mm_to_cpu );
    pthread_mutex_destroy( &mutex_page_fault_mm_to_swapper);
    pthread_mutex_destroy( &mutex_page_fault_swapper_to_mm );

    pthread_cond_destroy( &cond_jobList_to_mm );
    pthread_cond_destroy( &cond_jobList_to_scheduler );
    pthread_cond_destroy( &cond_priority );
    pthread_cond_destroy( &cond_memory );
    pthread_cond_destroy( &cond_page_fault_cpu_to_mm );
    pthread_cond_destroy( &cond_page_fault_mm_to_cpu );
    pthread_cond_destroy( &cond_page_fault_mm_to_swapper );
    pthread_cond_destroy( &cond_page_fault_swapper_to_mm );
    pthread_cond_destroy( &cond_bitmap );

    return 0;
}