
typedef struct Job
{
    int id;

    int endereco;   // endereco do processo na memoria fisica
    int tam;        // tamanho do processo
    int priority;

    Pagetable* pagetable; // tabla de paginas do processo

    pthread_mutex_t mutex;

}Job;

int __id_now = 0; // guardar o ultimo id numa variavel global


Job*
create_job ( int priority, int endereco, int tam )
{

    Job *j = (Job *) malloc ( sizeof(Job) );
    if (j)
    {
        pthread_mutex_t mutex;
        pthread_mutex_init(&mutex, NULL);

        j->mutex = mutex;
        j->priority = priority;
        j->endereco = endereco;
        j->pagetable = NULL;
        j->tam = tam;
        j->id = __id_now;
        __id_now++;

    } else
        err("can't malloc Job");

    return j;
}

