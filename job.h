#include "utils.h"

/*
    - ideal eh que se faca com thread para se ter uma ideia de como funciona na realidade
    - utilizar mutex e verificações de condição nas threads para controlar sua, execução ou 'pausa'
        - nese caso cada job teria um mutex, para controla-lo
    - sujestoes 'pthread_cond_wait'
    - abstrair o tempo real como uma 'moeda' que se pode diminuir apos uma 'execucao' da thread
        - de fato, nao eh necessario que a thread faca algo, eh necessario somente que ela exista.
*/

typedef struct Job
{
    /*  Doc
        Descricao:
            Job eh uma abstracao do que seria um processo pronto para executar;

        Comment:
            O problema atual diz que nao eh possivel saber o tempo que um processo leva para
            executar, logo o atributo 'tmp' somente sera inicializado quando o processo estiver 'em execucao' 
    */

    pthread_cond_t cond;  // condicao de thread
    pthread_mutex_t lock; // mutex da condicao da thread

    pthread_t *pt;
    void *fn;
    void *tret;

    int id;
    int tmp;       // tempo que levaria para executar
    int priority;  // prioridade, sera 0 se o job tiver terminado de executar, ou o valor que for definido em 'create_job()"

    struct Job *prox;
}Job;

int __id_now = 10000; // guardar o ultimo id numa variavel global ' de forma ingênua pode ser inseguro no realidade'


Job*
create_job (void * fn, int priority )
{
    /*  Doc
        Descricao:
            cria um Job 
            precisa chamar 'srand' na 'main'
    */


    pthread_t thr_id;
    void *tret;

    Job *j = (Job *) malloc (sizeof(Job));

    if (j)
    {
        j->pt = &thr_id;
        j->fn = fn;
        j->tret = tret;
        j->priority = priority;
        j->tmp = 1+(rand()%9);          

        j->id = __id_now;
        __id_now++;

        j->prox = NULL;
        j->priority = priority;

    } else
        err("can't malloc Job");

    return j;
}

