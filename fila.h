typedef struct No
{
    void* data;
    struct No* prox;
    struct No* ant;
}No;

typedef struct Fila
{
    // int tam;
    int tam_atual;

    No* start;
    No* end;
}Fila;

No* fila_drop ( Fila* f );
void fila_add ( Fila *f, void* data );
void fila_print ( Fila* f );
Fila* fila_create ();
No* fila_find ( Fila* f, void* data );
No* fila_remove ( Fila* f, No* data );

Fila*
fila_create ()
{
    Fila* f = malloc ( sizeof ( Fila ) );
    if ( f )
    {
        //f->tam = tam;
        f->tam_atual = 0;
        f->start = NULL;
        f->end = NULL;
    }    
    return f;
}

No*
fila_drop ( Fila* f )
{
    No* remover = f->start;

    if ( remover != NULL)
    {
        if (remover -> prox == NULL) 
        {
            f->start = NULL;
        } else {
            f->start = remover->prox;
            f->start->ant = NULL;
        }
        f->tam_atual--;

        remover->prox = NULL;
    }
    return remover;
}

No*
fila_remove ( Fila* f, No* no_remover )
{
    if (no_remover == NULL)
        return NULL;
    
    if (no_remover == f->start)
        return fila_drop(f);

    No* anterior = no_remover->ant;
    No* proximo = no_remover->prox;

    if (anterior)
        anterior->prox = proximo;

    if (proximo)
        proximo->ant = anterior;

    f->tam_atual--;

    no_remover->prox = NULL;
    no_remover->ant = NULL;
    
    return no_remover;
}

void
fila_add ( Fila *f, void* data )
{
    No* no = (No*) malloc (sizeof(No));
    
    if ( f->tam_atual )
    {
        f->end->prox = no;
        no->ant = f->end;
        f->end = no;
    } 
    else
    {
        f->start = no;
        f->end = no;
    }
    no->data = data;
    f->tam_atual++;
}

void
fila_print ( Fila* f )
{
    No* p = f->start;
    printf(">> ");
    while (p)
    {
        printf("%p",p);

        if ( p->prox )
            printf(" <-> ");
        
        p = p->prox;
    }
    puts("");
}

No*
fila_find ( Fila* f, void* data )
{
    No* p = f->start;
    while (p)
    {
        if ( p->data == data )
            return p;

        p = p->prox;
    }
    return p; // not found
}
